#include "ContainerMetadata.hpp"
#include <audiotaglib/except/FileNotFoundException.hpp>
#include <audiotaglib/except/FileNotReadableException.hpp>
#include <audiotaglib/tag_scanner/CompositeTagsScanner.hpp>
#include <fstream>
using namespace std::literals;
namespace fs = std::filesystem;


namespace audiotaglib {
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

	ContainerMetadata::ContainerMetadata(const fs::path & filePath, const config::ScanConfiguration &scanConfiguration)
    try : filePath(filePath)
		, modificationTime()
		, containerFormat(util::containerFormatByExtension(filePath))
		, tagContainerLocations() {
		validateFileWithThrow(filePath);
		modificationTime = fs::last_write_time(filePath);
		tagContainerLocations.reserve(8);
		scanFormats(scanConfiguration);
	}
	catch(fs::filesystem_error &) {
	    throw except::FileNotReadableException(filePath);
    }

	ContainerMetadata::ContainerMetadata(fs::path && filePath, const config::ScanConfiguration &scanConfiguration)
		: filePath(std::move(filePath))
		, modificationTime()
		, containerFormat(util::containerFormatByExtension(filePath))
		, tagContainerLocations() {
		validateFileWithThrow(filePath);
		tagContainerLocations.reserve(8);
		scanFormats(scanConfiguration);
	}


	const std::filesystem::path & ContainerMetadata::getFilePath() const noexcept {
		return filePath;
	}


	ContainerFormat ContainerMetadata::getContainerFormat() const noexcept {
		return containerFormat;
	}

	std::string ContainerMetadata::getContainerFormatString() const noexcept {
		return string::toString(getContainerFormat());
	}

	TagContainerFormat ContainerMetadata::getTagContainerFormats() const noexcept {
		TagContainerFormat tagFormat = TagContainerFormat::None;
		for (auto tagInformation : tagContainerLocations)
			tagFormat |= tagInformation.getTagContainerFormat();
		return tagFormat;
	}

	std::string ContainerMetadata::getTagContainerFormatsString() const {
		return string::toString(getTagContainerFormats());
	}

	const std::vector<TagContainerLocation>& ContainerMetadata::getTagContainerLocations() const {
		return tagContainerLocations;
	}

    bool ContainerMetadata::update(const config::ScanConfiguration &scanConfiguration) {
	    try {
            fs::file_time_type newModTime = fs::last_write_time(filePath);
            if (newModTime != modificationTime) {
                modificationTime = newModTime;
                tagContainerLocations.clear();
                scanFormats(scanConfiguration);
                return true;
            }
            return false;
        }
        catch (fs::filesystem_error &) {
            throw except::FileNotReadableException(filePath);
        }
    }

    void ContainerMetadata::scanFormats(const config::ScanConfiguration &scanConfiguration) {
        tag_scanner::CompositeTagsScanner scanner(containerFormat, scanConfiguration);
        tagContainerLocations = scanner.getTagContainerLocations(filePath);
    }
}


namespace audiotaglib::util {
	TagContainerFormat fileTagContainerFormats(const std::filesystem::path & filePath) {
		return ContainerMetadata(filePath).getTagContainerFormats();
	}
}
