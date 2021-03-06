#pragma once
#include <audiotaglib/ContainerFormat.hpp>
#include <audiotaglib/TagContainerLocation.hpp>
#include <audiotaglib/config/ScanConfiguration.hpp>
#include <filesystem>
#include <vector>

namespace audiotaglib {
	class ContainerMetadata {
	public:
		explicit ContainerMetadata(const std::filesystem::path &filePath,
                                   const config::ScanConfiguration &scanConfiguration = config::ScanConfiguration());
		explicit ContainerMetadata(std::filesystem::path &&filePath,
                                   const config::ScanConfiguration &scanConfiguration = config::ScanConfiguration());
		
		const std::filesystem::path& getFilePath() const noexcept;

		ContainerFormat getContainerFormat() const noexcept;
		std::string getContainerFormatString() const noexcept;

		TagContainerFormat getTagContainerFormats() const noexcept;
		std::string getTagContainerFormatsString() const;
		const std::vector<TagContainerLocation>& getTagContainerLocations() const;

		bool update(const config::ScanConfiguration &scanConfiguration = config::ScanConfiguration());
	private:
		void scanFormats(const config::ScanConfiguration &scanConfiguration);

		std::filesystem::path filePath;
		std::filesystem::file_time_type modificationTime;
		ContainerFormat containerFormat;
		std::vector<TagContainerLocation> tagContainerLocations;
	};
}

namespace audiotaglib::util {
	TagContainerFormat fileTagContainerFormats(const std::filesystem::path &filePath);
}