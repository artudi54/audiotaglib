#include "Header.hpp"
#include <audiotaglib/priv/read_util.hpp>

// TODO: move all headers to common package
namespace audiotaglib::priv::ogg {
    static const std::uint8_t CONTINUATION_FLAG = 0x01;
    static const std::uint8_t BEGGINNING_FLAG = 0x02;
    static const std::uint8_t END_FLAG = 0x04;

    const ByteArray<4> &Header::getId() const {
        return id;
    }

    std::uint8_t Header::getVersion() const {
        return version;
    }

    std::uint8_t Header::getFlags() const {
        return flags;
    }

    std::uint32_t Header::getPageSequenceNumber() const {
        return pageSequenceNumber;
    }

    std::uint8_t Header::getSegmentsCount() const {
        return segmentsCount;
    }

    std::uint32_t Header::getPageSize() const {
        return pageSize;
    }

    bool Header::isContinuation() const {
        return flags & CONTINUATION_FLAG;
    }

    bool Header::isBeggining() const {
        return flags & BEGGINNING_FLAG;
    }

    bool Header::isEnd() const {
        return flags & END_FLAG;
    }

    Header Header::readHeader(std::istream &readStream) {
        Header header{};
        header.id = priv::readHeader<4>(readStream);
        header.version = static_cast<std::uint8_t>(readStream.get());
        header.flags = static_cast<std::uint8_t>(readStream.get());
        readStream.seekg(12, std::ios::cur);
        header.pageSequenceNumber = priv::readLittleEndianNumber(readStream);
        readStream.seekg(4, std::ios::cur);
        header.segmentsCount = static_cast<std::uint8_t>(readStream.get());
        header.pageSize = 0;
        for (std::uint32_t i = 0; i < header.segmentsCount; ++i)
            header.pageSize += static_cast<std::uint8_t>(readStream.get());
        return header;
    }

    bool Header::isValid() const {
        return id == headers::OGG;
    }
}
