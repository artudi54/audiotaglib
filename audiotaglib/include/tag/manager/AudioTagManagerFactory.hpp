#pragma once
#include <memory>
#include <tag/manager/AudioTagManager.hpp>

namespace tag::manager {
	class AudioTagManagerFactory {
	public:
	    AudioTagManagerFactory() = default;
        AudioTagManagerFactory(AudioTagManagerFactory&&) = default;
        AudioTagManagerFactory& operator=(AudioTagManagerFactory&&) = default;

        AudioTagManagerFactory(const AudioTagManagerFactory&) = delete;
        AudioTagManagerFactory& operator=(const AudioTagManagerFactory&) = delete;

		virtual ~AudioTagManagerFactory() noexcept;

		virtual std::unique_ptr<AudioTagManager> create(const std::filesystem::path &path) const;
	};


	class ConfigurableAudioTagManagerFactory : public AudioTagManagerFactory {
	public:
		explicit ConfigurableAudioTagManagerFactory(const config::AudioTagConfiguration &configuration = config::AudioTagConfiguration());
		std::unique_ptr<AudioTagManager> create(const std::filesystem::path &path) const override;

		const config::AudioTagConfiguration& getConfiguration() const;
		config::AudioTagConfiguration& getConfiguration();
		void setConfiguration(const config::AudioTagConfiguration &configuration);
	private:
		config::AudioTagConfiguration configuration;
	};


	class SharedConfigAudioTagManagerFactory : public AudioTagManagerFactory {
	public:
		explicit SharedConfigAudioTagManagerFactory(const config::AudioTagConfiguration &configuration = config::AudioTagConfiguration());
		explicit SharedConfigAudioTagManagerFactory(const std::shared_ptr<config::AudioTagConfiguration> &configuration);
		std::unique_ptr<AudioTagManager> create(const std::filesystem::path &path) const override;

		std::shared_ptr<const config::AudioTagConfiguration> getConfiguration() const;
		std::shared_ptr<config::AudioTagConfiguration> getConfiguration();
	private:
		std::shared_ptr<config::AudioTagConfiguration> configuration;
	};
}
