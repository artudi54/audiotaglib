#include "AudioTagLocation.hpp"


namespace tag {
	AudioTagLocation::AudioTagLocation(AudioTagFormat tagFormat,
											 std::uint64_t headerOffset,
											 std::uint64_t length) noexcept
		: tagFormat(tagFormat), headerOffset(headerOffset), length(length) {}


    AudioTagFormat AudioTagLocation::getTagFormat() const noexcept {
		return tagFormat;
	}

	std::uint64_t AudioTagLocation::getHeaderOffset() const noexcept {
		return headerOffset;
	}

	std::uint64_t AudioTagLocation::getLength() const noexcept {
		return length;
	}
}
