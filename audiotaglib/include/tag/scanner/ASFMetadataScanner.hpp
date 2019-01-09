#pragma once
#include <tag/scanner/AudioTagScanner.hpp>
#include <fstream>

namespace tag::scanner {
	class ASFMetadataScanner : public AudioTagScanner {
	public:
		void appendAudioTagInformation(AudioTagInformationVector &informationVector,
									   const std::filesystem::path &filePath) const override;
		AudioContainerFormat getSpecificFormat() const override;
	};
}