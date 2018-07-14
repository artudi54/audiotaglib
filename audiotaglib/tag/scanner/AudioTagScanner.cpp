#include "AudioTagScanner.hpp"
namespace fs = std::filesystem;

namespace tag::scanner {

	AudioTagFormat toFormat(const AudioTagPosVector & tagPositions) noexcept {
		AudioTagFormat format = AudioTagFormat::None;
		for (auto &pair : tagPositions)
			format |= pair.first;
		return format;
	}

	AudioTagPosVector tag::scanner::AudioTagScanner::getTagPositions(const fs::path & filePath) const {
		std::vector<AudioTagInformation> infos;
		appendAudioTagInformation(infos, filePath);
		AudioTagPosVector vec;
		for (auto &info : infos)
			vec.emplace_back(info.getTagFormat(), info.getHeaderOffset());

		return vec;
	}




	std::pair<std::uintmax_t, std::ifstream>
	AudioTagScanner::getValidatedSizeAndStream(const std::filesystem::path &filePath) {
		std::error_code dummy;

		std::pair<std::uintmax_t, std::ifstream> retVal(
			fs::file_size(filePath, dummy),
			std::ifstream(filePath, std::ios::in | std::ios::binary)
		);
		if (retVal.first == -1 || !retVal.second.is_open())
			throw except::FileNotReadableException(filePath);

		return retVal;
	}

}