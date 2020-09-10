#pragma once
#include <audiotaglib/tag_scanner/TagScanner.hpp>

namespace audiotaglib::tag_scanner {
	class APETagScanner : public TagScanner {
	public:
        [[nodiscard]] ContainerFormat getAssociatedContainerFormat() const noexcept override;
    protected:
        void appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                                     common::ReadStream &readStream) const override;
	private:
	    static void appendFront(std::vector<TagContainerLocation> & tagContainerLocations, common::ReadStream & readStream);
        static void appendBack(std::vector<TagContainerLocation> & tagContainerLocations, common::ReadStream& readStream);
	};

}

