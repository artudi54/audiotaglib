#pragma once
#include <tag/AudioContainerFormat.hpp>
#include <tag/AudioTagLocation.hpp>
#include <filesystem>
#include <vector>

namespace tag::scanner {
    // TODO: rename to tag_scanner (future container_scanner feature)
    class TagScanner {
    public:
		virtual ~TagScanner();
        std::vector<AudioTagLocation> getAudioTagInformation(const std::filesystem::path &filePath) const;
		void appendAudioTagInformation(std::vector<AudioTagLocation> &informationVector,
                                           const std::filesystem::path &filePath) const;
		virtual AudioContainerFormat getSpecificFormat() const noexcept = 0;
    protected:
        virtual void appendAudioTagInformationImpl(std::vector<AudioTagLocation> &informationVector,
                                                        std::istream &readStream, std::uint64_t fileSize) const = 0;
    };
}
