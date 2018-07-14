#pragma once

#include <tag/AudioContainerFormat.hpp>
#include <tag/AudioTagInformation.hpp>
#include <tag/except/FileNotReadableException.hpp>
#include <filesystem>
#include <memory>
#include <vector>
#include <fstream>

namespace tag::scanner {

	using AudioTagPos = std::pair<AudioTagFormat, std::uint64_t>;
	using AudioTagPosVector = std::vector<AudioTagPos>;

	
	[[deprecated("This will be removed soon")]] AudioTagFormat toFormat(const AudioTagPosVector &tagPositions) noexcept;



    class AudioTagScanner {
    public:
        virtual ~AudioTagScanner() {}
		[[deprecated("This will be removed soon")]] virtual AudioTagPosVector getTagPositions(const std::filesystem::path &filePath) const;
		virtual void appendAudioTagInformation(AudioTagInformationVector &informationVector,
											   const std::filesystem::path &filePath) const = 0;
		virtual AudioContainerFormat getSpecificFormat() const = 0;
	protected:
		static std::pair<std::uintmax_t, std::ifstream>
			   getValidatedSizeAndStream(const std::filesystem::path &filePath);
    };
	using SharedTagScanner = std::shared_ptr<AudioTagScanner>;
	using SharedTagScannerVector = std::vector<SharedTagScanner>;
}

