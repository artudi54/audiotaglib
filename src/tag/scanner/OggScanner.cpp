#include "OggScanner.hpp"
#include <tag/except/StreamParseException.hpp>
#include <tag/priv/headers.hpp>
#include <tag/priv/read_util.hpp>
#include <tag/priv/ogg/Header.hpp>

namespace tag::scanner {
    ContainerFormat OggScanner::getAssociatedContainerFormat() const noexcept {
        return ContainerFormat::Unknown;
    }

    void OggScanner::appendAudioTagInformationImpl(std::vector<AudioTagLocation> &informationVector,
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
        informationVector.emplace_back(AudioTagFormat::VorbisComments, headerOffset, static_cast<std::uint64_t>(readStream.tellg()));
    }
}

