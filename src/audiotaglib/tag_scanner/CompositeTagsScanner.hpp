#pragma once
#include <audiotaglib/tag_scanner/TagScanner.hpp>
#include <audiotaglib/config/ScanConfiguration.hpp>

namespace audiotaglib::tag_scanner {
    class CompositeTagsScanner : public TagScanner {
    public:
        CompositeTagsScanner(ContainerFormat containerFormat, const config::ScanConfiguration &scanConfiguration);
    protected:
        void appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                             common::ReadStream &readStream) const override;
    private:
        const std::vector<std::unique_ptr<TagScanner>>& scanners;
    };
}