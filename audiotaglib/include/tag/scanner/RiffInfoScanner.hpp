#pragma once
#include <tag/scanner/AudioTagScanner.hpp>
#include <tag/except/FileParseException.hpp>

namespace tag::scanner {
	class RiffInfoScanner : public AudioTagScanner {
	public:
		virtual void appendAudioTagInformation(AudioTagInformationVector &informationVector,
											   const std::filesystem::path &filePath) const;
		virtual AudioContainerFormat getSpecificFormat() const;
	private:
		void findAndScanTagChunks(AudioTagInformationVector &information,
								  std::ifstream &readStream,
								  std::uint32_t size,
								  const std::filesystem::path &filePath) const;
	};
}

