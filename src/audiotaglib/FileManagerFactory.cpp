#include "FileManagerFactory.hpp"
namespace fs = std::filesystem;

namespace audiotaglib {
	FileManagerFactory::~FileManagerFactory() noexcept = default;

    std::unique_ptr<FileManager> FileManagerFactory::create(const fs::path & path) const {
		return std::make_unique<FileManager>(path);
	}



	ConfigurableFileManagerFactory::ConfigurableFileManagerFactory(const config::Configuration & configuration)
		: configuration(configuration) {
	}

    std::unique_ptr<FileManager> ConfigurableFileManagerFactory::create(const fs::path & path) const {
		return std::make_unique<ConfigurableFileManager>(path, configuration);
	}

	const config::Configuration & ConfigurableFileManagerFactory::getConfiguration() const {
		return configuration;
	}

	config::Configuration & ConfigurableFileManagerFactory::getConfiguration() {
		return configuration;
	}

	void ConfigurableFileManagerFactory::setConfiguration(const config::Configuration & configuration) {
		this->configuration = configuration;
	}



	SharedConfigFileManagerFactory::SharedConfigFileManagerFactory(const config::Configuration &configuration)
		:configuration(std::make_shared<config::Configuration>(configuration)) {}

	SharedConfigFileManagerFactory::SharedConfigFileManagerFactory(const std::shared_ptr<config::Configuration> &configuration)
	    :configuration(configuration) {}
    std::unique_ptr<FileManager> SharedConfigFileManagerFactory::create(const fs::path & path) const {
		return std::make_unique<SharedConfigFileManager>(path, configuration);
	}

	std::shared_ptr<const config::Configuration> SharedConfigFileManagerFactory::getConfiguration() const {
		return configuration;
	}

	std::shared_ptr<config::Configuration> SharedConfigFileManagerFactory::getConfiguration() {
		return configuration;
	}
}
