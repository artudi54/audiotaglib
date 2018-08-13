#pragma once
#include <tag/manager/AudioTagManagerConfiguration.hpp>
#include <tag/scanner/StaticScannerFactory.hpp>
#include <tag/reader/StaticReaderFactory.hpp>
#include <tag/AudioFileInformation.hpp>
#include <tag/AudioTagMap.hpp>

namespace tag::manager {
	class AudioTagManager {
	public:
		explicit AudioTagManager(const std::filesystem::path &filePath);
		virtual ~AudioTagManager();
		
		const AudioTagManagerConfiguration& getConfiguration() const;

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

	protected:
		explicit AudioTagManager(const std::filesystem::path &filePath, SharedAudioTagManagerConfiguration configuration);

		SharedAudioTagManagerConfiguration configuration;
	private:
		void read() const;
		AudioFileInformation audioFileInformation;
		mutable bool readingDone;
		mutable AudioTagMap tagMap;

		static const AudioTagManagerConfiguration DEFAULT_CONFIGURATION;
	};
	using SharedAudioTagManager = std::shared_ptr<AudioTagManager>;


	class ConfigurableAudioTagManager : public AudioTagManager {
	public:
		explicit ConfigurableAudioTagManager(const std::filesystem::path &filePath, const AudioTagManagerConfiguration &configuration = AudioTagManagerConfiguration());
		virtual ~ConfigurableAudioTagManager() override;

        using AudioTagManager::getConfiguration;
		AudioTagManagerConfiguration& getConfiguration();
		void setConfiguration(const AudioTagManagerConfiguration &configuration);
	};


	class SharedConfigAudioTagManager : public AudioTagManager {
	public:
		explicit SharedConfigAudioTagManager(const std::filesystem::path &filePath, SharedAudioTagManagerConfiguration configuration);
		virtual ~SharedConfigAudioTagManager() override;
	};
}
