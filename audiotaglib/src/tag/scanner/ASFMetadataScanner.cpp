#include "ASFMetadataScanner.hpp"
#include <tag/except/FileParseException.hpp>
#include <tag/priv/read_util.hpp>
#include <fstream>
namespace fs = std::filesystem;

namespace tag::scanner {
    AudioContainerFormat ASFMetadataScanner::getSpecificFormat() const {
        return AudioContainerFormat::WindowsMediaAudio;
    }

    void ASFMetadataScanner::appendAudioTagInformationImpl(AudioTagInformationVector &informationVector,
                                                                std::istream &readStream, std::uint64_t fileSize) const {
		if (fileSize >= 28 && priv::readAndEquals(readStream, priv::headers::ASF_HEADER_GUID))
			informationVector.emplace_back(AudioTagFormat::ASFMetadata, 0,
                                           priv::readLongLittleEndianNumber(readStream));
	}
}	