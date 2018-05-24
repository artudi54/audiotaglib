#pragma once
#include "AudioTagScanner.hpp"
#include <array>
#include <fstream>


namespace tag::scanner {
    class ID3TagScanner : public AudioTagScanner {
		friend class RiffInfoScanner;
    public:
        virtual AudioTagPosVector getTagPositions(const std::filesystem::path &filePath) const override;
		virtual bool isFormatSpecific() const noexcept override;
	private:
		static AudioTagFormat getVersionFromHeader(std::istream &readStream);
    };
}

