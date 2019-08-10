#include "FileManager.hpp"
#include <tag/scanner/TagScannerProvider.hpp>
#include <tag/reader/StaticReaderFactory.hpp>
#include <tag/manager/write/StaticWriteManagerFactory.hpp>
#include <tag/except/TagsNotSupportedException.hpp>

namespace fs = std::filesystem;

namespace tag {
	FileManager::FileManager(const fs::path & filePath)
		: FileManager(filePath, std::shared_ptr<config::FileManagerConfiguration>(
            const_cast<config::FileManagerConfiguration*>(&DEFAULT_CONFIGURATION), [](auto) {})
		) {}

	FileManager::~FileManager() = default;


	const config::FileManagerConfiguration & FileManager::getConfiguration() const {
		return *configuration;
	}


	const ContainerMetadata & FileManager::getContainerMetadata() const {
		return containerMetadata;
	}


	const std::filesystem::path & FileManager::getFilePath() const noexcept {
		return getContainerMetadata().getFilePath();
	}


	ContainerFormat FileManager::getContainerFormat() const noexcept {
		return getContainerMetadata().getContainerFormat();
	}

	std::string FileManager::getContainerFormatString() const noexcept {
		return getContainerMetadata().getContainerFormatString();
	}


	TagContainerFormat FileManager::getTagContainerFormats() const noexcept {
		return getContainerMetadata().getTagContainerFormats();
	}

	std::string FileManager::getTagContainerFormatsString() const {
		return getContainerMetadata().getTagContainerFormatsString();
	}


	const std::vector<TagContainerLocation>& FileManager::getTagContainerLocations() const {
		return getContainerMetadata().getTagContainerLocations();
	}


	const TagMap & FileManager::getTagMap() const {
		return tagMap;
	}

	TagMap & FileManager::getTagMap() {
		return tagMap;
	}

	void FileManager::setTagMap(const TagMap & tagMap) {
		this->tagMap = tagMap;
	}

    bool FileManager::updateTags() {
        if (containerMetadata.update(configuration->scanConfiguration)) {
            read();
            return true;
        }
        return false;
    }

    void FileManager::updateTagsFrom(const std::filesystem::path &filePath) {
        // TODO: fix
    }

    void FileManager::writeTags() {
	    containerMetadata.update(configuration->scanConfiguration);
        std::shared_ptr<manager::write::TagWriteManager> writeManager = manager::write::StaticWriteManagerFactory::getWriteManager(
                containerMetadata.getContainerFormat());
        if (writeManager == nullptr)
            throw except::TagsNotSupportedException(containerMetadata.getFilePath());
        writeManager->write(tagMap, containerMetadata, configuration->writeConfiguration);
    }

	void FileManager::writeTagsTo(const std::filesystem::path &filePath) const {
		ContainerMetadata fileInformation(filePath);
        std::shared_ptr<manager::write::TagWriteManager> writeManager = manager::write::StaticWriteManagerFactory::getWriteManager(
                fileInformation.getContainerFormat());
		if (writeManager == nullptr)
			throw except::TagsNotSupportedException(containerMetadata.getFilePath());
		writeManager->write(tagMap, fileInformation, configuration->writeConfiguration);
	}

	void FileManager::clearTags() {
		tagMap.clear();
		writeTags();
	}

	FileManager::FileManager(const std::filesystem::path & filePath, std::shared_ptr<config::FileManagerConfiguration> configuration)
		: configuration(configuration)
		, containerMetadata(filePath, configuration->scanConfiguration)
		, tagMap() {
		read();
	}


	void FileManager::read() {
		const std::size_t MIN_BUFFER_SIZE = 2048;
		const std::size_t BUFFER_SIZE = 32768;
		static thread_local char BUFFER[BUFFER_SIZE];

		tagMap.clear();
		for (auto &pos : containerMetadata.getTagContainerLocations()) {
			reader::SharedAudioTagReader reader = reader::StaticReaderFactory::getReader(pos.getTagContainerFormat());
			if (reader != nullptr) {
				std::ifstream fileStream(getFilePath(), std::ios::in | std::ios::binary);
				fileStream.rdbuf()->pubsetbuf(BUFFER, std::clamp(pos.getLength(), MIN_BUFFER_SIZE, BUFFER_SIZE));
				fileStream.seekg(std::streamoff(pos.getHeaderOffset()), std::ios::cur);

				tagMap.mergeWithOverwrite(reader->readTag(fileStream));
			}
		}
	}


    const config::FileManagerConfiguration FileManager::DEFAULT_CONFIGURATION;




	ConfigurableFileManager::ConfigurableFileManager(const fs::path & filePath, const config::FileManagerConfiguration & configuration)
		: FileManager(filePath) {
		this->configuration = std::make_shared<config::FileManagerConfiguration>(configuration);
	}


	config::FileManagerConfiguration & ConfigurableFileManager::getConfiguration() {
		return *configuration;
	}

	void ConfigurableFileManager::setConfiguration(const config::FileManagerConfiguration & configuration) {
		*this->configuration = configuration;
	}




	SharedConfigFileManager::SharedConfigFileManager(const fs::path & filePath, std::shared_ptr<config::FileManagerConfiguration> configuration)
		: FileManager(filePath) {
		this->configuration = std::move(configuration);
	}
}
