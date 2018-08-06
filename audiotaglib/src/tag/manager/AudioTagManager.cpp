#include "AudioTagManager.hpp"
namespace fs = std::filesystem;

namespace tag::manager {
	AudioTagManager::AudioTagManager(const fs::path & filePath)
		: AudioTagManager(filePath, SharedAudioTagManagerConfiguration(
			const_cast<AudioTagManagerConfiguration*>(&DEFAULT_CONFIGURATION), [](auto) {})
		) {}


	AudioTagManager::~AudioTagManager() {}







	const AudioTagManagerConfiguration & AudioTagManager::getConfiguration() const {
		return *configuration;
	}






	const AudioFileInformation & AudioTagManager::getAudioFileInformation() const {
		return audioFileInformation;
	}






	const std::filesystem::path & AudioTagManager::getFilePath() const noexcept {
		return getAudioFileInformation().getFilePath();
	}







	AudioContainerFormat AudioTagManager::getAudioContainerFormat() const noexcept {
		return getAudioFileInformation().getAudioContainerFormat();
	}

	std::string AudioTagManager::getAudioContainerFormatString() const noexcept {
		return getAudioFileInformation().getAudioContainerFormatString();
	}






	AudioTagFormat AudioTagManager::getAudioTagFormat() const noexcept {
		return getAudioFileInformation().getAudioTagFormat();
	}

	std::string AudioTagManager::getAudioTagFormatString() const {
		return getAudioFileInformation().getAudioTagFormatString();
	}






	const std::vector<AudioTagInformation>& AudioTagManager::getAudioTagInformations() const {
		return getAudioFileInformation().getAudioTagInformations();
	}







	const AudioTagMap & AudioTagManager::getTagMap() const {
		if (!readingDone)
			read();
		return tagMap;
	}



	AudioTagMap & AudioTagManager::getTagMap() {
		if (!readingDone)
			read();
		return tagMap;
	}



	void AudioTagManager::setTagMap(const AudioTagMap & tagMap) {
		if (!readingDone)
			read();
		this->tagMap = tagMap;
	}








	AudioTagManager::AudioTagManager(const std::filesystem::path & filePath, SharedAudioTagManagerConfiguration configuration)
		: configuration(configuration)
		, audioFileInformation(filePath, configuration->scanAllPossible)
		, readingDone(false)
		, tagMap() {}










	void AudioTagManager::read() const {
		const std::size_t MIN_BUFFER_SIZE = 2048;
		const std::size_t BUFFER_SIZE = 32768;
		static thread_local char BUFFER[BUFFER_SIZE];

		tagMap.clear();
		for (auto &pos : audioFileInformation.getAudioTagInformations()) {
			reader::SharedAudioTagReader reader = reader::StaticReaderFactory::getReader(pos.getTagFormat());
			if (reader != nullptr) {
				std::ifstream fileStream(getFilePath(), std::ios::in | std::ios::binary);
				fileStream.rdbuf()->pubsetbuf(BUFFER, std::clamp(pos.getLength(), MIN_BUFFER_SIZE, BUFFER_SIZE));
				fileStream.seekg(std::streamoff(pos.getHeaderOffset()), std::ios::cur);

				tagMap.mergeWithOverwrite(reader->readTag(fileStream));
			}
		}
		readingDone = true;
	}






	const AudioTagManagerConfiguration AudioTagManager::DEFAULT_CONFIGURATION;




















	ConfigurableAudioTagManager::ConfigurableAudioTagManager(const fs::path & filePath, const AudioTagManagerConfiguration & configuration)
		: AudioTagManager(filePath) {
		this->configuration = std::make_shared<AudioTagManagerConfiguration>(configuration);
	}


	ConfigurableAudioTagManager::~ConfigurableAudioTagManager() {}


	AudioTagManagerConfiguration & ConfigurableAudioTagManager::getConfiguration() const {
		return *configuration;
	}


	void ConfigurableAudioTagManager::setConfiguration(const AudioTagManagerConfiguration & configuration) {
		*this->configuration = configuration;
	}






















	SharedConfigAudioTagManager::SharedConfigAudioTagManager(const fs::path & filePath, SharedAudioTagManagerConfiguration configuration)
		: AudioTagManager(filePath){
		this->configuration = configuration;
	}

	SharedConfigAudioTagManager::~SharedConfigAudioTagManager() {}
}
