#include "TagScanner.hpp"
#include <fstream>
#include <audiotaglib/common/file_stream_utils.hpp>
#include <audiotaglib/except/FileNotReadableException.hpp>
#include <audiotaglib/except/FileParseException.hpp>
namespace fs = std::filesystem;

namespace audiotaglib::tag_scanner {
	TagScanner::~TagScanner() = default;

    std::vector<TagContainerLocation> TagScanner::getTagContainerLocations(const std::filesystem::path &filePath) const {
        std::vector<TagContainerLocation> informationVector;
        informationVector.reserve(8);
        appendTagContainerLocations(informationVector, filePath);
        return informationVector;
    }

    void TagScanner::appendTagContainerLocations(std::vector<TagContainerLocation> &tagContainerLocations,
                                                 const std::filesystem::path &filePath) const {
        auto [readStream, fileSize] = common::validInputFileStreamWithSize(filePath);

        try {
            appendTagContainerLocationsImpl(tagContainerLocations, readStream, fileSize);
        }
        catch (except::StreamParseException &exc) {
            throw except::FileParseException(filePath, exc);
        }
        catch (std::ios::failure &exc) {
            throw except::FileParseException(filePath, std::uint64_t(readStream.tellg()),
                                             except::FileParseException::PositionType::Offset);
        }
    }
}
