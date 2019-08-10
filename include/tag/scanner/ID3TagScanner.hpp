#pragma once
#include <tag/scanner/TagScanner.hpp>

namespace tag::scanner {
    class ID3TagScanner : public TagScanner {
    public:
        virtual ContainerFormat getAssociatedContainerFormat() const noexcept override;
    protected:
        virtual void appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                                     std::istream &readStream, std::uint64_t fileSize) const override;
    };
}

