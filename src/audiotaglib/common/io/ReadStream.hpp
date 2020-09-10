#pragma once
#include <filesystem>
#include <fstream>
#include <audiotaglib/priv/headers.hpp>

namespace audiotaglib::common {
    class ReadStream {
    public:
        enum class Offset {
            BEGIN = std::ios::beg,
            CURRENT = std::ios::cur,
            END = std::ios::end
        };
        explicit ReadStream(const std::filesystem::path& filePath);
        [[deprecated]] std::istream& getNativeStream();

        [[nodiscard]] std::uint64_t getSize() const;
        [[nodiscard]] std::uint64_t getRemainingSize();

        [[nodiscard]] std::uint64_t getPosition();
        void setPosition(std::uint32_t position, Offset direction = Offset::BEGIN);
        void setPosition(std::uint64_t position, Offset direction = Offset::BEGIN);
        void setPosition(std::int32_t position, Offset direction = Offset::BEGIN);
        void setPosition(std::int64_t position, Offset direction = Offset::BEGIN);

        template <std::size_t N>
        inline priv::ByteArray<N> readHeader() {
            priv::ByteArray<N> header = {};
            stream.read(reinterpret_cast<char*>(header.data()), N);
            return header;
        }

        template <std::size_t N>
        inline bool readHeaderAndEquals(const priv::ByteArray<N> &HEADER) {
            return readHeader<N>() == HEADER;
        }

        std::string readUtf8(std::uint64_t length = static_cast<std::uint64_t>(-1));
        std::string readLatin1(std::uint64_t length = static_cast<std::uint64_t>(-1));
        std::string readUtf16BOM(std::uint64_t length = static_cast<std::uint64_t>(-1));
        std::string readUtf16BE(std::uint64_t length = static_cast<std::uint64_t>(-1));
        std::string readUtf16LE(std::uint64_t length = static_cast<std::uint64_t>(-1));

        std::uint8_t readOneByteNumber();

        std::uint16_t readShortBigEndianNumber();
        std::uint32_t readThreeBytesBigEndianNumber();
        std::uint32_t readBigEndianNumber();
        std::uint32_t readSyncSafeBigEndianNumber();

        std::uint16_t readShortLittleEndianNumber();
        std::uint32_t readLittleEndianNumber();
        std::uint64_t readLongLittleEndianNumber();

    private:
        std::string readRawUtf16Bytes(std::uint64_t length);

        std::ifstream stream;
        std::uint64_t size;
    };

    void truncatePadding(std::string &string);
    std::string processMultiString(const std::string_view &text);
    std::string processGenreString(std::string genres);
}
