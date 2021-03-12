#include "OggScanner.hpp"
#include <audiotaglib/except/StreamParseException.hpp>
#include <audiotaglib/priv/headers.hpp>
#include <audiotaglib/priv/ogg/Header.hpp>

namespace audiotaglib::tag_scanner {
    void OggScanner::appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                                     common::ReadStream &readStream) const {
        std::uint32_t pageNumber = 0;

        // skip information header
        priv::ogg::Header header = priv::ogg::Header::readHeader(readStream.getNativeStream());
        if (!header.isValid())
            return;
        readStream.setPosition(header.getPageSize(), common::ReadStream::Offset::CURRENT);
        ++pageNumber;

        // location for information vector
        std::uint64_t headerOffset = readStream.getPosition();

        // vorbis comments header
        header = priv::ogg::Header::readHeader(readStream.getNativeStream());
        if (!header.isValid())
            throw except::StreamParseException(readStream.getPosition() - priv::ogg::Header::HEADER_SIZE);
        readStream.setPosition(header.getPageSize(), common::ReadStream::Offset::CURRENT);
        ++pageNumber;

        // continuations
        while (readStream.getRemainingSize() >= 0 && !header.isEnd()) {
            header = priv::ogg::Header::readHeader(readStream.getNativeStream());
            if (priv::ogg::Header::HEADER_SIZE + header.getPageSize() > readStream.getRemainingSize())
                throw except::StreamParseException(readStream.getPosition());
            if (!header.isValid())
                throw except::StreamParseException(readStream.getPosition() - priv::ogg::Header::HEADER_SIZE);
            if (pageNumber != header.getPageSequenceNumber())
                throw except::StreamParseException(readStream.getPosition() - priv::ogg::Header::HEADER_SIZE + 16);
            readStream.setPosition(header.getPageSize(), common::ReadStream::Offset::CURRENT);
            ++pageNumber;
        }
        tagContainerLocations.emplace_back(TagContainerFormat::VorbisComments, headerOffset, readStream.getPosition());
    }
}

