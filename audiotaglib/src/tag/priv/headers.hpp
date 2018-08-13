#pragma once
#include <array>
#include <cctype>
#include <cstddef>

namespace tag::priv {
	template < std::size_t N >
	using ByteArray = std::array<std::byte, N>;

	namespace headers {
		static constexpr ByteArray<3> ID3_V1 =
		{ std::byte('T'), std::byte('A'), std::byte('G') };
		static constexpr ByteArray<3> ID3_V2 =
		{ std::byte('I'), std::byte('D'), std::byte('3') };
		static constexpr ByteArray<3> ID3_V2R =
		{ std::byte('3'), std::byte('D'), std::byte('I') };


		static constexpr ByteArray<8> APE = {
			std::byte('A'),
			std::byte('P'),
			std::byte('E'),
			std::byte('T'),
			std::byte('A'),
			std::byte('G'),
			std::byte('E'),
			std::byte('X')
		};


		static constexpr ByteArray<4> RIFF_CHUNK =
		{ std::byte('R'), std::byte('I'), std::byte('F'), std::byte('F') };
		static constexpr ByteArray<4> WAVE =
		{ std::byte('W'), std::byte('A'), std::byte('V'), std::byte('E') };

		static constexpr ByteArray<4> LIST_CHUNK
		{ std::byte('L'), std::byte('I'), std::byte('S'), std::byte('T') };
		static constexpr ByteArray<4> ID3_CHUNK =
		{ std::byte('I'), std::byte('D'), std::byte('3'), std::byte(' ') };
		static constexpr ByteArray<4> ID3_CHUNK_LOWER =
		{ std::byte('i'), std::byte('d'), std::byte('3'), std::byte(' ') };
		static constexpr ByteArray<4> INFO_CHUNK =
		{ std::byte('I'), std::byte('N'), std::byte('F'), std::byte('O') };


		static constexpr ByteArray<4> FORM_CHUNK =
		{ std::byte('F'), std::byte('O'), std::byte('R'), std::byte('M') };
		static constexpr ByteArray<4> AIFF_CHUNK =
		{ std::byte('A'), std::byte('I'), std::byte('F'), std::byte('F') };

		static constexpr ByteArray<4> NAME_CHUNK =
		{ std::byte('N'), std::byte('A'), std::byte('M'), std::byte('E') };
		static constexpr ByteArray<4> AUTHOR_CHUNK =
		{ std::byte('A'), std::byte('U'), std::byte('T'), std::byte('H') };
		static constexpr ByteArray<4> COPYRIGHT_CHUNK =
		{ std::byte('('), std::byte('c'), std::byte(')'), std::byte(' ') };
		static constexpr ByteArray<4> ANNOTATION_CHUNK =
		{ std::byte('A'), std::byte('N'), std::byte('N'), std::byte('O') };


		static constexpr ByteArray<16> ASF_HEADER_GUID = {
			std::byte(0x30), std::byte(0x26), std::byte(0xb2), std::byte(0x75),
			std::byte(0x8e), std::byte(0x66), std::byte(0xcf), std::byte(0x11),
			std::byte(0xa6), std::byte(0xd9), std::byte(0x00), std::byte(0xaa),
			std::byte(0x00), std::byte(0x62), std::byte(0xce), std::byte(0x6c)
		};
		static constexpr ByteArray<16> ASF_CONTENT_DESCRIPTION_GUID = {
			std::byte(0x33), std::byte(0x26), std::byte(0xB2), std::byte(0x75),
			std::byte(0x8E), std::byte(0x66), std::byte(0xCF), std::byte(0x11),
			std::byte(0xA6), std::byte(0xD9), std::byte(0x00), std::byte(0xAA),
			std::byte(0x00), std::byte(0x62), std::byte(0xCE), std::byte(0x6C)
		};
		static constexpr ByteArray<16> ASF_EXTENDED_CONTENT_DESCRIPTION_GUID = {
			std::byte(0x40), std::byte(0xA4), std::byte(0xD0), std::byte(0xD2),
			std::byte(0x07), std::byte(0xE3), std::byte(0xD2), std::byte(0x11),
			std::byte(0x97), std::byte(0xF0), std::byte(0x00), std::byte(0xA0),
			std::byte(0xC9), std::byte(0x5E), std::byte(0xA8), std::byte(0x50)
		};
	}
}
