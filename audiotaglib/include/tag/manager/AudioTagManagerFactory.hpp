#pragma once
#include <tag/manager/AudioTagManager.hpp>

namespace tag::manager {
	class AudioTagManagerFactory {
	public:
		virtual ~AudioTagManagerFactory() noexcept;
		virtual SharedAudioTagManager create(const std::filesystem::path &path) const;
	};


	class ConfigurableAudioTagManagerFactory : public AudioTagManagerFactory {
		explicit ConfigurableAudioTagManagerFactory(const config::AudioTagConfiguration &configuration = config::AudioTagConfiguration());
		virtual ~ConfigurableAudioTagManagerFactory() override;
		virtual SharedAudioTagManager create(const std::filesystem::path &path) const override;

		const config::AudioTagConfiguration& getConfiguration() const;
		config::AudioTagConfiguration& getConfiguration();
		void setConfiguration(const config::AudioTagConfiguration &configuration);
	private:
		config::AudioTagConfiguration configuration;
	};


	class SharedConfigAudioTagManagerFactory : public AudioTagManagerFactory {
	public:
		explicit SharedConfigAudioTagManagerFactory(const config::AudioTagConfiguration &configuration = config::AudioTagConfiguration());
		virtual ~SharedConfigAudioTagManagerFactory() override;
		virtual SharedAudioTagManager create(const std::filesystem::path &path) const override;

		const config::AudioTagConfiguration& getConfiguration() const;
		config::AudioTagConfiguration& getConfiguration();
		void setConfiguration(const config::AudioTagConfiguration &configuration);
	private: 
		std::shared_ptr<config::AudioTagConfiguration> configuration;
	};
}
