#pragma once
#include "AudioTagScanner.hpp"
#include <fstream>

namespace tag::scanner {
	
	class APETagScanner : public AudioTagScanner {
	public:
		virtual AudioTagPosVector getTagPositions(const std::filesystem::path &filePath) const override;
		virtual bool isFormatSpecific() const noexcept override;
	private:
		static AudioTagFormat getVersionFromHeader(std::istream &readStream);
	};

}

