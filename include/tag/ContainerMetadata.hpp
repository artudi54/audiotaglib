#pragma once
#include <tag/ContainerFormat.hpp>
#include <tag/AudioTagLocation.hpp>
#include <tag/config/ScanConfiguration.hpp>
#include <filesystem>
#include <vector>

namespace tag {
	class ContainerMetadata {
	public:
		explicit ContainerMetadata(const std::filesystem::path &filePath,
                                   const config::ScanConfiguration &scanConfiguration = config::ScanConfiguration());
		explicit ContainerMetadata(std::filesystem::path &&filePath,
                                   const config::ScanConfiguration &scanConfiguration = config::ScanConfiguration());
		
		const std::filesystem::path& getFilePath() const noexcept;

		ContainerFormat getContainerFormat() const noexcept;
		std::string getContainerFormatString() const noexcept;

		AudioTagFormat getAudioTagFormat() const noexcept;
		std::string getAudioTagFormatString() const;

		const std::vector<AudioTagLocation>& getAudioTagLocations() const;

		bool update(const config::ScanConfiguration &scanConfiguration = config::ScanConfiguration());
	private:
		void scanFormats(const config::ScanConfiguration &scanConfiguration);

		std::filesystem::path filePath;
		std::filesystem::file_time_type modificationTime;
		ContainerFormat containerFormat;
		std::vector<AudioTagLocation> audioTagLocations;
	};
}

namespace tag::util {
	AudioTagFormat fileTagFormat(const std::filesystem::path &filePath);
}