#include "ID3TagScanner.hpp"
namespace fs = std::filesystem;

namespace tag::scanner {

	AudioTagPosVector ID3TagScanner::getTagPositions(const fs::path &filePath) const {
        std::error_code dummy;

		AudioTagPosVector positions;

		std::uintmax_t size = fs::file_size(filePath, dummy);
        std::ifstream readStream(filePath, std::ios::in | std::ios::binary);
		if (size == -1 || !readStream.is_open())
			return positions;



		if (size >= 128 && readStream.seekg(-128, std::ios::end) && readAndEquals(readStream, Headers::ID3_V1))
			positions.emplace_back(AudioTagFormat::ID3v1, std::uint64_t(readStream.tellg()) - 3);

		if (size >= 10 && readStream.seekg(0, std::ios::beg) && readAndEquals(readStream, Headers::ID3_V2))
			positions.emplace_back(getVersionFromHeader(readStream), 0);

		if (size >= 138 && readStream.seekg(-138, std::ios::end) && readAndEquals(readStream, Headers::ID3_V2R)) {
			unsigned size = readBigEndianSize(readStream);
			positions.emplace_back(AudioTagFormat::ID3v24, std::uint64_t(readStream.tellg()) - 17 - size);
		}
        return positions;
    }


	bool ID3TagScanner::isFormatSpecific() const noexcept {
		return false;
	}


	AudioTagFormat ID3TagScanner::getVersionFromHeader(std::istream & readStream) {
		int version = readStream.get();
		if (version == 2)
			return AudioTagFormat::ID3v22;
		else if (version == 3)
			return AudioTagFormat::ID3v23;
		else
			return AudioTagFormat::ID3v24;
	}
}
