#pragma once
#include "AudioTagScanner.hpp"
#include "ID3TagScanner.hpp"
#include <fstream>

namespace tag::scanner {

	class RiffInfoScanner : public AudioTagScanner {
	public:
		virtual AudioTagPosVector getTagPositions(const std::filesystem::path &filePath) const override;
		virtual bool isFormatSpecific() const noexcept override;
	private:
		AudioTagPosVector findInfoChunkType(std::ifstream &readStream, std::uintmax_t size) const;
	};

}

