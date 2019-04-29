#include "OggScanner.hpp"
#include <tag/except/StreamParseException.hpp>
#include <tag/priv/headers.hpp>
#include <tag/priv/read_util.hpp>
#include <tag/priv/ogg/Header.hpp>

namespace tag::scanner {
    //TODO: change stream exception to file exception
    void OggScanner::appendAudioTagInformation(AudioTagInformationVector &informationVector,
                                       const std::filesystem::path &filePath) const {
        auto[size, readStream] = priv::validatedSizeAndStream(filePath);
        uintmax_t leftSize = size;
        std::uint32_t pageNumber = 0;

        // skip information header
        priv::ogg::Header header = priv::ogg::Header::readHeader(readStream);
        if (!header.isValid())
            return;
        readStream.seekg(header.getPageSize(), std::ios::cur);
        leftSize -= priv::ogg::Header::HEADER_SIZE + header.getPageSize();
        ++pageNumber;

        // location for information vector
        std::uint64_t headerOffset = static_cast<std::uint64_t>(readStream.tellg());


        // starting vorbis comments header
        header = priv::ogg::Header::readHeader(readStream);
        if (!header.isValid())
            throw except::StreamParseException(static_cast<std::uint64_t>(readStream.tellg()) - priv::ogg::Header::HEADER_SIZE);
        if (!priv::readAndEquals(readStream, priv::headers::OGG_VORBIS))
            return;
        readStream.seekg(header.getPageSize() - priv::headers::OGG_VORBIS.size(), std::ios::cur);
        leftSize -= priv::ogg::Header::HEADER_SIZE + header.getPageSize() - priv::headers::OGG_VORBIS.size();
        ++pageNumber;

        // continuations
        while (leftSize >= priv::ogg::Header::HEADER_SIZE && !header.isContinuation()) {
            header = priv::ogg::Header::readHeader(readStream);
            if (priv::ogg::Header::HEADER_SIZE + header.getPageSize() > leftSize)
                throw except::StreamParseException(static_cast<std::uint64_t>(readStream.tellg()));
            if (!header.isValid())
                throw except::StreamParseException(static_cast<std::uint64_t>(readStream.tellg()) - priv::ogg::Header::HEADER_SIZE);
            if (pageNumber != header.getPageSequenceNumber())
                throw except::StreamParseException(static_cast<std::uint64_t>(readStream.tellg()) - priv::ogg::Header::HEADER_SIZE + 16);
            readStream.seekg(header.getPageSize(), std::ios::cur);
            leftSize -= priv::ogg::Header::HEADER_SIZE + header.getPageSize();
            ++pageNumber;
        }
        informationVector.emplace_back(AudioTagFormat::VorbisComments, headerOffset, static_cast<std::uint64_t>(readStream.tellg()));
    }


    AudioContainerFormat OggScanner::getSpecificFormat() const {
        return AudioContainerFormat::Unspecified;
    }
}

