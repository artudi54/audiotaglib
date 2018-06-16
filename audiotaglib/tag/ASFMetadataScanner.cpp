#include "ASFMetadataScanner.hpp"
namespace fs = std::filesystem;

namespace tag::scanner {
	AudioTagPosVector ASFMetadataScanner::getTagPositions(const fs::path & filePath) const {
		std::error_code dummy;

		AudioTagPosVector positions;

		std::uintmax_t size = fs::file_size(filePath, dummy);
		std::ifstream readStream(filePath, std::ios::in | std::ios::binary);
		if (size == -1 || !readStream.is_open())
			return positions;
		if (size >= 28  && readAndEquals(readStream, Headers::ASF_HEADER_GUID))
			positions.emplace_back(AudioTagFormat::ASFMetadata, 0);
		return positions;
	}

	bool ASFMetadataScanner::isFormatSpecific() const noexcept {
		return true;
	}

}
