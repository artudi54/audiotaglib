#pragma once
#include <tag/AudioTagFormat.hpp>
#include <vector>

namespace tag {
	class AudioTagInformation {
	public:
		AudioTagInformation(AudioTagFormat format,
							std::uint64_t headerPosition,
							std::uint64_t length) noexcept;
		AudioTagFormat getTagFormat() const noexcept;
		std::uint64_t getHeaderOffset() const noexcept;
		std::uint64_t getLength() const noexcept;
	private:

		AudioTagFormat tagFormat;
		std::uint64_t headerOffset;
		std::uint64_t length;
	};
	using AudioTagInformationVector = std::vector<AudioTagInformation>;
}