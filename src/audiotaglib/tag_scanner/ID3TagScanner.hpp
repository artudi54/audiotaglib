#pragma once
#include <audiotaglib/tag_scanner/TagScanner.hpp>

namespace audiotaglib::tag_scanner {
    class ID3TagScanner : public TagScanner {
    protected:
        void appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                             common::ReadStream &readStream) const override;
    private:
        static void appendFrontV2(std::vector<TagContainerLocation> &tagContainerLocations, common::ReadStream &readStream);
        static void appendV1(std::vector<TagContainerLocation> &tagContainerLocations, common::ReadStream &readStream);
        static void appendBackV2(std::vector<TagContainerLocation> &tagContainerLocations, common::ReadStream &readStream);
        };
}

