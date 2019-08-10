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
		explicit ConfigurableFileManagerFactory(const config::FileManagerConfiguration &configuration = config::FileManagerConfiguration());
		std::unique_ptr<FileManager> create(const std::filesystem::path &path) const override;

		const config::FileManagerConfiguration& getConfiguration() const;
		config::FileManagerConfiguration& getConfiguration();
		void setConfiguration(const config::FileManagerConfiguration &configuration);
	private:
		config::FileManagerConfiguration configuration;
	};


	class SharedConfigFileManagerFactory : public FileManagerFactory {
	public:
		explicit SharedConfigFileManagerFactory(const config::FileManagerConfiguration &configuration = config::FileManagerConfiguration());
		explicit SharedConfigFileManagerFactory(const std::shared_ptr<config::FileManagerConfiguration> &configuration);
		std::unique_ptr<FileManager> create(const std::filesystem::path &path) const override;

		std::shared_ptr<const config::FileManagerConfiguration> getConfiguration() const;
		std::shared_ptr<config::FileManagerConfiguration> getConfiguration();
	private:
		std::shared_ptr<config::FileManagerConfiguration> configuration;
	};
}
