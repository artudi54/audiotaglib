#pragma once
#include <tag/scanner/AudioTagScanner.hpp>
#include <tag/except/FileParseException.hpp>

namespace tag::scanner {
	class APETagScanner : public AudioTagScanner {
	public:
		void appendAudioTagInformation(AudioTagInformationVector &informationVector,
									   const std::filesystem::path &filePath) const override;
		AudioContainerFormat getSpecificFormat() const override;
	private:
		void appendFront(AudioTagInformationVector &informationVector, std::uintmax_t size,
						 std::istream &readStream, const std::filesystem::path &filePath) const;
		void appendBack(AudioTagInformationVector &informationVector, std::uintmax_t size,
						std::istream &readStream, const std::filesystem::path &filePath) const;
	};

}

