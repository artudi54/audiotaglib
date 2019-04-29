#pragma once
#include <tag/scanner/TagScanner.hpp>

namespace tag::scanner {
    class ID3TagScanner : public TagScanner {
    public:
		void appendAudioTagInformation(AudioTagInformationVector &informationVector,
									   const std::filesystem::path &filePath) const override;
		AudioContainerFormat getSpecificFormat() const override;
	private:
		void appendFrontV2(AudioTagInformationVector &informationVector, std::uintmax_t size,
						   std::istream &readStream, const std::filesystem::path &filePath) const;
		void appendV1(AudioTagInformationVector &informationVector, std::uintmax_t size, std::istream &readStream) const;
		void appendBackV2(AudioTagInformationVector &informationVector, std::uintmax_t size,
						  std::istream &readStream, const std::filesystem::path &filePath) const;
    };
}

