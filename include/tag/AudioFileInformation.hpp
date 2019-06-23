#pragma once
#include <tag/AudioContainerFormat.hpp>
#include <tag/AudioTagInformation.hpp>
#include <tag/config/ScanConfiguration.hpp>
#include <filesystem>
#include <vector>

namespace tag {
	class AudioFileInformation {
	public:
		explicit AudioFileInformation(const std::filesystem::path &filePath,
		                              const config::ScanConfiguration &scanConfiguration = config::ScanConfiguration());
		explicit AudioFileInformation(std::filesystem::path &&filePath,
                                      const config::ScanConfiguration &scanConfiguration = config::ScanConfiguration());
		
		const std::filesystem::path& getFilePath() const noexcept;

		AudioContainerFormat getAudioContainerFormat() const noexcept;
		std::string getAudioContainerFormatString() const noexcept;

		AudioTagFormat getAudioTagFormat() const noexcept;
		std::string getAudioTagFormatString() const;

		const std::vector<AudioTagInformation>& getAudioTagInformation() const;

		bool update(const config::ScanConfiguration &scanConfiguration = config::ScanConfiguration());
	private:
		void scanFormats(const config::ScanConfiguration &scanConfiguration);

		std::filesystem::path filePath;
		std::filesystem::file_time_type modificationTime;
		AudioContainerFormat audioContainerFormat;
		std::vector<AudioTagInformation> audioTagInformation;
	};
}

namespace tag::util {
	AudioTagFormat fileTagFormat(const std::filesystem::path &filePath);
}