#pragma once
#include <audiotaglib/priv/headers.hpp>
#include <istream>

namespace audiotaglib::priv::ogg {
    class Header {
    public:
        const ByteArray<4>& getId() const;
        std::uint8_t getVersion() const;
        std::uint8_t getFlags() const;
        std::uint32_t getPageSequenceNumber() const;
        std::uint8_t getSegmentsCount() const;
        std::uint32_t getPageSize() const;
        bool isContinuation() const;
        bool isBeggining() const;
        bool isEnd() const;
        bool isValid() const;
        static Header readHeader(std::istream &readStream);

        static const std::uint32_t HEADER_SIZE = 27;
    private:
        ByteArray<4> id;
        std::uint8_t version;
        std::uint8_t flags;
        std::uint32_t pageSequenceNumber;
        std::uint8_t segmentsCount;
        std::uint32_t pageSize;
    };
}