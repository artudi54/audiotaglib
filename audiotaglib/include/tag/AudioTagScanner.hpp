#pragma once

#include "AudioContainerFormat.hpp"
#include "AudioTagInformation.hpp"
#include "AudioTagProcessorBase.hpp"
#include <filesystem>
#include <memory>
#include <vector>
namespace tag::scanner {

	using AudioTagPos = std::pair<AudioTagFormat, std::uint64_t>;
	using AudioTagPosVector = std::vector<AudioTagPos>;

	AudioTagFormat toFormat(const AudioTagPosVector &tagPositions) noexcept;



    class AudioTagScanner : public base::AudioTagProcessorBase {
    public:
        virtual ~AudioTagScanner() {}
        virtual AudioTagPosVector getTagPositions(const std::filesystem::path &filePath) const = 0;
		virtual bool isFormatSpecific() const noexcept = 0;
		/////
		 void appendAudioTagInformation(std::vector<AudioTagInformation> &information, const std::filesystem::path &filePath) const {
			 AudioTagPosVector poss = getTagPositions(filePath);
			 for (auto &x : poss) {
				 AudioTagInformation inf(x.first, x.second, 0);
				 information.push_back(inf);
			 }
		 }
		virtual AudioContainerFormat getSpecificFormatStr() const { return AudioContainerFormat::Invalid; }
    };
	using SharedTagScanner = std::shared_ptr<AudioTagScanner>;
	using SharedTagScannerVector = std::vector<SharedTagScanner>;
}

