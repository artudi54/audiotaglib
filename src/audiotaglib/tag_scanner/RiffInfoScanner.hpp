#pragma once
#include <audiotaglib/tag_scanner/TagScanner.hpp>

namespace audiotaglib::tag_scanner {
	class RiffInfoScanner : public TagScanner {
	public:
        [[nodiscard]] ContainerFormat getAssociatedContainerFormat() const noexcept override;
    protected:
        void appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                             common::ReadStream &readStream) const override;
	private:
        static void findAndScanTagChunks(std::vector<TagContainerLocation> & tagContainerLocations, common::ReadStream & readStream, std::uint32_t riffChunkSize);
	};
}

