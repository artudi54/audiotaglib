#pragma once

#include <cstdint>

namespace tag {
	enum class AudioFormat : std::uint16_t {
		Unknown,
		WaveAudio,
		MpegLayer3
	};
}