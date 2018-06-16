#pragma once
#include "AudioTagScanner.hpp"
#include <fstream>


namespace tag::scanner {
	class ASFMetadataScanner : public AudioTagScanner {
	public:
		virtual AudioTagPosVector getTagPositions(const std::filesystem::path &filePath) const override;
		virtual bool isFormatSpecific() const noexcept override;
	};
}