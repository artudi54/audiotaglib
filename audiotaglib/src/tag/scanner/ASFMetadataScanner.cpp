#include "ASFMetadataScanner.hpp"
#include <tag/except/FileParseException.hpp>
#include <tag/priv/read_util.hpp>
#include <fstream>
namespace fs = std::filesystem;

namespace tag::scanner {
	void ASFMetadataScanner::appendAudioTagInformation(AudioTagInformationVector& informationVector,
													   const std::filesystem::path & filePath) const {
		auto[size, readStream] = priv::validatedSizeAndStream(filePath);

		if (size >= 28 && priv::readAndEquals(readStream, priv::headers::ASF_HEADER_GUID))
			informationVector.emplace_back(AudioTagFormat::ASFMetadata, 0,
                                           priv::readLongLittleEndianNumber(readStream));
	}

	AudioContainerFormat ASFMetadataScanner::getSpecificFormat() const {
		return AudioContainerFormat::WindowsMediaAudio;
	}
}	