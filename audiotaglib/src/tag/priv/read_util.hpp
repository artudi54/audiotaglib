#pragma once
#include <string>
#include <istream>
#include <tag/priv/headers.hpp>

namespace tag::priv {
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

	std::string readUtf8(std::istream &readStream, std::uint64_t length = -1);
	std::string readLatin1(std::istream &readStream, std::uint64_t length = -1);
	std::string readUtf16BOM(std::istream &readStream, std::uint64_t length = -1);
	std::string readUtf16BE(std::istream &readStream, std::uint64_t length = -1);
	std::string readUtf16LE(std::istream &readStream, std::uint64_t length = -1);
	
	void truncatePadding(std::string &string);



	std::string processMultistring(const std::string &text);
	std::string processGenreString(std::string genres);


	std::uint16_t readShortBigEndianSize(std::istream &readStream);
	unsigned readBigEndianSize(std::istream &readStream);
	unsigned readSyncSafeBigEndianSize(std::istream & readStream);

	unsigned readLittleEndianSize(std::istream &readStream);
	std::uint64_t readLongLittleEndianSize(std::istream &readStream);
}