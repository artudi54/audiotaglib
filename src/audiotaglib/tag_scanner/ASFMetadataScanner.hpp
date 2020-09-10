#pragma once
#include <audiotaglib/tag_scanner/TagScanner.hpp>

namespace audiotaglib::tag_scanner {
	class ASFMetadataScanner : public TagScanner {
	public:
        ContainerFormat getAssociatedContainerFormat() const noexcept override;
    protected:
        void appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                                     common::ReadStream &readStream) const override;
	};
}