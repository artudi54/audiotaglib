#include "read_util.hpp"
#include <regex>
#include <codecvt>
#include <boost/algorithm/string.hpp>
#include <tag/string/genres.hpp>
using namespace std::literals;

namespace tag::priv {
/* MSVC fix
 * this is a fix for missing codecvt facet templates
 * char16_t overload is missing
 */
#ifdef _MSC_VER
	using char16_type = std::int16_t;
#else
	using char16_type = char16_t;
#endif


	std::string readUtf8(std::istream & readStream, std::uint64_t length) {
		std::string result;
		if (length != std::uint64_t(-1)) {
			result.resize(length);
			readStream.read(result.data(), length);
			truncatePadding(result);
		} else
			std::getline(readStream, result, '\0');
		return result;
	}

	std::string readLatin1(std::istream & readStream, std::uint64_t length) {
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

	std::string readUtf16BOM(std::istream & readStream, std::uint64_t length) {
		if (length == 0 || length == 1) {
			readStream.seekg(length, std::ios::cur);
			return std::string();
		}

		if (length != std::uint64_t(-1))
			length -= 2;

		char first = readStream.get();
		char second = readStream.get();

		if (first == char(0xFF) && second == char(0xFE)) //little endian
			return readUtf16LE(readStream, length);
		else if (first == char(0xFE) && second == char(0xFF)) //big endian
			return readUtf16BE(readStream, length);

		if (length != std::uint64_t(-1))
			readStream.seekg(length);
		return std::string();
	}

	std::string readUtf16BE(std::istream & readStream, std::uint64_t length) {
		std::string rawData;
		if (length != std::uint64_t(-1)) {
			rawData.resize(length);
			readStream.read(rawData.data(), length);
			if (length % 2 == 1)
				rawData.pop_back();
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
		std::wstring_convert<std::codecvt_utf8_utf16<char16_type>, char16_type> converter;
		return converter.to_bytes(
			reinterpret_cast<char16_type*>(unicodeString.data()),
			reinterpret_cast<char16_type*>(unicodeString.data() + unicodeString.size())
		);
	}

	std::string readUtf16LE(std::istream & readStream, std::uint64_t length) {
		std::string rawData;
		if (length != std::uint64_t(-1)) {
			rawData.resize(length);
			readStream.read(rawData.data(), length);
			if (length % 2 == 1)
				rawData.pop_back();
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
		std::wstring_convert<std::codecvt_utf8_utf16<char16_type >, char16_type > converter;
		return converter.to_bytes(
			reinterpret_cast<char16_type*>(unicodeString.data()),
			reinterpret_cast<char16_type*>(unicodeString.data() + unicodeString.size())
		);
	}



	void truncatePadding(std::string & string) {
		while (!string.empty() && (string.back() == '\0' || string.back() == ' '))
			string.pop_back();
	}



	std::string processMultiString(const std::string_view &text) {
		static const std::regex PATTERN(R"(\s*[;,/\\0\\]\s*)"s);
		std::string newText;
		newText.reserve(text.size());
		std::regex_replace(std::back_inserter(newText), text.begin(), text.end(), PATTERN, "; "s);
		return newText;
	}

	//todo: add better splitting
	std::string processGenreString(std::string genres) {
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



	std::uint16_t readShortBigEndianNumber(std::istream &readStream) {
		std::array<std::byte, 2> readSize;
		readStream.read(reinterpret_cast<char*>(readSize.data()), 2);
		return
			(unsigned(readSize[0]) << 8) | unsigned(readSize[1]);
	}

	std::uint32_t readThreeBytesBigEndianNumber(std::istream & readStream) {
		std::array<std::byte, 3> readSize;
		readStream.read(reinterpret_cast<char*>(readSize.data()), 3);
		return
			(unsigned(readSize[0]) << 16) | (unsigned(readSize[1]) << 8) |
			(unsigned(readSize[2]));
	}

	unsigned readBigEndianNumber(std::istream &readStream) {
		std::array<std::byte, 4> readSize;
		readStream.read(reinterpret_cast<char*>(readSize.data()), 4);
		return
			(unsigned(readSize[0]) << 24) | (unsigned(readSize[1]) << 16) |
			(unsigned(readSize[2]) << 8) | (unsigned(readSize[3]));
	}

	unsigned readSyncSafeBigEndianNumber(std::istream &readStream) {
		std::array<std::byte, 4> readSize;
		readStream.read(reinterpret_cast<char*>(readSize.data()), 4);

		return (unsigned(readSize[0]) << 21) | (unsigned(readSize[1]) << 14) |
			   (unsigned(readSize[2]) << 7)  | (unsigned(readSize[3]));
	}



	std::uint16_t readShortLittleEndianNumber(std::istream &readStream) {
		std::array<std::byte, 2> readSize;
		readStream.read(reinterpret_cast<char*>(readSize.data()), 2);
		return
			(std::uint16_t(readSize[0])) | (std::uint16_t(readSize[1]) << 8);
	}

	unsigned readLittleEndianNumber(std::istream &readStream) {
		std::array<std::byte, 4> readSize;
		readStream.read(reinterpret_cast<char*>(readSize.data()), 4);
		return
			(unsigned(readSize[0]))		  | (unsigned(readSize[1]) << 8) |
			(unsigned(readSize[2]) << 16) | (unsigned(readSize[3]) << 24);
	}

	std::uint64_t readLongLittleEndianNumber(std::istream &readStream) {
		std::array<std::byte, 8> readSize;
		readStream.read(reinterpret_cast<char*>(readSize.data()), 8);
		return
			(std::uint64_t(readSize[0]))		  | (std::uint64_t(readSize[1]) << 8ull) |
			(std::uint64_t(readSize[2]) << 16ull) | (std::uint64_t(readSize[3]) << 24ull) |
			(std::uint64_t(readSize[4]) << 32ull) | (std::uint64_t(readSize[5]) << 40ull) |
			(std::uint64_t(readSize[6]) << 48ull) | (std::uint64_t(readSize[7]) << 56ull);
	}
}