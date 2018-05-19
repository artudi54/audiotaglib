#include "TagManagerFactory.hpp"


namespace tag::manager {
	TagManagerFactory::~TagManagerFactory() noexcept {}


	SharedTagManager TagManagerFactory::create(const fs::path & path) const {
		return std::make_shared<TagManager>(path);
	}







	SharedConfigTagManagerFactory::SharedConfigTagManagerFactory(const TagConfiguration &configuration)
		:configuration(std::make_shared<TagConfiguration>(configuration)) {}


	SharedConfigTagManagerFactory::~SharedConfigTagManagerFactory() noexcept {}


	SharedTagManager SharedConfigTagManagerFactory::create(const fs::path & path) const {
		return std::make_shared<SharedConfigTagManager>(path, configuration);
	}


	const TagConfiguration & SharedConfigTagManagerFactory::getConfiguration() const {
		return *configuration;
	}


	TagConfiguration & SharedConfigTagManagerFactory::getConfiguration() {
		return *configuration;
	}


	void SharedConfigTagManagerFactory::setConfiguration(const TagConfiguration & configuration) {
		*this->configuration = configuration;
	}




	ConfigurableTagManagerFactory::ConfigurableTagManagerFactory(const TagConfiguration & configuration)
		: configuration(configuration) {}


	ConfigurableTagManagerFactory::~ConfigurableTagManagerFactory() {}


	SharedTagManager ConfigurableTagManagerFactory::create(const fs::path & path) const {
		return std::make_shared<ConfigurableTagManager>(path, configuration);
	}


	const TagConfiguration & ConfigurableTagManagerFactory::getConfiguration() const {
		return configuration;
	}


	TagConfiguration & ConfigurableTagManagerFactory::getConfiguration() {
		return configuration;
	}


	void ConfigurableTagManagerFactory::setConfiguration(const TagConfiguration & configuration) {
		this->configuration = configuration;
	}
}
