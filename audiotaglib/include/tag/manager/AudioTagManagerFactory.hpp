#pragma once
#include <tag/manager/AudioTagManager.hpp>

namespace tag::manager {

	class AudioTagManagerFactory {
	public:
		virtual ~AudioTagManagerFactory() noexcept;
		virtual SharedAudioTagManager create(const std::filesystem::path &path) const;
	};


	class ConfigurableAudioTagManagerFactory : public AudioTagManagerFactory {
		explicit ConfigurableAudioTagManagerFactory(const AudioTagManagerConfiguration &configuration = AudioTagManagerConfiguration());
		virtual ~ConfigurableAudioTagManagerFactory();
		virtual SharedAudioTagManager create(const std::filesystem::path &path) const override;

		const AudioTagManagerConfiguration& getConfiguration() const;
		AudioTagManagerConfiguration& getConfiguration();
		void setConfiguration(const AudioTagManagerConfiguration &configuration);
	private:
		AudioTagManagerConfiguration configuration;
	};



	class SharedConfigAudioTagManagerFactory : public AudioTagManagerFactory {
	public:
		explicit SharedConfigAudioTagManagerFactory(const AudioTagManagerConfiguration &configuration = AudioTagManagerConfiguration());
		virtual ~SharedConfigAudioTagManagerFactory() noexcept;
		virtual SharedAudioTagManager create(const std::filesystem::path &path) const override;

		const AudioTagManagerConfiguration& getConfiguration() const;
		AudioTagManagerConfiguration& getConfiguration();
		void setConfiguration(const AudioTagManagerConfiguration &configuration);
	private: 
		SharedAudioTagManagerConfiguration configuration;
	};
}

