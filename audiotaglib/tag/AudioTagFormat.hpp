#pragma once
#include <cstdint>

namespace tag {
    enum class AudioTagFormat : std::uint16_t {
        None = 0,
        ID3v1 = 1,
		ID3v22 = 2,
		ID3v23 = 4,
		ID3v24 = 8,
        WaveInfo = 16,
		APEv1 = 32,
		APEv2 = 64,
    };

    constexpr bool anyTag(AudioTagFormat tag) {
        return tag != AudioTagFormat::None;
    }

    constexpr bool noTags(AudioTagFormat tag) {
        return !anyTag(tag);
    }

    constexpr AudioTagFormat operator &(AudioTagFormat lhs, AudioTagFormat rhs) {
        return AudioTagFormat(static_cast<std::uint16_t>(lhs) & static_cast<std::uint16_t>(rhs));
    }

    constexpr AudioTagFormat operator |(AudioTagFormat lhs, AudioTagFormat rhs) {
        return AudioTagFormat(static_cast<std::uint16_t>(lhs) | static_cast<std::uint16_t>(rhs));
    }

    constexpr AudioTagFormat operator ^(AudioTagFormat lhs, AudioTagFormat rhs) {
        return AudioTagFormat(static_cast<std::uint16_t>(lhs) | static_cast<std::uint16_t>(rhs));
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