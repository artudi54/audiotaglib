#pragma once
#include <audiotaglib/tag_scanner/TagScanner.hpp>

namespace audiotaglib::tag_scanner {
    class ID3TagScanner : public TagScanner {
    public:
        [[nodiscard]] ContainerFormat getAssociatedContainerFormat() const noexcept override;
    protected:
        void appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                             std::istream &readStream, std::uint64_t fileSize) const override;
    private:
        static void appendFrontV2(std::vector<TagContainerLocation> &tagContainerLocations, std::istream &readStream, std::uint64_t fileSize);
        static void appendV1(std::vector<TagContainerLocation> &tagContainerLocations, std::istream &readStream, std::uint64_t fileSize);
        static void appendBackV2(std::vector<TagContainerLocation> &tagContainerLocations, std::istream &readStream, std::uint64_t fileSize);
        };
}

