#include <tag/AudioFileInformation.hpp>
using namespace std::literals;
namespace fs = std::filesystem;


namespace tag {
	AudioFileInformation::AudioFileInformation(const fs::path & filePath, bool scanAll)
		: filePath(filePath), audioContainerFormat(util::fileContainerFormat(filePath)), audioTagInformations() {
		validateFileWithThrow();
		audioTagInformations.reserve(4);
		scanFormats(scanAll);
	}

	AudioFileInformation::AudioFileInformation(fs::path && filePath, bool scanAll)
		: filePath(std::move(filePath)), audioContainerFormat(util::fileContainerFormat(filePath)), audioTagInformations() {
		validateFileWithThrow();
		audioTagInformations.reserve(4);
		scanFormats(scanAll);
	}





	const std::filesystem::path & AudioFileInformation::getFilePath() const noexcept {
		return filePath;
	}

	AudioContainerFormat AudioFileInformation::getAudioContainerFormat() const noexcept {
		return audioContainerFormat;
	}

	std::string AudioFileInformation::getAudioContainerFormatString() const noexcept {
		return string::toString(getAudioContainerFormat());
	}

	AudioTagFormat AudioFileInformation::getAudioTagFormat() const noexcept {
		AudioTagFormat tagFormat = AudioTagFormat::None;
		for (auto tagInformation : audioTagInformations)
			tagFormat |= tagInformation.getTagFormat();
		return tagFormat;
	}

	std::string AudioFileInformation::getAudioTagFormatString() const {
		return string::toString(getAudioTagFormat());
	}

	const std::vector<AudioTagInformation>& AudioFileInformation::getAudioTagInformations() const {
		return audioTagInformations;
	}





	void AudioFileInformation::validateFileWithThrow() {
		std::error_code dummy;

		if (!fs::exists(filePath, dummy))
			throw except::FileNotFoundException(filePath);

		std::ifstream testStream(filePath, std::ios::in);
		bool open = testStream.is_open();
		testStream.close();

		if (!open)
			throw except::FileNotReadableException(filePath);
	}




	void AudioFileInformation::scanFormats(bool scanAll) {
		const auto& scanners = scanner::StaticScannerFactory::getScanners(audioContainerFormat, scanAll);
		for (const auto& scanner : scanners) {

			std::size_t beforeSize = audioTagInformations.size();
			scanner->appendAudioTagInformation(audioTagInformations, filePath);
			std::size_t afterSize = audioTagInformations.size();

			if (beforeSize != afterSize && scanner->getSpecificFormat() != AudioContainerFormat::Unspecified) {
				audioContainerFormat = scanner->getSpecificFormat();
				break;
			}
		}

		if (audioContainerFormat == AudioContainerFormat::Invalid && !audioTagInformations.empty())
			audioContainerFormat = AudioContainerFormat::Unspecified;
	}
}





namespace tag::util {
	AudioTagFormat fileTagFormat(const std::filesystem::path & filePath) {
		return AudioFileInformation(filePath).getAudioTagFormat();
	}
}
