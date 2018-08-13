#include "AudioTagManagerFactory.hpp"
namespace fs = std::filesystem;

namespace tag::manager {
	AudioTagManagerFactory::~AudioTagManagerFactory() noexcept {}

	SharedAudioTagManager AudioTagManagerFactory::create(const fs::path & path) const {
		return std::make_shared<AudioTagManager>(path);
	}




	ConfigurableAudioTagManagerFactory::ConfigurableAudioTagManagerFactory(const AudioTagManagerConfiguration & configuration)
		: configuration(configuration) {
	}

	ConfigurableAudioTagManagerFactory::~ConfigurableAudioTagManagerFactory() {}

		SharedAudioTagManager ConfigurableAudioTagManagerFactory::create(const fs::path & path) const {
		return std::make_shared<ConfigurableAudioTagManager>(path, configuration);
	}


	const AudioTagManagerConfiguration & ConfigurableAudioTagManagerFactory::getConfiguration() const {
		return configuration;
	}

	AudioTagManagerConfiguration & ConfigurableAudioTagManagerFactory::getConfiguration() {
		return configuration;
	}

	void ConfigurableAudioTagManagerFactory::setConfiguration(const AudioTagManagerConfiguration & configuration) {
		this->configuration = configuration;
	}



	
	SharedConfigAudioTagManagerFactory::SharedConfigAudioTagManagerFactory(const AudioTagManagerConfiguration &configuration)
		:configuration(std::make_shared<AudioTagManagerConfiguration>(configuration)) {}

	SharedConfigAudioTagManagerFactory::~SharedConfigAudioTagManagerFactory() noexcept {}

	SharedAudioTagManager SharedConfigAudioTagManagerFactory::create(const fs::path & path) const {
		return std::make_shared<SharedConfigAudioTagManager>(path, configuration);
	}


	const AudioTagManagerConfiguration & SharedConfigAudioTagManagerFactory::getConfiguration() const {
		return *configuration;
	}

	AudioTagManagerConfiguration & SharedConfigAudioTagManagerFactory::getConfiguration() {
		return *configuration;
	}
	
	void SharedConfigAudioTagManagerFactory::setConfiguration(const AudioTagManagerConfiguration & configuration) {
		*this->configuration = configuration;
	}
}
