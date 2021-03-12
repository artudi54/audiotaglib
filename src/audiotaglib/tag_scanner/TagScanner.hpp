#pragma once
#include <filesystem>
#include <vector>
#include <audiotaglib/ContainerFormat.hpp>
#include <audiotaglib/TagContainerLocation.hpp>
#include <audiotaglib/common/io/ReadStream.hpp>

namespace audiotaglib::tag_scanner {
    class TagScanner {
    public:
		virtual ~TagScanner();

        [[nodiscard]] std::vector<TagContainerLocation> getTagContainerLocations(const std::filesystem::path &filePath) const;
		void appendTagContainerLocations(std::vector<TagContainerLocation> &tagContainerLocations,
                                         const std::filesystem::path &filePath) const;
        void appendTagContainerLocations(std::vector<TagContainerLocation> &tagContainerLocations,
                                          common::ReadStream &readStream) const;

    protected:
        virtual void appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                                     common::ReadStream &readStream) const = 0;
    };
}
