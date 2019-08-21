#pragma once
#include <audiotaglib/config/Configuration.hpp>
#include <audiotaglib/ContainerMetadata.hpp>
#include <audiotaglib/TagMap.hpp>

namespace audiotaglib {
	class FileManager {
	public:
		explicit FileManager(const std::filesystem::path &filePath);
		virtual ~FileManager();
		
		const config::Configuration& getConfiguration() const;

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
		FileManager(const std::filesystem::path &filePath, std::shared_ptr<config::Configuration> configuration);

		std::shared_ptr<config::Configuration> configuration;
	private:
		void read();
		ContainerMetadata containerMetadata;
		TagMap tagMap;

		static const config::Configuration DEFAULT_CONFIGURATION;
	};


	class ConfigurableFileManager : public FileManager {
	public:
		explicit ConfigurableFileManager(const std::filesystem::path &filePath, const config::Configuration &configuration = config::Configuration());

        using FileManager::getConfiguration;
		config::Configuration& getConfiguration();
		void setConfiguration(const config::Configuration &configuration);
	};


	class SharedConfigFileManager : public FileManager {
	public:
		explicit SharedConfigFileManager(const std::filesystem::path &filePath, std::shared_ptr<config::Configuration> configuration);
	};
}
