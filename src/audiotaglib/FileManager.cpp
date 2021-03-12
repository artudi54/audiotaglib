#include "FileManager.hpp"
#include <audiotaglib/reader/StaticReaderFactory.hpp>
#include <audiotaglib/manager/write/StaticWriteManagerFactory.hpp>
#include <audiotaglib/except/TagsNotSupportedException.hpp>

namespace fs = std::filesystem;

namespace audiotaglib {
	FileManager::FileManager(const fs::path & filePath)
		: FileManager(filePath, std::shared_ptr<config::Configuration>(
            const_cast<config::Configuration*>(&DEFAULT_CONFIGURATION), [](auto) {})
		) {}

	FileManager::~FileManager() = default;


	const config::Configuration & FileManager::getConfiguration() const {
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

	FileManager::FileManager(const std::filesystem::path & filePath, std::shared_ptr<config::Configuration> configuration)
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


    const config::Configuration FileManager::DEFAULT_CONFIGURATION;




	ConfigurableFileManager::ConfigurableFileManager(const fs::path & filePath, const config::Configuration & configuration)
		: FileManager(filePath) {
		this->configuration = std::make_shared<config::Configuration>(configuration);
	}


	config::Configuration & ConfigurableFileManager::getConfiguration() {
		return *configuration;
	}

	void ConfigurableFileManager::setConfiguration(const config::Configuration & configuration) {
		*this->configuration = configuration;
	}




	SharedConfigFileManager::SharedConfigFileManager(const fs::path & filePath, std::shared_ptr<config::Configuration> configuration)
		: FileManager(filePath) {
		this->configuration = std::move(configuration);
	}
}
