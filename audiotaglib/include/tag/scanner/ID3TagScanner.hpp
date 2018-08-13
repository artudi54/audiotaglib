#pragma once
#include <tag/scanner/AudioTagScanner.hpp>
#include <tag/except/FileParseException.hpp>

namespace tag::scanner {
    class ID3TagScanner : public AudioTagScanner {
    public:
		virtual void appendAudioTagInformation(AudioTagInformationVector &informationVector,
											   const std::filesystem::path &filePath) const;
		virtual AudioContainerFormat getSpecificFormat() const;
	private:
		void appendFrontV2(AudioTagInformationVector &informationVector, std::uintmax_t size,
						   std::istream &readStream, const std::filesystem::path &filePath) const;
		void appendV1(AudioTagInformationVector &informationVector, std::uintmax_t size, std::istream &readStream) const;
		void appendBackV2(AudioTagInformationVector &informationVector, std::uintmax_t size,
						  std::istream &readStream, const std::filesystem::path &filePath) const;
    };
}

