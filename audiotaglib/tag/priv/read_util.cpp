#include "read_util.hpp"

namespace tag::priv {

	unsigned readSyncSafeBigEndianSize(std::istream & readStream) {
		std::array<std::byte, 4> readSize;
		readStream.read(reinterpret_cast<char*>(readSize.data()), 4);

		return (unsigned(readSize[0]) << 21) | (unsigned(readSize[1]) << 14) |
			   (unsigned(readSize[2]) << 7)  | (unsigned(readSize[3]));
	}







	unsigned readLittleEndianSize(std::istream & readStream) {
		std::array<std::byte, 4> readSize;
		readStream.read(reinterpret_cast<char*>(readSize.data()), 4);
		return
			(unsigned(readSize[0]))		  | (unsigned(readSize[1]) << 8) |
			(unsigned(readSize[2]) << 16) | (unsigned(readSize[3]) << 24);
	}


	std::uint64_t readLongLittleEndianSize(std::istream & readStream) {
		std::array<std::byte, 8> readSize;
		readStream.read(reinterpret_cast<char*>(readSize.data()), 8);
		return
			(std::uint64_t(readSize[0]))		  | (std::uint64_t(readSize[1]) << 8ull) |
			(std::uint64_t(readSize[2]) << 16ull) | (std::uint64_t(readSize[3]) << 24ull) |
			(std::uint64_t(readSize[4]) << 32ull) | (std::uint64_t(readSize[5]) << 40ull) |
			(std::uint64_t(readSize[6]) << 48ull) | (std::uint64_t(readSize[7]) << 56ull);
	}
}