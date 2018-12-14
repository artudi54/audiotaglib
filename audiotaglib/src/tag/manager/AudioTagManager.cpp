#include "AudioTagManager.hpp"
#include <tag/scanner/StaticScannerFactory.hpp>
#include <tag/reader/StaticReaderFactory.hpp>
#include <tag/manager/write/StaticWriteManagerFactory.hpp>
#include <tag/manager/AudioTagManager.hpp>
#include <tag/except/TagsNotSupportedException.hpp>

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
		return getAudioFileInformation().getAudioTagInformation();
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

    bool AudioTagManager::update() {
        if (audioFileInformation.update(configuration->scanConfiguration)) {
            tagMap.clear();
            read();
            return true;
        }
        return false;
    }

    void AudioTagManager::writeTags() {
	    audioFileInformation.update(configuration->scanConfiguration);
        write::SharedTagWriteManager writeManager = write::StaticWriteManagerFactory::getWriteManager(
                audioFileInformation.getAudioContainerFormat());
        if (writeManager == nullptr)
            throw except::TagsNotSupportedException(audioFileInformation.getFilePath());
        writeManager->write(tagMap, audioFileInformation, configuration->writeConfiguration);
    }

	void AudioTagManager::writeTagsTo(const std::filesystem::path &filePath) const {
		AudioFileInformation fileInformation(filePath);
		write::SharedTagWriteManager writeManager = write::StaticWriteManagerFactory::getWriteManager(
				fileInformation.getAudioContainerFormat());
		if (writeManager == nullptr)
			throw except::TagsNotSupportedException(audioFileInformation.getFilePath());
		writeManager->write(tagMap, fileInformation, configuration->writeConfiguration);
	}

	void AudioTagManager::clearTags() {
		tagMap.clear();
		writeTags();
	}

	void AudioTagManager::writeFrom(const std::filesystem::path &filePath) {
		this->tagMap = AudioTagManager(filePath).getTagMap();
		writeTags();
	}

	void AudioTagManager::writeFrom(const AudioTagMap &tagMap) {
		this->tagMap = tagMap;
		writeTags();
	}

	AudioTagManager::AudioTagManager(const std::filesystem::path & filePath, SharedAudioTagManagerConfiguration configuration)
		: configuration(configuration)
		, audioFileInformation(filePath, configuration->scanConfiguration)
		, readingDone(false)
		, tagMap() {}


	void AudioTagManager::read() const {
		const std::size_t MIN_BUFFER_SIZE = 2048;
		const std::size_t BUFFER_SIZE = 32768;
		static thread_local char BUFFER[BUFFER_SIZE];

		tagMap.clear();
		for (auto &pos : audioFileInformation.getAudioTagInformation()) {
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


	AudioTagManagerConfiguration & ConfigurableAudioTagManager::getConfiguration() {
		return *configuration;
	}

	void ConfigurableAudioTagManager::setConfiguration(const AudioTagManagerConfiguration & configuration) {
		*this->configuration = configuration;
	}




	SharedConfigAudioTagManager::SharedConfigAudioTagManager(const fs::path & filePath, SharedAudioTagManagerConfiguration configuration)
		: AudioTagManager(filePath){
		this->configuration = std::move(configuration);
	}

	SharedConfigAudioTagManager::~SharedConfigAudioTagManager() {}
}
