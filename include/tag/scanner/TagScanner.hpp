#pragma once
#include <tag/ContainerFormat.hpp>
#include <tag/TagContainerLocation.hpp>
#include <filesystem>
#include <vector>

namespace tag::scanner {
    // TODO: rename to tag_scanner (future container_scanner feature)
    class TagScanner {
    public:
		virtual ~TagScanner();
        std::vector<TagContainerLocation> getTagContainerLocations(const std::filesystem::path &filePath) const;
		void appendTagContainerLocations(std::vector<TagContainerLocation> &tagContainerLocations,
                                         const std::filesystem::path &filePath) const;
		virtual ContainerFormat getAssociatedContainerFormat() const noexcept = 0;
    protected:
        virtual void appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                                     std::istream &readStream, std::uint64_t fileSize) const = 0;
    };
}
