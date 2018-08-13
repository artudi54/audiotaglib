#pragma once
#include <tag/scanner/AudioTagScanner.hpp>
#include <fstream>

namespace tag::scanner {
	class ASFMetadataScanner : public AudioTagScanner {
	public:
		virtual void appendAudioTagInformation(AudioTagInformationVector &informationVector,
											   const std::filesystem::path &filePath) const;
		virtual AudioContainerFormat getSpecificFormat() const;
	};
}