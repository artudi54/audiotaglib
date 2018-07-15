#pragma once

#include <array>
#include <cstddef>
#include <string>
#include <codecvt>
#include <istream>
#include <locale>
#include <regex>
#include <boost/algorithm/string.hpp>
#include <tag/string/genres.hpp>
using namespace std::literals;

namespace tag::base {

class AudioTagProcessorBase {
protected:
    struct Headers {
        static constexpr std::array<std::byte, 3> ID3_V1 =
        { std::byte('T'), std::byte('A'), std::byte('G') };
        static constexpr std::array<std::byte, 3> ID3_V2 =
        { std::byte('I'), std::byte('D'), std::byte('3') };
        static constexpr std::array<std::byte, 3> ID3_V2R =
        { std::byte('3'), std::byte('D'), std::byte('I') };

        static constexpr std::array<std::byte, 8 > APE = {
            std::byte('A'),
            std::byte('P'),
            std::byte('E'),
            std::byte('T'),
            std::byte('A'),
            std::byte('G'),
            std::byte('E'),
            std::byte('X')
        };

        static constexpr std::array<std::byte, 4> RIFF_CHUNK =
        { std::byte('R'), std::byte('I'), std::byte('F'), std::byte('F') };
        static constexpr std::array<std::byte, 4> WAVE =
        { std::byte('W'), std::byte('A'), std::byte('V'), std::byte('E') };

        static constexpr std::array<std::byte, 4> LIST_CHUNK
        { std::byte('L'), std::byte('I'), std::byte('S'), std::byte('T') };

        static constexpr std::array<std::byte, 4> ID3_CHUNK =
        { std::byte('I'), std::byte('D'), std::byte('3'), std::byte(' ') };

        static constexpr std::array<std::byte, 4> INFO_CHUNK =
        { std::byte('I'), std::byte('N'), std::byte('F'), std::byte('O') };

		static constexpr std::array<std::byte, 16> ASF_HEADER_GUID = {
			std::byte(0x30), std::byte(0x26), std::byte(0xb2), std::byte(0x75),
			std::byte(0x8e), std::byte(0x66), std::byte(0xcf), std::byte(0x11),
			std::byte(0xa6), std::byte(0xd9), std::byte(0x00), std::byte(0xaa),
			std::byte(0x00), std::byte(0x62), std::byte(0xce), std::byte(0x6c)
		};
		static constexpr std::array<std::byte, 16> ASF_CONTENT_DESCRIPTION_GUID = {
			std::byte(0x33), std::byte(0x26), std::byte(0xB2), std::byte(0x75),
			std::byte(0x8E), std::byte(0x66), std::byte(0xCF), std::byte(0x11),
			std::byte(0xA6), std::byte(0xD9), std::byte(0x00), std::byte(0xAA),
			std::byte(0x00), std::byte(0x62), std::byte(0xCE), std::byte(0x6C)
		};
		static constexpr std::array<std::byte, 16> ASF_EXTENDED_CONTENT_DESCRIPTION_GUID = {
			std::byte(0x40), std::byte(0xA4), std::byte(0xD0), std::byte(0xD2),
			std::byte(0x07), std::byte(0xE3), std::byte(0xD2), std::byte(0x11),
			std::byte(0x97), std::byte(0xF0), std::byte(0x00), std::byte(0xA0),
			std::byte(0xC9), std::byte(0x5E), std::byte(0xA8), std::byte(0x50)
		};
    };

    template < std::size_t N >
    inline static bool readAndEquals(std::istream &readStream, const std::array<std::byte, N> &HEADER) {
        std::array<std::byte, N> readHeader = {};
        readStream.read(reinterpret_cast<char*>(readHeader.data()), N);
        return readHeader == HEADER;
    }

    template < std::size_t N>
    inline static std::array<std::byte, N> readHeader(std::istream &readStream) {
        std::array<std::byte, N> header = {};
        readStream.read(reinterpret_cast<char*>(header.data()), N);
        return header;
    }

    inline static std::string readUtf8(std::istream &readStream, std::streamsize length = -1) {
        std::string result;
        if (length != -1) {
            result.resize(length);
            readStream.read(result.data(), length);
            truncatePadding(result);
        } else
            std::getline(readStream, result, '\0');
        return result;
    }


    inline static std::string readLatin1(std::istream &readStream, std::streamsize length = -1) {
        std::string latin1 = readUtf8(readStream, length);
        std::string utf;
        utf.reserve(3 * latin1.size() / 2);
        for (std::size_t i = 0; i < latin1.size(); ++i) {
            if (latin1[i] < 0x80) {
                utf.push_back(latin1[i]);
            } else {
                utf.push_back(0xc0 | (latin1[i] & 0xc0) >> 6);
                utf.push_back(0x80 | (latin1[i] & 0x3f));
            }
        }
        return utf;
    }

    inline static std::string readUtf16BOM(std::istream &readStream, std::streamsize length = -1) {
        std::string rawData;
        if (length != -1) {
            rawData.resize(length);
            readStream.read(rawData.data(), length);
            while (rawData.size() >= 2 && rawData.back() == '\0' && rawData[rawData.size() - 2] == '\0') {
                rawData.pop_back();
                rawData.pop_back();
            }
        } else {
            for (
                int first = readStream.get(), second = readStream.get();
                first > 0 || second > 0;
                first = readStream.get(), second = readStream.get()) {

                rawData.push_back(first);
                rawData.push_back(second);
            }
        }
        if (rawData.size() < 2)
            return std::string();

        std::u16string unicodeString;
        unicodeString.reserve(rawData.size() / 2);

        if (rawData[0] == char(0xFF) && rawData[1] == char(0xFE)) //little endian
            for (std::size_t i = 3; i < rawData.size(); i += 2)
                unicodeString.push_back(rawData[i - 1] | (rawData[i] << 8));
        else if (rawData[0] == char(0xFE) && rawData[1] == char(0xFF)) //big endian
            for (std::size_t i = 3; i < rawData.size(); i += 2)
                unicodeString.push_back((rawData[i - 1] << 8) | rawData[i]);

        std::wstring_convert<std::codecvt_utf8_utf16<std::int16_t >, std::int16_t > converter;
        return converter.to_bytes(
                   reinterpret_cast<std::int16_t *>(unicodeString.data()),
                   reinterpret_cast<std::int16_t *>(unicodeString.data() + unicodeString.size())
               );
    }

	inline static std::string readUtf16BE(std::istream &readStream, std::streamsize length = -1) {
		std::string rawData;
		if (length != -1) {
			rawData.resize(length);
			readStream.read(rawData.data(), length);
			while (!rawData.empty() && rawData.back() == '\0' && rawData[rawData.size() - 2] == '\0') {
				rawData.pop_back();
				rawData.pop_back();
			}
		} else {
			for (
				char first = readStream.get(), second = readStream.get();
				first != '\0' || second != '\0';
				first = readStream.get(), second = readStream.get()) {

				rawData.push_back(first);
				rawData.push_back(second);
			}
		}

		std::u16string unicodeString;
		unicodeString.reserve(rawData.size() / 2);

		for (std::size_t i = 1; i < rawData.size(); i += 2)
			unicodeString.push_back((rawData[i - 1] << 8) | rawData[i]);
		std::wstring_convert<std::codecvt_utf8_utf16<std::int16_t>, std::int16_t> converter;
		return converter.to_bytes(
			reinterpret_cast<std::int16_t*>(unicodeString.data()),
			reinterpret_cast<std::int16_t*>(unicodeString.data() + unicodeString.size())
		);
	}

	inline static std::string readUtf16LE(std::istream &readStream, std::streamsize length = -1) {
		std::string rawData;
		if (length != -1) {
			rawData.resize(length);
			readStream.read(rawData.data(), length);
			while (!rawData.empty() && rawData.back() == '\0' && rawData[rawData.size() - 2] == '\0') {
				rawData.pop_back();
				rawData.pop_back();
			}
		} else {
			for (
				char first = readStream.get(), second = readStream.get();
				first != '\0' || second != '\0';
				first = readStream.get(), second = readStream.get()) {

				rawData.push_back(first);
				rawData.push_back(second);
			}
		}

		std::u16string unicodeString;
		unicodeString.reserve(rawData.size() / 2);

		for (std::size_t i = 1; i < rawData.size(); i += 2)
			unicodeString.push_back((rawData[i] << 8) | rawData[i - 1]);
		std::wstring_convert<std::codecvt_utf8_utf16<std::int16_t >, std::int16_t > converter;
		return converter.to_bytes(
			reinterpret_cast<std::int16_t*>(unicodeString.data()),
			reinterpret_cast<std::int16_t*>(unicodeString.data() + unicodeString.size())
		);
	}

    inline static void truncatePadding(std::string &string) {
        while (!string.empty() && (string.back() == '\0' || string.back() == ' '))
            string.pop_back();
    }

	inline static std::string processMultistring(const std::string &text) {
		static const std::regex PATTERN(R"(\s*[;,/\\0\\]\s*)"s);

		std::string newText;
		newText.reserve(text.size());
		std::regex_replace(std::back_inserter(newText), text.begin(), text.end(), PATTERN, "; "s);
		return newText;
	}

	inline static std::string processGenreString(std::string genres) {
		static const std::regex PATTERN(R"((?:^|[^\(])\((\d+)\))");

		std::smatch match;
		while (std::regex_search(genres, match, PATTERN)) {
			try {
				std::size_t index = std::stol(match[1].str());
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







	inline static std::uint16_t readShortLittleEndianSize(std::istream &readStream) {
		std::array<std::byte, 2> readSize;
		readStream.read(reinterpret_cast<char*>(readSize.data()), 2);
		return
			(std::uint16_t(readSize[0])) | (std::uint16_t(readSize[1]) << 8);
	}

    inline static unsigned readLittleEndianSize(std::istream &readStream) {
        std::array<std::byte, 4> readSize;
        readStream.read(reinterpret_cast<char*>(readSize.data()), 4);
        return
            (unsigned(readSize[0])) | (unsigned(readSize[1]) << 8) |
            (unsigned(readSize[2]) << 16) | (unsigned(readSize[3]) << 24);
    }

	inline static std::uint64_t readLongLittleEndianSize(std::istream &readStream) {
		std::array<std::byte, 8> readSize;
		readStream.read(reinterpret_cast<char*>(readSize.data()), 8);
		return
			(std::uint64_t(readSize[0])) | (std::uint64_t(readSize[1]) << 8ull) |
			(std::uint64_t(readSize[2]) << 16ull) | (std::uint64_t(readSize[3]) << 24ull) |
			(std::uint64_t(readSize[4]) << 32ull) | (std::uint64_t(readSize[5]) << 40ull) |
			(std::uint64_t(readSize[6]) << 48ull) | (std::uint64_t(readSize[7]) << 56ull);
	}

    inline static unsigned readBigEndianSize(std::istream &readStream) {
        std::array<std::byte, 4> readSize;
        readStream.read(reinterpret_cast<char*>(readSize.data()), 4);
        return
            (unsigned(readSize[0]) << 24) | (unsigned(readSize[1]) << 16) |
            (unsigned(readSize[2]) << 8) | (unsigned(readSize[3]));
    }

	inline static unsigned readSyncSafeBigEndianSize(std::istream & readStream) {
		std::array<std::byte, 4> readSize;
		readStream.read(reinterpret_cast<char*>(readSize.data()), 4);
		return (unsigned(readSize[0]) << 21) | (unsigned(readSize[1]) << 14) |
			(unsigned(readSize[2]) << 7) | (unsigned(readSize[3]));
	}
};
}
