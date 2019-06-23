#pragma once
#include <tag/AudioContainerFormat.hpp>
#include <tag/AudioTagInformation.hpp>
#include <filesystem>
#include <vector>

namespace tag::scanner {
    class TagScanner {
    public:
		virtual ~TagScanner();
		AudioTagInformationVector getAudioTagInformation(const std::filesystem::path &filePath) const;
		void appendAudioTagInformation(AudioTagInformationVector &informationVector,
                                           const std::filesystem::path &filePath) const;
		virtual AudioContainerFormat getSpecificFormat() const noexcept = 0;
    protected:
        virtual void appendAudioTagInformationImpl(AudioTagInformationVector &informationVector,
                                                        std::istream &readStream, std::uint64_t fileSize) const = 0;
    };
}
