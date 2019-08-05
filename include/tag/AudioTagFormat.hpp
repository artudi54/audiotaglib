#pragma once
#include <cstdint>
#include <string>

namespace tag {
	enum class AudioTagFormat : std::uint16_t {
		None = 0,
		ID3v1 = 1,
		ID3v22 = 2,
		ID3v23 = 4,
		ID3v24 = 8,
		APEv1 = 16,
		APEv2 = 32,
		VorbisComments = 64,
		FLACPictures = 128,
		ASFMetadata = 256,
		RiffInfo = 512,
		AiffChunks = 1024,
		MatroskaMetadata = 2048,
		MP4Metadata = 4096
    };

	constexpr std::underlying_type_t<AudioTagFormat> operator*(AudioTagFormat format) {
		return static_cast<std::underlying_type_t<AudioTagFormat>>(format);
	}

    constexpr AudioTagFormat operator &(AudioTagFormat lhs, AudioTagFormat rhs) {
        return AudioTagFormat((*lhs) & (*rhs));
    }

    constexpr AudioTagFormat operator |(AudioTagFormat lhs, AudioTagFormat rhs) {
		return AudioTagFormat((*lhs) | (*rhs));
    }

    constexpr AudioTagFormat operator ^(AudioTagFormat lhs, AudioTagFormat rhs) {
		return AudioTagFormat((*lhs) ^ (*rhs));

    }

    constexpr AudioTagFormat& operator &=(AudioTagFormat &lhs, AudioTagFormat rhs) {
        return lhs = lhs & rhs;
    }

    constexpr AudioTagFormat& operator |=(AudioTagFormat &lhs, AudioTagFormat rhs) {
        return lhs = lhs | rhs;
    }

    constexpr AudioTagFormat& operator ^=(AudioTagFormat &lhs, AudioTagFormat rhs) {
        return lhs = lhs ^ rhs;
    }
}

namespace tag::string {
	std::string toString(AudioTagFormat audioTagFormat);
}



namespace tag::util {
	constexpr bool hasAnyTag(AudioTagFormat tag) {
		return (*tag) != 0;
	}

	constexpr bool hasNoTags(AudioTagFormat tag) {
		return !hasAnyTag(tag);
	}
}