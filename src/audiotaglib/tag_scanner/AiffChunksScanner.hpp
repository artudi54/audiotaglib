#pragma once
#include <audiotaglib/tag_scanner/TagScanner.hpp>

namespace audiotaglib::tag_scanner {
	class AiffChunksScanner : public TagScanner {
	public:
        [[nodiscard]] ContainerFormat getAssociatedContainerFormat() const noexcept override;
    protected:
        void appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                             common::ReadStream &readStream) const override;
	private:
        static void findID3Chunk(std::vector<TagContainerLocation> & tagContainerLocations,
                                 common::ReadStream &readStream, std::uint32_t size);
	};
}