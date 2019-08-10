#include "ASFMetadataScanner.hpp"
#include <tag/except/FileParseException.hpp>
#include <tag/priv/read_util.hpp>
#include <fstream>
namespace fs = std::filesystem;

namespace tag::scanner {
    ContainerFormat ASFMetadataScanner::getAssociatedContainerFormat() const noexcept {
        return ContainerFormat::WindowsMediaAudio;
    }

    void ASFMetadataScanner::appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                                             std::istream &readStream, std::uint64_t fileSize) const {
		if (fileSize >= 28 && priv::readAndEquals(readStream, priv::headers::ASF_HEADER_GUID))
			tagContainerLocations.emplace_back(TagContainerFormat::ASFMetadata, 0,
                                               priv::readLongLittleEndianNumber(readStream));
	}
}	