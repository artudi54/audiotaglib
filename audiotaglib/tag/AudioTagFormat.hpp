#pragma once
#include <cstdint>
#include <type_traits>

namespace tag {
	enum class AudioTagFormat : std::uint16_t {
		None = 0,
		ID3v1 = 1,
		ID3v22 = 2,
		ID3v23 = 4,
		ID3v24 = 8,
		RiffInfo = 16,
		APEv1 = 32,
		APEv2 = 64,
		ASFMetadata = 128
    };

	constexpr std::underlying_type_t<AudioTagFormat> operator*(AudioTagFormat format) {
		return static_cast<std::underlying_type_t<AudioTagFormat>>(format);
	}

    constexpr bool anyTag(AudioTagFormat tag) {
        return (*tag) != 0;
    }

    constexpr bool noTags(AudioTagFormat tag) {
        return !anyTag(tag);
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