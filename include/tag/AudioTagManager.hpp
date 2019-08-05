#pragma once
#include <tag/config/AudioTagConfiguration.hpp>
#include <tag/ContainerMetadata.hpp>
#include <tag/AudioTagMap.hpp>

namespace tag {
    // TODO: rename to tag_manager
	class AudioTagManager {
	public:
		explicit AudioTagManager(const std::filesystem::path &filePath);
		virtual ~AudioTagManager();
		
		const config::AudioTagConfiguration& getConfiguration() const;

		const ContainerMetadata& getContainerMetadata() const;

		const std::filesystem::path& getFilePath() const noexcept;

		ContainerFormat getContainerFormat() const noexcept;
		std::string getContainerFormatString() const noexcept;

		AudioTagFormat getAudioTagFormat() const noexcept;
		std::string getAudioTagFormatString() const;

		const std::vector<AudioTagLocation>& getAudioTagLocations() const;

		const AudioTagMap& getTagMap() const;
		AudioTagMap& getTagMap();
		void setTagMap(const AudioTagMap &tagMap);

        bool updateTags();
        void updateTagsFrom(const std::filesystem::path &filePath);
        void writeTags();
        void writeTagsTo(const std::filesystem::path &filePath) const;
        void clearTags();
	protected:
		AudioTagManager(const std::filesystem::path &filePath, std::shared_ptr<config::AudioTagConfiguration> configuration);

		std::shared_ptr<config::AudioTagConfiguration> configuration;
	private:
		void read();
		ContainerMetadata containerMetadata;
		AudioTagMap tagMap;

		static const config::AudioTagConfiguration DEFAULT_CONFIGURATION;
	};


	class ConfigurableAudioTagManager : public AudioTagManager {
	public:
		explicit ConfigurableAudioTagManager(const std::filesystem::path &filePath, const config::AudioTagConfiguration &configuration = config::AudioTagConfiguration());

        using AudioTagManager::getConfiguration;
		config::AudioTagConfiguration& getConfiguration();
		void setConfiguration(const config::AudioTagConfiguration &configuration);
	};


	class SharedConfigAudioTagManager : public AudioTagManager {
	public:
		explicit SharedConfigAudioTagManager(const std::filesystem::path &filePath, std::shared_ptr<config::AudioTagConfiguration> configuration);
	};
}
