#pragma once
#include <tag/scanner/TagScanner.hpp>

namespace tag::scanner {
	class APETagScanner : public TagScanner {
	public:
        virtual AudioContainerFormat getSpecificFormat() const override;
    protected:
        virtual void appendAudioTagInformationImpl(AudioTagInformationVector &informationVector,
                                                        std::istream &readStream, std::uint64_t fileSize) const override;
	};

}

