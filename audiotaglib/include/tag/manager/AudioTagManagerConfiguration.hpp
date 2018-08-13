#pragma once
#include <memory>
#include <filesystem>
#include <tag/except/FileNotReadableException.hpp>
#include <tag/except/FileNotWritableException.hpp>
#include <tag/except/FileParseException.hpp>

namespace tag::manager {
	class AudioTagManagerConfiguration {
	public:
		enum class WaveTagFormat : std::uint8_t {
			InfoChunk,
			ID3Chunk,
			BothChunks
		};

		enum class ID3v2Version : std::uint8_t {
			V3,
			V4
		};

		enum class PrefferedID3v2Encoding : std::uint8_t {
			Latin1,
			Utf16BOM,
			Utf16BE,
			Utf8
		};

		bool					appendID3v1Tag			= true;
		ID3v2Version			id3v2Version			= ID3v2Version::V4;
		PrefferedID3v2Encoding	prefferedID3v2Encoding	= PrefferedID3v2Encoding::Utf8;
		bool					saveOnDestroy			= false;
		bool					scanAllPossible			= false;
		WaveTagFormat			waveTagFormat			= WaveTagFormat::BothChunks;

		void saveTo(const std::filesystem::path &iniFilePath) const;
		static AudioTagManagerConfiguration loadFrom(const std::filesystem::path &iniFilePath);
	};

	using SharedAudioTagManagerConfiguration = std::shared_ptr<AudioTagManagerConfiguration>;
}

