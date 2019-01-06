#include "AudioTagManagerFactory.hpp"
namespace fs = std::filesystem;

namespace tag::manager {
	AudioTagManagerFactory::~AudioTagManagerFactory() noexcept {}

	SharedAudioTagManager AudioTagManagerFactory::create(const fs::path & path) const {
		return std::make_shared<AudioTagManager>(path);
	}




	ConfigurableAudioTagManagerFactory::ConfigurableAudioTagManagerFactory(const config::AudioTagConfiguration & configuration)
		: configuration(configuration) {
	}

	ConfigurableAudioTagManagerFactory::~ConfigurableAudioTagManagerFactory() {}

		SharedAudioTagManager ConfigurableAudioTagManagerFactory::create(const fs::path & path) const {
		return std::make_shared<ConfigurableAudioTagManager>(path, configuration);
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

	SharedConfigAudioTagManagerFactory::~SharedConfigAudioTagManagerFactory() noexcept {}

	SharedAudioTagManager SharedConfigAudioTagManagerFactory::create(const fs::path & path) const {
		return std::make_shared<SharedConfigAudioTagManager>(path, configuration);
	}


	const config::AudioTagConfiguration & SharedConfigAudioTagManagerFactory::getConfiguration() const {
		return *configuration;
	}

	config::AudioTagConfiguration & SharedConfigAudioTagManagerFactory::getConfiguration() {
		return *configuration;
	}
	
	void SharedConfigAudioTagManagerFactory::setConfiguration(const config::AudioTagConfiguration & configuration) {
		*this->configuration = configuration;
	}
}
