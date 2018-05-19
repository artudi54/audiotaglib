#include "WaveInfoScanner.hpp"
namespace fs = std::filesystem;

namespace tag::scanner {

	AudioTagPosVector WaveInfoScanner::getTagPositions(const fs::path & filePath) const {
		std::error_code dummy;

		std::uintmax_t size = fs::file_size(filePath, dummy);
		std::ifstream readStream(filePath, std::ios::in | std::ios::binary);
		if (size == -1 || !readStream.is_open())
			return AudioTagPosVector();

		if (size >= 44) {
			if (readAndEquals(readStream, Headers::RIFF)) {
				readStream.seekg(8, std::ios::beg);
				if (readAndEquals(readStream, Headers::WAVE))
					return findInfoChunkType(readStream, size - 12);
			}
		}
		return AudioTagPosVector();
	}

	bool WaveInfoScanner::isFormatSpecific() const noexcept {
		return true;
	}



	AudioTagPosVector WaveInfoScanner::findInfoChunkType(std::ifstream & readStream, std::uintmax_t size) const {
		unsigned leftChunkSize, totalChunkSize;
		AudioTagPosVector positions;

		while (size >= 4) {
			std::array<std::byte, 4> header = readHeader<4>(readStream);
			totalChunkSize = leftChunkSize = readLittleEndianSize(readStream);

			if (header == Headers::LIST_CHUNK && leftChunkSize >= 4) {
				leftChunkSize -= 4;
				if (readAndEquals(readStream, Headers::INFO_SUBCHUNK))
					positions.emplace_back(AudioTagFormat::WaveInfo, std::uint64_t(readStream.tellg()) - 8);
			} else if (header == Headers::ID3_CHUNK && leftChunkSize >= 10) {
				readStream.seekg(3, std::ios::cur);
				AudioTagFormat version = ID3TagScanner::getVersionFromHeader(readStream);
				positions.emplace_back(version, std::uint64_t(readStream.tellg()) - 4);
				leftChunkSize -= 4;
			}
			readStream.seekg(leftChunkSize, std::ios::cur);
			if (totalChunkSize + 8 > size)
				return positions;
			size -= totalChunkSize + 8;
		}
		return positions;
	}
}
