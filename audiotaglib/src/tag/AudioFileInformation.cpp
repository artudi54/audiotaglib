
#include <tag/AudioFileInformation.hpp>

#include "AudioFileInformation.hpp"
using namespace std::literals;
namespace fs = std::filesystem;


namespace tag {
	AudioFileInformation::AudioFileInformation(const fs::path & filePath, const config::ScanConfiguration &scanConfiguration)
    try : filePath(filePath)
		, modificationTime()
		, audioContainerFormat(util::fileContainerFormat(filePath))
		, audioTagInformation() {
		validateFileWithThrow();
		modificationTime = fs::last_write_time(filePath);
		audioTagInformation.reserve(4);
		scanFormats(scanConfiguration);
	}
	catch(fs::filesystem_error &) {
	    throw except::FileNotReadableException(filePath);
    }

	AudioFileInformation::AudioFileInformation(fs::path && filePath, const config::ScanConfiguration &scanConfiguration)
		: filePath(std::move(filePath)), audioContainerFormat(util::fileContainerFormat(filePath)), audioTagInformation() {
		validateFileWithThrow();
		audioTagInformation.reserve(4);
		scanFormats(scanConfiguration);
	}


	const std::filesystem::path & AudioFileInformation::getFilePath() const noexcept {
		return filePath;
	}

	const std::filesystem::file_time_type& AudioFileInformation::getModificationTime() const {
		return modificationTime;
	}


	AudioContainerFormat AudioFileInformation::getAudioContainerFormat() const noexcept {
		return audioContainerFormat;
	}

	std::string AudioFileInformation::getAudioContainerFormatString() const noexcept {
		return string::toString(getAudioContainerFormat());
	}

	AudioTagFormat AudioFileInformation::getAudioTagFormat() const noexcept {
		AudioTagFormat tagFormat = AudioTagFormat::None;
		for (auto tagInformation : audioTagInformation)
			tagFormat |= tagInformation.getTagFormat();
		return tagFormat;
	}

	std::string AudioFileInformation::getAudioTagFormatString() const {
		return string::toString(getAudioTagFormat());
	}

	const std::vector<AudioTagInformation>& AudioFileInformation::getAudioTagInformation() const {
		return audioTagInformation;
	}


	void AudioFileInformation::validateFileWithThrow() {
		std::error_code dummy;

		if (!fs::exists(filePath, dummy))
			throw except::FileNotFoundException(filePath);

		std::ifstream testStream(filePath, std::ios::in);
		bool open = testStream.is_open();
		testStream.close();

		if (!open)
			throw except::FileNotReadableException(filePath);
	}

	void AudioFileInformation::scanFormats(const config::ScanConfiguration &scanConfiguration) {
		const auto& scanners = scanner::StaticScannerFactory::getScanners(audioContainerFormat, scanConfiguration);
		for (const auto& scanner : scanners) {

			std::size_t beforeSize = audioTagInformation.size();
			scanner->appendAudioTagInformation(audioTagInformation, filePath);
			std::size_t afterSize = audioTagInformation.size();

			if (beforeSize != afterSize && scanner->getSpecificFormat() != AudioContainerFormat::Unspecified) {
				audioContainerFormat = scanner->getSpecificFormat();
				break;
			}
		}

		if (audioContainerFormat == AudioContainerFormat::Invalid && !audioTagInformation.empty())
			audioContainerFormat = AudioContainerFormat::Unspecified;
	}

    bool AudioFileInformation::update(const config::ScanConfiguration &scanConfiguration) {
	    try {
            fs::file_time_type newModTime = fs::last_write_time(filePath);
            if (newModTime != modificationTime) {
                modificationTime = newModTime;
                audioTagInformation.clear();
                scanFormats(scanConfiguration);
                return true;
            }
            return false;
        }
        catch (fs::filesystem_error &) {
            throw except::FileNotReadableException(filePath);
        }
    }
}


namespace tag::util {
	AudioTagFormat fileTagFormat(const std::filesystem::path & filePath) {
		return AudioFileInformation(filePath).getAudioTagFormat();
	}
}
