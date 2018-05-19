#pragma once
#include <filesystem>
#include <memory>
#include <fstream>
#include "AudioTagMap.hpp"
#include "AudioTagProcessorBase.hpp"

namespace tag::reader {
	class AudioTagReader : public base::AudioTagProcessorBase {
	public:
		virtual ~AudioTagReader() noexcept;
		virtual AudioTagMap readTag(std::istream &readStream) const = 0;

		static std::ifstream makeStream(const std::filesystem::path &filePath, std::uint64_t pos);
	};
	using SharedAudioTagReader = std::shared_ptr<AudioTagReader>;
}

