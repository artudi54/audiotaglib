
#include <tag/manager/AudioTagManagerFactory.hpp>

#include "AudioTagManagerFactory.hpp"
namespace fs = std::filesystem;

namespace tag::manager {
	AudioTagManagerFactory::~AudioTagManagerFactory() noexcept {}

    std::unique_ptr<AudioTagManager> AudioTagManagerFactory::create(const fs::path & path) const {
		return std::make_unique<AudioTagManager>(path);
	}



	ConfigurableAudioTagManagerFactory::ConfigurableAudioTagManagerFactory(const config::AudioTagConfiguration & configuration)
		: configuration(configuration) {
	}

    std::unique_ptr<AudioTagManager> ConfigurableAudioTagManagerFactory::create(const fs::path & path) const {
		return std::make_unique<ConfigurableAudioTagManager>(path, configuration);
	}

	const config::AudioTagConfiguration & ConfigurableAudioTagManagerFactory::getConfiguration() const {
		return configuration;
	}

	config::AudioTagConfiguration & ConfigurableAudioTagManagerFactory::getConfiguration() {
		return configuration;
	}

	void ConfigurableAudioTagManagerFactory::setConfiguration(const config::AudioTagConfiguration & configuration) {
		this->configuration = configuration;
	}



	SharedConfigAudioTagManagerFactory::SharedConfigAudioTagManagerFactory(const config::AudioTagConfiguration &configuration)
		:configuration(std::make_shared<config::AudioTagConfiguration>(configuration)) {}

	SharedConfigAudioTagManagerFactory::SharedConfigAudioTagManagerFactory(const std::shared_ptr<config::AudioTagConfiguration> &configuration)
	    :configuration(configuration) {}
    std::unique_ptr<AudioTagManager> SharedConfigAudioTagManagerFactory::create(const fs::path & path) const {
		return std::make_unique<SharedConfigAudioTagManager>(path, configuration);
	}

	std::shared_ptr<const config::AudioTagConfiguration> SharedConfigAudioTagManagerFactory::getConfiguration() const {
		return configuration;
	}

	std::shared_ptr<config::AudioTagConfiguration> SharedConfigAudioTagManagerFactory::getConfiguration() {
		return configuration;
	}
}
