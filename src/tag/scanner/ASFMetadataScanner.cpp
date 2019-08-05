#include "ASFMetadataScanner.hpp"
#include <tag/except/FileParseException.hpp>
#include <tag/priv/read_util.hpp>
#include <fstream>
namespace fs = std::filesystem;

namespace tag::scanner {
    ContainerFormat ASFMetadataScanner::getAssociatedContainerFormat() const noexcept {
        return ContainerFormat::WindowsMediaAudio;
    }

    void ASFMetadataScanner::appendAudioTagInformationImpl(std::vector<AudioTagLocation> &informationVector,
                                                                std::istream &readStream, std::uint64_t fileSize) const {
		if (fileSize >= 28 && priv::readAndEquals(readStream, priv::headers::ASF_HEADER_GUID))
			informationVector.emplace_back(AudioTagFormat::ASFMetadata, 0,
                                           priv::readLongLittleEndianNumber(readStream));
	}
}	