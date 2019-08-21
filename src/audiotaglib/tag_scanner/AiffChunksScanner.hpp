#pragma once
#include <audiotaglib/tag_scanner/TagScanner.hpp>

namespace audiotaglib::tag_scanner {
	class AiffChunksScanner : public TagScanner {
	public:
        virtual ContainerFormat getAssociatedContainerFormat() const noexcept override;
    protected:
        virtual void appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                                     std::istream &readStream, std::uint64_t fileSize) const override;
	private:
        static void findID3Chunk(std::vector<TagContainerLocation> & tagContainerLocations, std::istream & readStream, std::uint32_t size);
	};
}