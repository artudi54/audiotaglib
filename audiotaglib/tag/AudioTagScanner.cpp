#include "AudioTagScanner.hpp"

namespace tag::scanner {

	AudioTagFormat toFormat(const AudioTagPosVector & tagPositions) noexcept {
		AudioTagFormat format = AudioTagFormat::None;
		for (auto &pair : tagPositions)
			format |= pair.first;
		return format;
	}

}