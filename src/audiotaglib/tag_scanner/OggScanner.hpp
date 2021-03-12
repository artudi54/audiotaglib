#pragma once
#include <audiotaglib/tag_scanner/TagScanner.hpp>

namespace audiotaglib::tag_scanner {
    class OggScanner : public TagScanner {
    protected:
        void appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                             common::ReadStream &readStream) const override;
    };
}