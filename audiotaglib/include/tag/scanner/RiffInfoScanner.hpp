#pragma once
#include <tag/scanner/TagScanner.hpp>

namespace tag::scanner {
	class RiffInfoScanner : public TagScanner {
	public:
		void appendAudioTagInformation(AudioTagInformationVector &informationVector,
									   const std::filesystem::path &filePath) const override;
		AudioContainerFormat getSpecificFormat() const override;
	private:
		void findAndScanTagChunks(AudioTagInformationVector &information,
								  std::ifstream &readStream,
								  std::uint32_t size,
								  const std::filesystem::path &filePath) const;
	};
}

