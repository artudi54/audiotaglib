#pragma once
#include <tag/config/AudioTagConfiguration.hpp>
#include <tag/AudioFileInformation.hpp>
#include <tag/AudioTagMap.hpp>

namespace tag::manager {
	class AudioTagManager {
	public:
		explicit AudioTagManager(const std::filesystem::path &filePath);
		virtual ~AudioTagManager();
		
		const config::AudioTagConfiguration& getConfiguration() const;

		const AudioFileInformation& getAudioFileInformation() const;

		const std::filesystem::path& getFilePath() const noexcept;

		AudioContainerFormat getAudioContainerFormat() const noexcept;
		std::string getAudioContainerFormatString() const noexcept;

		AudioTagFormat getAudioTagFormat() const noexcept;
		std::string getAudioTagFormatString() const;

		const std::vector<AudioTagInformation>& getAudioTagInformations() const;

		const AudioTagMap& getTagMap() const;
		AudioTagMap& getTagMap();
		void setTagMap(const AudioTagMap &tagMap);

        bool update();
        void writeTags();
        void writeTagsTo(const std::filesystem::path &filePath) const;
        void clearTags();
        void writeFrom(const std::filesystem::path &filePath);
        void writeFrom(const AudioTagMap &tagMap);
	protected:
		explicit AudioTagManager(const std::filesystem::path &filePath, std::shared_ptr<config::AudioTagConfiguration> configuration);

		std::shared_ptr<config::AudioTagConfiguration> configuration;
	private:
		void read();
		AudioFileInformation audioFileInformation;
		AudioTagMap tagMap;

		static const config::AudioTagConfiguration DEFAULT_CONFIGURATION;
	};
	using SharedAudioTagManager = std::shared_ptr<AudioTagManager>;


	class ConfigurableAudioTagManager : public AudioTagManager {
	public:
		explicit ConfigurableAudioTagManager(const std::filesystem::path &filePath, const config::AudioTagConfiguration &configuration = config::AudioTagConfiguration());
		virtual ~ConfigurableAudioTagManager() override;

        using AudioTagManager::getConfiguration;
		config::AudioTagConfiguration& getConfiguration();
		void setConfiguration(const config::AudioTagConfiguration &configuration);
	};


	class SharedConfigAudioTagManager : public AudioTagManager {
	public:
		explicit SharedConfigAudioTagManager(const std::filesystem::path &filePath, std::shared_ptr<config::AudioTagConfiguration> configuration);
		virtual ~SharedConfigAudioTagManager() override;
	};
}
