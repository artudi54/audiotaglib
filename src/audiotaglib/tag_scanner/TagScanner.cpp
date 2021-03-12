#include "TagScanner.hpp"
#include <fstream>
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
        common::ReadStream readStream(filePath);
        try {
            appendTagContainerLocations(tagContainerLocations, readStream);
        }
        catch (except::StreamParseException &exc) {
            throw except::FileParseException(filePath, exc);
        }
        catch (std::ios::failure &exc) {
            throw except::FileParseException(filePath, readStream.getPosition(),
                                             except::FileParseException::PositionType::Offset);
        }
    }

    void TagScanner::appendTagContainerLocations(std::vector<TagContainerLocation> &tagContainerLocations,
                                                 common::ReadStream &readStream) const {
        readStream.setPosition(0, common::ReadStream::Offset::BEGIN);
        appendTagContainerLocationsImpl(tagContainerLocations, readStream);
    }
}
