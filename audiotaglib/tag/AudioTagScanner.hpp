#pragma once

#include "AudioTagFormat.hpp"
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
    };
	using SharedTagScanner = std::shared_ptr<AudioTagScanner>;
	using SharedTagScannerVector = std::vector<SharedTagScanner>;
}

