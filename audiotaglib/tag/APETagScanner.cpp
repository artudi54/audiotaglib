#include "APETagScanner.hpp"
namespace fs = std::filesystem;

namespace tag::scanner {
	//todo: mark header for v2 version instead of header
	AudioTagPosVector APETagScanner::getTagPositions(const fs::path & filePath) const {
		std::error_code dummy;

		AudioTagPosVector positions;

		std::uintmax_t size = fs::file_size(filePath, dummy);
		std::ifstream readStream(filePath, std::ios::in | std::ios::binary);
		if (size == -1 || !readStream.is_open())
			return positions;

		if (size >= 32 && readAndEquals(readStream, Headers::APE))
			positions.emplace_back(AudioTagFormat::APEv2, std::uint64_t(readStream.tellg()) - 8);
		
		else if (size >= 32 && readStream.seekg(-32, std::ios::end)
			&& readAndEquals(readStream, Headers::APE)) {
			AudioTagFormat format = getVersionFromHeader(readStream);
			positions.emplace_back(format, std::uint64_t(readStream.tellg()) - 12);
		}
		
		else if (size >= 160 && readStream.seekg(-160, std::ios::end)
			&& readAndEquals(readStream, Headers::APE)) {
			AudioTagFormat format = getVersionFromHeader(readStream);
			positions.emplace_back(format, std::uint64_t(readStream.tellg()) - 12);
		}

		return positions;
	}


	bool APETagScanner::isFormatSpecific() const noexcept {
		return false;
	}


	AudioTagFormat APETagScanner::getVersionFromHeader(std::istream & readStream) {
		int version = readLittleEndianSize(readStream);
		if (version == 1000)
			return AudioTagFormat::APEv1;
		else
			return AudioTagFormat::APEv2;
	}
}