#include <tag/scanner/AudioTagScanner.hpp>
namespace fs = std::filesystem;

namespace tag::scanner {
	
	AudioTagScanner::~AudioTagScanner() {}

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