#pragma once
#include <tag/scanner/TagScanner.hpp>

namespace tag::scanner {
	class ASFMetadataScanner : public TagScanner {
	public:
		void appendAudioTagInformation(AudioTagInformationVector &informationVector,
									   const std::filesystem::path &filePath) const override;
		AudioContainerFormat getSpecificFormat() const override;
	};
}