#pragma once
#include <tag/scanner/TagScanner.hpp>

namespace tag::scanner {
    class OggScanner : public TagScanner {
        virtual void appendAudioTagInformation(AudioTagInformationVector &informationVector,
                                                   const std::filesystem::path &filePath) const override;
        virtual AudioContainerFormat getSpecificFormat() const override;
    };
}