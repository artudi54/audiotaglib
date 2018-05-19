#include "AudioTagReader.hpp"
namespace fs = std::filesystem;


namespace tag::reader {

	AudioTagReader::~AudioTagReader() noexcept {}


	std::ifstream AudioTagReader::makeStream(const fs::path & filePath, std::uint64_t pos) {
		std::ifstream stream(filePath, std::ios::in | std::ios::binary);
		stream.seekg(std::streamoff(pos), std::ios::cur);
		return stream;
	}
}