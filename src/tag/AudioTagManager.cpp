#include "AudioTagManager.hpp"
#include <tag/scanner/TagScannerProvider.hpp>
#include <tag/reader/StaticReaderFactory.hpp>
#include <tag/manager/write/StaticWriteManagerFactory.hpp>
#include <tag/except/TagsNotSupportedException.hpp>

namespace fs = std::filesystem;

namespace tag {
	AudioTagManager::AudioTagManager(const fs::path & filePath)
		: AudioTagManager(filePath, std::shared_ptr<config::AudioTagConfiguration>(
			const_cast<config::AudioTagConfiguration*>(&DEFAULT_CONFIGURATION), [](auto) {})
		) {}

	AudioTagManager::~AudioTagManager() {}


	const config::AudioTagConfiguration & AudioTagManager::getConfiguration() const {
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


	const std::vector<AudioTagLocation>& AudioTagManager::getAudioTagLocations() const {
		return getAudioFileInformation().getAudioTagLocations();
	}


	const AudioTagMap & AudioTagManager::getTagMap() const {
		return tagMap;
	}

	AudioTagMap & AudioTagManager::getTagMap() {
		return tagMap;
	}

	void AudioTagManager::setTagMap(const AudioTagMap & tagMap) {
		this->tagMap = tagMap;
	}

    bool AudioTagManager::updateTags() {
        if (audioFileInformation.update(configuration->scanConfiguration)) {
            read();
            return true;
        }
        return false;
    }

    void AudioTagManager::updateTagsFrom(const std::filesystem::path &filePath) {
        // TODO: fix
    }

    void AudioTagManager::writeTags() {
	    audioFileInformation.update(configuration->scanConfiguration);
        std::shared_ptr<manager::write::TagWriteManager> writeManager = manager::write::StaticWriteManagerFactory::getWriteManager(
                audioFileInformation.getAudioContainerFormat());
        if (writeManager == nullptr)
            throw except::TagsNotSupportedException(audioFileInformation.getFilePath());
        writeManager->write(tagMap, audioFileInformation, configuration->writeConfiguration);
    }

	void AudioTagManager::writeTagsTo(const std::filesystem::path &filePath) const {
		AudioFileInformation fileInformation(filePath);
        std::shared_ptr<manager::write::TagWriteManager> writeManager = manager::write::StaticWriteManagerFactory::getWriteManager(
				fileInformation.getAudioContainerFormat());
		if (writeManager == nullptr)
			throw except::TagsNotSupportedException(audioFileInformation.getFilePath());
		writeManager->write(tagMap, fileInformation, configuration->writeConfiguration);
	}

	void AudioTagManager::clearTags() {
		tagMap.clear();
		writeTags();
	}

	AudioTagManager::AudioTagManager(const std::filesystem::path & filePath, std::shared_ptr<config::AudioTagConfiguration> configuration)
		: configuration(configuration)
		, audioFileInformation(filePath, configuration->scanConfiguration)
		, tagMap() {
		read();
	}


	void AudioTagManager::read() {
		const std::size_t MIN_BUFFER_SIZE = 2048;
		const std::size_t BUFFER_SIZE = 32768;
		static thread_local char BUFFER[BUFFER_SIZE];

		tagMap.clear();
		for (auto &pos : audioFileInformation.getAudioTagLocations()) {
			reader::SharedAudioTagReader reader = reader::StaticReaderFactory::getReader(pos.getTagFormat());
			if (reader != nullptr) {
				std::ifstream fileStream(getFilePath(), std::ios::in | std::ios::binary);
				fileStream.rdbuf()->pubsetbuf(BUFFER, std::clamp(pos.getLength(), MIN_BUFFER_SIZE, BUFFER_SIZE));
				fileStream.seekg(std::streamoff(pos.getHeaderOffset()), std::ios::cur);

				tagMap.mergeWithOverwrite(reader->readTag(fileStream));
			}
		}
	}


    const config::AudioTagConfiguration AudioTagManager::DEFAULT_CONFIGURATION;




	ConfigurableAudioTagManager::ConfigurableAudioTagManager(const fs::path & filePath, const config::AudioTagConfiguration & configuration)
		: AudioTagManager(filePath) {
		this->configuration = std::make_shared<config::AudioTagConfiguration>(configuration);
	}


	config::AudioTagConfiguration & ConfigurableAudioTagManager::getConfiguration() {
		return *configuration;
	}

	void ConfigurableAudioTagManager::setConfiguration(const config::AudioTagConfiguration & configuration) {
		*this->configuration = configuration;
	}




	SharedConfigAudioTagManager::SharedConfigAudioTagManager(const fs::path & filePath, std::shared_ptr<config::AudioTagConfiguration> configuration)
		: AudioTagManager(filePath) {
		this->configuration = std::move(configuration);
	}
}
