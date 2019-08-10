#include "FileManagerFactory.hpp"
namespace fs = std::filesystem;

namespace tag {
	FileManagerFactory::~FileManagerFactory() noexcept = default;

    std::unique_ptr<FileManager> FileManagerFactory::create(const fs::path & path) const {
		return std::make_unique<FileManager>(path);
	}



	ConfigurableFileManagerFactory::ConfigurableFileManagerFactory(const config::FileManagerConfiguration & configuration)
		: configuration(configuration) {
	}

    std::unique_ptr<FileManager> ConfigurableFileManagerFactory::create(const fs::path & path) const {
		return std::make_unique<ConfigurableFileManager>(path, configuration);
	}

	const config::FileManagerConfiguration & ConfigurableFileManagerFactory::getConfiguration() const {
		return configuration;
	}

	config::FileManagerConfiguration & ConfigurableFileManagerFactory::getConfiguration() {
		return configuration;
	}

	void ConfigurableFileManagerFactory::setConfiguration(const config::FileManagerConfiguration & configuration) {
		this->configuration = configuration;
	}



	SharedConfigFileManagerFactory::SharedConfigFileManagerFactory(const config::FileManagerConfiguration &configuration)
		:configuration(std::make_shared<config::FileManagerConfiguration>(configuration)) {}

	SharedConfigFileManagerFactory::SharedConfigFileManagerFactory(const std::shared_ptr<config::FileManagerConfiguration> &configuration)
	    :configuration(configuration) {}
    std::unique_ptr<FileManager> SharedConfigFileManagerFactory::create(const fs::path & path) const {
		return std::make_unique<SharedConfigFileManager>(path, configuration);
	}

	std::shared_ptr<const config::FileManagerConfiguration> SharedConfigFileManagerFactory::getConfiguration() const {
		return configuration;
	}

	std::shared_ptr<config::FileManagerConfiguration> SharedConfigFileManagerFactory::getConfiguration() {
		return configuration;
	}
}
