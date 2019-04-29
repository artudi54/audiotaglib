#pragma once
#include <tag/scanner/TagScanner.hpp>

namespace tag::scanner {
	class FLACScanner : public TagScanner {
		virtual void appendAudioTagInformation(AudioTagInformationVector &informationVector,
									               const std::filesystem::path &filePath) const override;
		virtual AudioContainerFormat getSpecificFormat() const override;
	};
}