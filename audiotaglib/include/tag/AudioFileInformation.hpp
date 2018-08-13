#pragma once
#include <tag/AudioContainerFormat.hpp>
#include <tag/AudioTagInformation.hpp>
#include <tag/scanner/StaticScannerFactory.hpp>
#include <tag/except/FileNotFoundException.hpp>
#include <tag/except/FileNotReadableException.hpp>
#include <filesystem>
#include <vector>

namespace tag {
	class AudioFileInformation {
	public:
		explicit AudioFileInformation(const std::filesystem::path &filePath, bool scanAll = false);
		explicit AudioFileInformation(std::filesystem::path &&filePath, bool scanAll = false);
		
		const std::filesystem::path& getFilePath() const noexcept;
		AudioContainerFormat getAudioContainerFormat() const noexcept;
		std::string getAudioContainerFormatString() const noexcept;
		AudioTagFormat getAudioTagFormat() const noexcept;
		std::string getAudioTagFormatString() const;
		const std::vector<AudioTagInformation>& getAudioTagInformation() const;
	private:
		void validateFileWithThrow();
		void scanFormats(bool scanAll);

		std::filesystem::path filePath;
		AudioContainerFormat audioContainerFormat;
		std::vector<AudioTagInformation> audioTagInformation;
	};
}

namespace tag::util {
	AudioTagFormat fileTagFormat(const std::filesystem::path &filePath);
}