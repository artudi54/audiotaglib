#pragma once
#include <audiotaglib/tag_scanner/TagScanner.hpp>

namespace audiotaglib::tag_scanner {
	class RiffInfoScanner : public TagScanner {
	public:
        virtual ContainerFormat getAssociatedContainerFormat() const noexcept override;
    protected:
        virtual void appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                                     std::istream &readStream, std::uint64_t fileSize) const override;
	private:
        static void findAndScanTagChunks(std::vector<TagContainerLocation> & tagContainerLocations, std::istream & readStream, std::uint32_t riffChunkSize);
	};
}

