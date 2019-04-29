#pragma once
#include <tag/AudioContainerFormat.hpp>
#include <tag/AudioTagInformation.hpp>
#include <filesystem>
#include <memory> // TODO: remove after removing aliases
#include <vector>

namespace tag::scanner {
    class TagScanner {
    public:
		virtual ~TagScanner();
		AudioTagInformationVector getAudioTagInformation(const std::filesystem::path &filePath) const;
		virtual void appendAudioTagInformation(AudioTagInformationVector &informationVector,
											       const std::filesystem::path &filePath) const = 0;
		virtual AudioContainerFormat getSpecificFormat() const = 0;
    };
	using SharedTagScanner = std::unique_ptr<TagScanner>;
	using SharedTagScannerVector = std::vector<SharedTagScanner>;
}
