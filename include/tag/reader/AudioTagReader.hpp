#pragma once
#include <tag/AudioTagMap.hpp>
#include <filesystem>
#include <fstream>

//todo: add assumption of reading exacly whole tag
namespace tag::reader {
	class AudioTagReader {
	public:
		virtual ~AudioTagReader() noexcept;
		virtual AudioTagMap readTag(std::istream &readStream) const = 0;
	};
	using SharedAudioTagReader = std::shared_ptr<AudioTagReader>;
}
