#include "TagScanner.hpp"
#include <audiotaglib/except/FileNotReadableException.hpp>
#include <audiotaglib/except/FileParseException.hpp>
#include <fstream>
namespace fs = std::filesystem;

namespace audiotaglib::scanner {
	TagScanner::~TagScanner() = default;

    std::vector<TagContainerLocation> TagScanner::getTagContainerLocations(const std::filesystem::path &filePath) const {
        std::vector<TagContainerLocation> informationVector;
        informationVector.reserve(8);
        appendTagContainerLocations(informationVector, filePath);
        return informationVector;
    }

    void TagScanner::appendTagContainerLocations(std::vector<TagContainerLocation> &tagContainerLocations,
                                                 const std::filesystem::path &filePath) const {
        std::error_code dummy;

        std::ifstream readStream(filePath, std::ios::in | std::ios::binary);
        std::uint64_t fileSize = fs::file_size(filePath, dummy);
        if (!readStream.is_open() || fileSize == std::uint64_t(-1))
            throw except::FileNotReadableException(filePath);

        try {
            readStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            appendTagContainerLocationsImpl(tagContainerLocations, readStream, fileSize);
        }
        catch (std::ios::failure &exc) {
            throw except::FileParseException(filePath, std::uint64_t(readStream.tellg()),
                                             except::FileParseException::PositionType::Offset);
        }
        catch (except::StreamParseException &exc) {
            throw except::FileParseException(filePath, exc);
        }
    }
}
