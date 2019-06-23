#pragma once
#include <tag/scanner/TagScanner.hpp>

namespace tag::scanner {
    class OggScanner : public TagScanner {
    public:
        virtual AudioContainerFormat getSpecificFormat() const noexcept override;
    protected:
        virtual void appendAudioTagInformationImpl(AudioTagInformationVector &informationVector,
                                                        std::istream &readStream, std::uint64_t fileSize) const override;
    };
}