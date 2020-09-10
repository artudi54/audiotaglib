#include "ReadStream.hpp"
#include <regex>
#include <boost/algorithm/string.hpp>
#include <audiotaglib/common/io/file_stream_utils.hpp>
#include <audiotaglib/string/genres.hpp>
namespace fs = std::filesystem;
using namespace std::literals;

namespace audiotaglib::common {


/* MSVC fix
 * this is a fix for missing codecvt facet templates
 * char16_t overload is missing
 */
#ifdef _MSC_VER
    using char16_type = std::int16_t;
#else
    using char16_type = char16_t;
#endif


    ReadStream::ReadStream(const fs::path &filePath)
        : stream()
        , size(0) {
        std::tie(stream, size) = validInputFileStreamWithSize(filePath);
    }

    std::istream &ReadStream::getNativeStream() {
        return stream;
    }


    std::uint64_t ReadStream::getSize() const {
        return size;
    }

    std::uint64_t ReadStream::getRemainingSize() {
        return size - static_cast<std::uint64_t>(stream.tellg());
    }


    std::uint64_t ReadStream::getPosition() {
        return static_cast<std::uint64_t>(stream.tellg());
    }

    void ReadStream::setPosition(std::uint32_t position, ReadStream::Offset direction) {
        setPosition(static_cast<std::uint64_t>(position), direction);
    }

    void ReadStream::setPosition(std::uint64_t position, ReadStream::Offset direction) {
        stream.seekg(static_cast<std::ios::off_type>(position), static_cast<std::ios::seekdir>(direction));
    }

    void ReadStream::setPosition(std::int32_t position, ReadStream::Offset direction) {
        setPosition(static_cast<std::int64_t>(position), direction);
    }

    void ReadStream::setPosition(std::int64_t position, ReadStream::Offset direction) {
        stream.seekg(static_cast<std::ios::off_type>(position), static_cast<std::ios::seekdir>(direction));
    }


    std::string ReadStream::readUtf8(std::uint64_t length) {
        std::string result;
        if (length != static_cast<std::uint64_t>(-1)) {
            result.resize(length);
            stream.read(result.data(), static_cast<std::streamsize>(length));
            truncatePadding(result);
        } else
            std::getline(stream, result, '\0');
        return result;
    }

    std::string ReadStream::readLatin1(std::uint64_t length) {
        std::string latin1 = readUtf8(length);
        std::string utf;
        utf.reserve(3 * latin1.size() / 2);
        for (char signedChar : latin1) {
            std::uint8_t unsignedChar = static_cast<std::uint8_t>(signedChar);
            if (static_cast<std::uint8_t>(unsignedChar) < 0x80) {
                utf.push_back(static_cast<char>(unsignedChar));
            } else {
                utf.push_back(static_cast<char>(0xc0u | (unsignedChar & 0xc0u) >> 6u));
                utf.push_back(static_cast<char>(0x80u | (unsignedChar & 0x3fu)));
            }
        }
        return utf;
    }

    std::string ReadStream::readUtf16BOM(std::uint64_t length) {
        static constexpr priv::ByteArray<2> BIG_ENDIAN_BOM = {std::byte(0xfe), std::byte(0xff)};
        static constexpr priv::ByteArray<2> LITTLE_ENDIAN_BOM = {std::byte(0xff), std::byte(0xfe)};

        if (length <= 1) {
            stream.seekg(static_cast<std::streamsize>(length), std::ios::cur);
            return std::string();
        }

        if (length != std::uint64_t(-1))
            length -= 2;

        priv::ByteArray<2> bom = readHeader<2>();

        if (bom == LITTLE_ENDIAN_BOM)
            return readUtf16LE(length);
        else if (bom == BIG_ENDIAN_BOM)
            return readUtf16BE(length);

        if (length != std::uint64_t(-1))
            stream.seekg(static_cast<std::streamsize>(length));
        return std::string();
    }

    // TODO optimise for architecture
    std::string ReadStream::readUtf16BE(std::uint64_t length) {
        std::string rawData = readRawUtf16Bytes(length);

        std::u16string unicodeString(rawData.size() / 2, '\0');
        for (std::size_t i = 1; i < rawData.size(); i += 2)
            unicodeString[i / 2] = static_cast<char16_t>((rawData[i - 1] << 8) | rawData[i]);

        std::wstring_convert<std::codecvt_utf8_utf16<char16_type>, char16_type> converter;
        return converter.to_bytes(
                reinterpret_cast<char16_type*>(unicodeString.data()),
                reinterpret_cast<char16_type*>(unicodeString.data() + unicodeString.size())
        );
    }

    // TODO optimise for architecture
    std::string ReadStream::readUtf16LE(std::uint64_t length) {
        std::string rawData = readRawUtf16Bytes(length);

        std::u16string unicodeString(rawData.size() / 2, '\0');
        for (std::size_t i = 1; i < rawData.size(); i += 2)
            unicodeString[i / 2] = static_cast<char16_t>((rawData[i] << 8) | rawData[i - 1]);

        std::wstring_convert<std::codecvt_utf8_utf16<char16_type>, char16_type> converter;
        return converter.to_bytes(
                reinterpret_cast<char16_type*>(unicodeString.data()),
                reinterpret_cast<char16_type*>(unicodeString.data() + unicodeString.size())
        );
    }


    std::uint8_t ReadStream::readOneByteNumber() {
        return static_cast<std::uint8_t>(stream.get());
    }

    // TODO optimise for architecture
    std::uint16_t ReadStream::readShortBigEndianNumber() {
        std::array<std::byte, 2> readSize;
        stream.read(reinterpret_cast<char*>(readSize.data()), 2);
        return std::uint16_t((std::uint16_t(readSize[0]) << 8u) | std::uint16_t(readSize[1]));
    }

    // TODO optimise for architecture
    std::uint32_t ReadStream::readThreeBytesBigEndianNumber() {
        std::array<std::byte, 3> readSize;
        stream.read(reinterpret_cast<char*>(readSize.data()), 3);
        return
                (std::uint32_t(readSize[0]) << 16u) | (std::uint32_t(readSize[1]) << 8u) |
                (std::uint32_t(readSize[2]));
    }

    // TODO optimise for architecture
    std::uint32_t ReadStream::readBigEndianNumber() {
        std::array<std::byte, 4> readSize;
        stream.read(reinterpret_cast<char*>(readSize.data()), 4);
        return
                (std::uint32_t(readSize[0]) << 24) | (std::uint32_t(readSize[1]) << 16) |
                (std::uint32_t(readSize[2]) << 8) | (std::uint32_t(readSize[3]));
    }

    // TODO optimise for architecture
    std::uint32_t ReadStream::readSyncSafeBigEndianNumber() {
        std::array<std::byte, 4> readSize;
        stream.read(reinterpret_cast<char*>(readSize.data()), 4);

        return (std::uint32_t(readSize[0]) << 21) | (std::uint32_t(readSize[1]) << 14) |
               (std::uint32_t(readSize[2]) << 7)  | (std::uint32_t(readSize[3]));
    }


    // TODO optimise for architecture
    std::uint16_t ReadStream::readShortLittleEndianNumber() {
        std::array<std::byte, 2> readSize;
        stream.read(reinterpret_cast<char*>(readSize.data()), 2);
        return std::uint16_t(std::uint16_t(readSize[0]) | (std::uint16_t(readSize[1]) << 8u));
    }

    // TODO optimise for architecture
    std::uint32_t ReadStream::readLittleEndianNumber() {
        std::array<std::byte, 4> readSize;
        stream.read(reinterpret_cast<char*>(readSize.data()), 4);
        return
                (std::uint32_t(readSize[0]))		  | (std::uint32_t(readSize[1]) << 8) |
                (std::uint32_t(readSize[2]) << 16) | (std::uint32_t(readSize[3]) << 24);
    }

    // TODO optimise for architecture
    std::uint64_t ReadStream::readLongLittleEndianNumber() {
        std::array<std::byte, 8> readSize;
        stream.read(reinterpret_cast<char*>(readSize.data()), 8);
        return
                (std::uint64_t(readSize[0]))		  | (std::uint64_t(readSize[1]) << 8ull) |
                (std::uint64_t(readSize[2]) << 16ull) | (std::uint64_t(readSize[3]) << 24ull) |
                (std::uint64_t(readSize[4]) << 32ull) | (std::uint64_t(readSize[5]) << 40ull) |
                (std::uint64_t(readSize[6]) << 48ull) | (std::uint64_t(readSize[7]) << 56ull);
    }


    std::string ReadStream::readRawUtf16Bytes(std::uint64_t length) {
        std::string rawData;
        if (length != std::uint64_t(-1)) {
            rawData.resize(length);
            stream.read(rawData.data(), static_cast<std::streamsize>(length));
            if (length % 2 == 1)
                rawData.pop_back();
            while (!rawData.empty() && rawData.back() == '\0' && rawData[rawData.size() - 2] == '\0') {
                rawData.pop_back();
                rawData.pop_back();
            }
        } else {
            for (char first = static_cast<char>(stream.get()), second = static_cast<char>(stream.get());
                 first != '\0' || second != '\0';
                 first = static_cast<char>(stream.get()), second = static_cast<char>(stream.get())) {
                rawData.push_back(first);
                rawData.push_back(second);
            }
        }
        return rawData;
    }


    void truncatePadding(std::string &string) {
        while (!string.empty() && (string.back() == '\0' || std::isspace(string.back())))
            string.pop_back();
    }

    std::string processMultiString(const std::string_view &text) {
        static const std::regex PATTERN(R"(\s*[;,/\\0\\]\s*)"s, std::regex::optimize);
        std::string newText;
        newText.reserve(text.size());
        std::regex_replace(std::back_inserter(newText), text.begin(), text.end(), PATTERN, "; "s);
        return newText;
    }

    std::string processGenreString(std::string genres) {
        static const std::regex PATTERN(R"((?:^|[^\(])\((\d+)\))"s, std::regex::optimize);

        boost::trim(genres);

        std::smatch match;
        while (std::regex_search(genres, match, PATTERN)) {
            try {
                std::size_t index = static_cast<std::size_t>(std::stol(match[1].str()));
                auto beg = std::prev(match[1].first), end = std::next(match[1].second);
                std::string replacement = (end == genres.end()) ?
                                          string::getGenreByIndex(index) : string::getGenreByIndex(index) + "; "s;
                genres.replace(beg, end, replacement);
            }
            catch (std::logic_error&) {
                genres.erase(std::prev(match[1].first), std::next(match[1].second));
            }
        }

        boost::replace_all(genres, "(("s, "("s);
        return genres;
    }
}