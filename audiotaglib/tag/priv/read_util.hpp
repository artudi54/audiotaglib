#pragma once
#include <array>
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
	


	unsigned readSyncSafeBigEndianSize(std::istream & readStream);

	unsigned readLittleEndianSize(std::istream &readStream);
	std::uint64_t readLongLittleEndianSize(std::istream &readStream);
}