#pragma once
#include <tag/scanner/AudioTagScanner.hpp>
#include <tag/except/FileParseException.hpp>

namespace tag::scanner {
	class AiffChunksScanner : public AudioTagScanner {
	public:
		virtual void appendAudioTagInformation(AudioTagInformationVector &informationVector,
											   const std::filesystem::path &filePath) const;
		virtual AudioContainerFormat getSpecificFormat() const;
	private:
		void findID3Chunk(AudioTagInformationVector &informationVector, std::istream &readStream,
						  unsigned size, const std::filesystem::path &filePath) const;
	};
}