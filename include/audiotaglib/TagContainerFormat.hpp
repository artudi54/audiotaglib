#pragma once
#include <cstdint>
#include <string>

namespace audiotaglib {
	enum class TagContainerFormat : std::uint16_t {
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

	constexpr std::underlying_type_t<TagContainerFormat> operator*(TagContainerFormat tagContainerFormat) {
		return static_cast<std::underlying_type_t<TagContainerFormat>>(tagContainerFormat);
	}

    constexpr TagContainerFormat operator &(TagContainerFormat lhs, TagContainerFormat rhs) {
        return TagContainerFormat((*lhs) & (*rhs));
    }

    constexpr TagContainerFormat operator |(TagContainerFormat lhs, TagContainerFormat rhs) {
		return TagContainerFormat((*lhs) | (*rhs));
    }

    constexpr TagContainerFormat operator ^(TagContainerFormat lhs, TagContainerFormat rhs) {
		return TagContainerFormat((*lhs) ^ (*rhs));

    }

    constexpr TagContainerFormat& operator &=(TagContainerFormat &lhs, TagContainerFormat rhs) {
        return lhs = lhs & rhs;
    }

    constexpr TagContainerFormat& operator |=(TagContainerFormat &lhs, TagContainerFormat rhs) {
        return lhs = lhs | rhs;
    }

    constexpr TagContainerFormat& operator ^=(TagContainerFormat &lhs, TagContainerFormat rhs) {
        return lhs = lhs ^ rhs;
    }
}

namespace audiotaglib::string {
	std::string toString(TagContainerFormat tagContainerFormat);
}



namespace audiotaglib::util {
	constexpr bool hasAnyFormat(TagContainerFormat tagContainerFormat) {
		return (*tagContainerFormat) != 0;
	}

	constexpr bool hasNoFormat(TagContainerFormat tagContainerFormat) {
		return !hasAnyFormat(tagContainerFormat);
	}
}