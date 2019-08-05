#include "AudioFileInformation.hpp"
#include <tag/except/FileNotFoundException.hpp>
#include <tag/except/FileNotReadableException.hpp>
#include <tag/scanner/TagScannerProvider.hpp>
#include <fstream>
using namespace std::literals;
namespace fs = std::filesystem;


namespace tag {
    static void validateFileWithThrow(const fs::path & filePath) {
        std::error_code dummy;

        if (!fs::exists(filePath, dummy))
            throw except::FileNotFoundException(filePath);

        std::ifstream testStream(filePath, std::ios::in);
        bool open = testStream.is_open();
        testStream.close();

        if (!open)
            throw except::FileNotReadableException(filePath);
    }

	AudioFileInformation::AudioFileInformation(const fs::path & filePath, const config::ScanConfiguration &scanConfiguration)
    try : filePath(filePath)
		, modificationTime()
		, containerFormat(util::containerFormatByExtension(filePath))
		, audioTagLocations() {
		validateFileWithThrow(filePath);
		modificationTime = fs::last_write_time(filePath);
		audioTagLocations.reserve(8);
		scanFormats(scanConfiguration);
	}
	catch(fs::filesystem_error &) {
	    throw except::FileNotReadableException(filePath);
    }

	AudioFileInformation::AudioFileInformation(fs::path && filePath, const config::ScanConfiguration &scanConfiguration)
		: filePath(std::move(filePath))
		, modificationTime()
		, containerFormat(util::containerFormatByExtension(filePath))
		, audioTagLocations() {
		validateFileWithThrow(filePath);
		audioTagLocations.reserve(8);
		scanFormats(scanConfiguration);
	}


	const std::filesystem::path & AudioFileInformation::getFilePath() const noexcept {
		return filePath;
	}


	ContainerFormat AudioFileInformation::getContainerFormat() const noexcept {
		return containerFormat;
	}

	std::string AudioFileInformation::getContainerFormatString() const noexcept {
		return string::toString(getContainerFormat());
	}

	AudioTagFormat AudioFileInformation::getAudioTagFormat() const noexcept {
		AudioTagFormat tagFormat = AudioTagFormat::None;
		for (auto tagInformation : audioTagLocations)
			tagFormat |= tagInformation.getTagFormat();
		return tagFormat;
	}

	std::string AudioFileInformation::getAudioTagFormatString() const {
		return string::toString(getAudioTagFormat());
	}

	const std::vector<AudioTagLocation>& AudioFileInformation::getAudioTagLocations() const {
		return audioTagLocations;
	}


	void AudioFileInformation::scanFormats(const config::ScanConfiguration &scanConfiguration) {
		const auto& scanners = scanner::TagScannerProvider::getScanners(containerFormat, scanConfiguration);
		for (const auto& scanner : scanners) {

			std::size_t beforeSize = audioTagLocations.size();
			scanner->appendAudioTagInformation(audioTagLocations, filePath);
			std::size_t afterSize = audioTagLocations.size();

			if (beforeSize != afterSize && scanner->getAssociatedContainerFormat() != ContainerFormat::Unspecified) {
                containerFormat = scanner->getAssociatedContainerFormat();
				break;
			}
		}

		if (containerFormat == ContainerFormat::Invalid && !audioTagLocations.empty())
            containerFormat = ContainerFormat::Unspecified;
	}

    bool AudioFileInformation::update(const config::ScanConfiguration &scanConfiguration) {
	    try {
            fs::file_time_type newModTime = fs::last_write_time(filePath);
            if (newModTime != modificationTime) {
                modificationTime = newModTime;
                audioTagLocations.clear();
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
