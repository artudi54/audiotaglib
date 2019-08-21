#pragma once
#include <string>
#include <string_view>
#include <filesystem>
#include <istream>
#include <fstream>
#include <audiotaglib/priv/headers.hpp>

namespace audiotaglib::priv {
    //todo replace strings with string_view
	template < std::size_t N>
	inline ByteArray<N> readHeader(std::istream &readStream) {
		ByteArray<N> header = {};
		readStream.read(reinterpret_cast<char*>(header.data()), N);
		return header;
	}

	template < std::size_t N >
	inline bool readAndEquals(std::istream &readStream, const ByteArray<N> &HEADER) {
		ByteArray<N> readHeader = {};
		readStream.read(reinterpret_cast<char*>(readHeader.data()), N);
		return readHeader == HEADER;
	}


	std::string readUtf8(std::istream &readStream, std::uint64_t length = std::uint64_t(-1));
	std::string readLatin1(std::istream &readStream, std::uint64_t length = std::uint64_t(-1));
	std::string readUtf16BOM(std::istream &readStream, std::uint64_t length = std::uint64_t(-1));
	std::string readUtf16BE(std::istream &readStream, std::uint64_t length = std::uint64_t(-1));
	std::string readUtf16LE(std::istream &readStream, std::uint64_t length = std::uint64_t(-1));
	
	void truncatePadding(std::string &string);

	std::string processMultiString(const std::string_view &text);
	std::string processGenreString(std::string genres);

	std::uint16_t readShortBigEndianNumber(std::istream &readStream);
	std::uint32_t readThreeBytesBigEndianNumber(std::istream &readStream);
	std::uint32_t readBigEndianNumber(std::istream &readStream);
	std::uint32_t readSyncSafeBigEndianNumber(std::istream &readStream);

	std::uint16_t readShortLittleEndianNumber(std::istream &readStream);
	std::uint32_t readLittleEndianNumber(std::istream &readStream);
	std::uint64_t readLongLittleEndianNumber(std::istream &readStream);
}