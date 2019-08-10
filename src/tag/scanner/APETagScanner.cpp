#include "APETagScanner.hpp"
#include <tag/except/StreamParseException.hpp>
#include <tag/priv/read_util.hpp>
#include <tag/priv/ape/Header.hpp>
#include <fstream>
namespace fs = std::filesystem;

namespace tag::scanner {
    static void appendFront(std::vector<TagContainerLocation> & tagContainerLocations, std::istream & readStream,
                            std::uint64_t fileSize) {
        if (fileSize >= 32 && priv::readAndEquals(readStream, priv::headers::APE)) {
            readStream.seekg(0, std::ios::beg);
            priv::ape::Header header = priv::ape::Header::readHeader(readStream);

            if (header.tagVersion() == TagContainerFormat::None)
                throw except::StreamParseException(8);
            if (header.totalTagSize() > fileSize)
                throw except::StreamParseException(12);

            tagContainerLocations.emplace_back(TagContainerFormat::APEv2, header.size, header.totalTagSize());
        }
    }

    static void appendBack(std::vector<TagContainerLocation> & tagContainerLocations, std::istream & readStream,
                           std::uint64_t fileSize) {
        if (fileSize >= 32 && readStream.seekg(-32, std::ios::end)
            && priv::readAndEquals(readStream, priv::headers::APE)) {
            readStream.seekg(-8, std::ios::cur);
            priv::ape::Header header = priv::ape::Header::readHeader(readStream);

            if (header.tagVersion() == TagContainerFormat::None)
                throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 24);
            if (header.totalTagSize() > fileSize)
                throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 20);

            tagContainerLocations.emplace_back(header.tagVersion(), std::uint64_t(readStream.tellg()) - 32,
                                               header.totalTagSize());
        }

        else if (fileSize >= 160 && readStream.seekg(-160, std::ios::end)
                 && priv::readAndEquals(readStream, priv::headers::APE)) {
            readStream.seekg(-8, std::ios::cur);
            priv::ape::Header header = priv::ape::Header::readHeader(readStream);

            if (header.tagVersion() == TagContainerFormat::None)
                throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 24);
            if (header.totalTagSize() > fileSize)
                throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 20);

            tagContainerLocations.emplace_back(header.tagVersion(), std::uint64_t(readStream.tellg()) - 32,
                                               header.totalTagSize());
        }
    }

    ContainerFormat APETagScanner::getAssociatedContainerFormat() const noexcept {
        return ContainerFormat::Unknown;
    }

    void APETagScanner::appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                                        std::istream &readStream, std::uint64_t fileSize) const {
		appendFront(tagContainerLocations, readStream, fileSize);
		appendBack(tagContainerLocations, readStream, fileSize);
	}
}