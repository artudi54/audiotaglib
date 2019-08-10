#pragma once
#include <tag/config/FileManagerConfiguration.hpp>
#include <tag/ContainerMetadata.hpp>
#include <tag/TagMap.hpp>

namespace tag {
    // TODO: rename to tag_manager
	class FileManager {
	public:
		explicit FileManager(const std::filesystem::path &filePath);
		virtual ~FileManager();
		
		const config::FileManagerConfiguration& getConfiguration() const;

		const ContainerMetadata& getContainerMetadata() const;

		const std::filesystem::path& getFilePath() const noexcept;

		ContainerFormat getContainerFormat() const noexcept;
		std::string getContainerFormatString() const noexcept;

		TagContainerFormat getTagContainerFormats() const noexcept;
		std::string getTagContainerFormatsString() const;

		const std::vector<TagContainerLocation>& getTagContainerLocations() const;

		const TagMap& getTagMap() const;
		TagMap& getTagMap();
		void setTagMap(const TagMap &tagMap);

        bool updateTags();
        void updateTagsFrom(const std::filesystem::path &filePath);
        void writeTags();
        void writeTagsTo(const std::filesystem::path &filePath) const;
        void clearTags();
	protected:
		FileManager(const std::filesystem::path &filePath, std::shared_ptr<config::FileManagerConfiguration> configuration);

		std::shared_ptr<config::FileManagerConfiguration> configuration;
	private:
		void read();
		ContainerMetadata containerMetadata;
		TagMap tagMap;

		static const config::FileManagerConfiguration DEFAULT_CONFIGURATION;
	};


	class ConfigurableFileManager : public FileManager {
	public:
		explicit ConfigurableFileManager(const std::filesystem::path &filePath, const config::FileManagerConfiguration &configuration = config::FileManagerConfiguration());

        using FileManager::getConfiguration;
		config::FileManagerConfiguration& getConfiguration();
		void setConfiguration(const config::FileManagerConfiguration &configuration);
	};


	class SharedConfigFileManager : public FileManager {
	public:
		explicit SharedConfigFileManager(const std::filesystem::path &filePath, std::shared_ptr<config::FileManagerConfiguration> configuration);
	};
}
