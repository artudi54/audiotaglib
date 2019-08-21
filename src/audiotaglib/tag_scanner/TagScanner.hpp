#pragma once
#include <audiotaglib/ContainerFormat.hpp>
#include <audiotaglib/TagContainerLocation.hpp>
#include <filesystem>
#include <vector>

namespace audiotaglib::tag_scanner {
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
