#include "ASFMetadataScanner.hpp"
#include <audiotaglib/priv/headers.hpp>
namespace fs = std::filesystem;

namespace audiotaglib::tag_scanner {
    void ASFMetadataScanner::appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                                             common::ReadStream &readStream) const {
		if (readStream.getSize() >= 28 && readStream.readHeaderAndEquals(priv::headers::ASF_HEADER_GUID))
			tagContainerLocations.emplace_back(TagContainerFormat::ASFMetadata, 0, readStream.readLongLittleEndianNumber());
	}
}	