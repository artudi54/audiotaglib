#pragma once
#include <tag/AudioTagMap.hpp>
//todo: remove this dependency
#include <tag/AudioTagProcessorBase.hpp>
#include <filesystem>
#include <fstream>

//todo: add assumption of reading exacly whole tag
namespace tag::reader {
	class AudioTagReader : public base::AudioTagProcessorBase {
	public:
		virtual ~AudioTagReader() noexcept;
		virtual AudioTagMap readTag(std::istream &readStream) const = 0;
	};
	using SharedAudioTagReader = std::shared_ptr<AudioTagReader>;
}

