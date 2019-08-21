#include "OggScanner.hpp"
#include <audiotaglib/except/StreamParseException.hpp>
#include <audiotaglib/priv/headers.hpp>
#include <audiotaglib/priv/read_util.hpp>
#include <audiotaglib/priv/ogg/Header.hpp>

namespace audiotaglib::scanner {
    ContainerFormat OggScanner::getAssociatedContainerFormat() const noexcept {
        return ContainerFormat::Unknown;
    }

    void OggScanner::appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                                     std::istream &readStream, std::uint64_t fileSize) const {
        std::uint64_t leftSize = fileSize;
        std::uint32_t pageNumber = 0;

        // skip information header
        priv::ogg::Header header = priv::ogg::Header::readHeader(readStream);
        if (!header.isValid())
            return;
        readStream.seekg(header.getPageSize(), std::ios::cur);
        leftSize -= priv::ogg::Header::HEADER_SIZE + header.getSegmentsCount() + header.getPageSize();
        ++pageNumber;

        // location for information vector
        std::uint64_t headerOffset = static_cast<std::uint64_t>(readStream.tellg());


        // vorbis comments header
        header = priv::ogg::Header::readHeader(readStream);
        if (!header.isValid())
            throw except::StreamParseException(
                    static_cast<std::uint64_t>(readStream.tellg()) - priv::ogg::Header::HEADER_SIZE);
        readStream.seekg(header.getPageSize(), std::ios::cur);
        leftSize -= priv::ogg::Header::HEADER_SIZE + header.getSegmentsCount() + header.getPageSize();
        ++pageNumber;

        // continuations
        while (leftSize >= 0 && !header.isEnd()) {
            header = priv::ogg::Header::readHeader(readStream);
            if (priv::ogg::Header::HEADER_SIZE + header.getPageSize() > leftSize)
                throw except::StreamParseException(static_cast<std::uint64_t>(readStream.tellg()));
            if (!header.isValid())
                throw except::StreamParseException(static_cast<std::uint64_t>(readStream.tellg()) - priv::ogg::Header::HEADER_SIZE);
            if (pageNumber != header.getPageSequenceNumber())
                throw except::StreamParseException(static_cast<std::uint64_t>(readStream.tellg()) - priv::ogg::Header::HEADER_SIZE + 16);
            readStream.seekg(header.getPageSize(), std::ios::cur);
            leftSize -= priv::ogg::Header::HEADER_SIZE + header.getSegmentsCount() + header.getPageSize();
            ++pageNumber;
        }
        tagContainerLocations.emplace_back(TagContainerFormat::VorbisComments, headerOffset, static_cast<std::uint64_t>(readStream.tellg()));
    }
}

