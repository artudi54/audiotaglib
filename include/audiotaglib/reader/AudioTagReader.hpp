#pragma once
#include <audiotaglib/TagMap.hpp>
#include <filesystem>
#include <fstream>

//todo: add assumption of reading exacly whole audiotaglib
// TODO: rename to tag_reader
namespace audiotaglib::reader {
	class AudioTagReader {
	public:
		virtual ~AudioTagReader() noexcept;
		virtual TagMap readTag(std::istream &readStream) const = 0;
	};
	using SharedAudioTagReader = std::shared_ptr<AudioTagReader>;
}
