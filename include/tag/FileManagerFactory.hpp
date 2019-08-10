#pragma once
#include <memory>
#include <tag/FileManager.hpp>

namespace tag {
	class FileManagerFactory {
	public:
	    FileManagerFactory() = default;
        FileManagerFactory(FileManagerFactory&&) = default;
        FileManagerFactory& operator=(FileManagerFactory&&) = default;

        FileManagerFactory(const FileManagerFactory&) = delete;
        FileManagerFactory& operator=(const FileManagerFactory&) = delete;

		virtual ~FileManagerFactory() noexcept;

		virtual std::unique_ptr<FileManager> create(const std::filesystem::path &path) const;
	};


	class ConfigurableFileManagerFactory : public FileManagerFactory {
	public:
		explicit ConfigurableFileManagerFactory(const config::Configuration &configuration = config::Configuration());
		std::unique_ptr<FileManager> create(const std::filesystem::path &path) const override;

		const config::Configuration& getConfiguration() const;
		config::Configuration& getConfiguration();
		void setConfiguration(const config::Configuration &configuration);
	private:
		config::Configuration configuration;
	};


	class SharedConfigFileManagerFactory : public FileManagerFactory {
	public:
		explicit SharedConfigFileManagerFactory(const config::Configuration &configuration = config::Configuration());
		explicit SharedConfigFileManagerFactory(const std::shared_ptr<config::Configuration> &configuration);
		std::unique_ptr<FileManager> create(const std::filesystem::path &path) const override;

		std::shared_ptr<const config::Configuration> getConfiguration() const;
		std::shared_ptr<config::Configuration> getConfiguration();
	private:
		std::shared_ptr<config::Configuration> configuration;
	};
}
