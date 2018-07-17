#include <tag/AudioTagInformation.hpp>


namespace tag {
	AudioTagInformation::AudioTagInformation(AudioTagFormat tagFormat,
											 std::uint64_t headerOffset,
											 std::uint64_t length) noexcept
		: tagFormat(tagFormat), headerOffset(headerOffset), length(length) {}




	AudioTagFormat AudioTagInformation::getTagFormat() const noexcept {
		return tagFormat;
	}
	std::uint64_t AudioTagInformation::getHeaderOffset() const noexcept {
		return headerOffset;
	}
	std::uint64_t AudioTagInformation::getLength() const noexcept {
		return length;
	}
}