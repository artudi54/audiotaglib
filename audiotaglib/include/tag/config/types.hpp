#pragma once
#include <cstdint>

namespace tag::config {
	enum class WaveTagFormat : std::uint8_t {
		InfoChunk,
		ID3Chunk,
		BothChunks
	};

	enum class ID3v2APEv2Option {
        APEv2,
        ID3v2
	};

	enum class ID3v2Version : std::uint8_t {
		V3,
		V4
	};

	enum class PreferredID3v2Encoding : std::uint8_t {
		Latin1,
		Utf16BOM,
		Utf16BE,
		Utf8
	};
}