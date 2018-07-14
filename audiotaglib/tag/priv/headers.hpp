#pragma once
#include <array>
#include <cctype>

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


		static constexpr ByteArray<4> RIFF =
		{ std::byte('R'), std::byte('I'), std::byte('F'), std::byte('F') };

		static constexpr ByteArray<4> WAVE =
		{ std::byte('W'), std::byte('A'), std::byte('V'), std::byte('E') };




		static constexpr ByteArray<4> LIST_CHUNK
		{ std::byte('L'), std::byte('I'), std::byte('S'), std::byte('T') };

		static constexpr ByteArray<4> ID3_CHUNK =
		{ std::byte('I'), std::byte('D'), std::byte('3'), std::byte(' ') };

		static constexpr ByteArray<4> INFO_SUBCHUNK =
		{ std::byte('I'), std::byte('N'), std::byte('F'), std::byte('O') };




		static constexpr std::array<std::byte, 16> ASF_HEADER_GUID = {
			std::byte(0x30), std::byte(0x26), std::byte(0xb2), std::byte(0x75),
			std::byte(0x8e), std::byte(0x66), std::byte(0xcf), std::byte(0x11),
			std::byte(0xa6), std::byte(0xd9), std::byte(0x00), std::byte(0xaa),
			std::byte(0x00), std::byte(0x62), std::byte(0xce), std::byte(0x6c)
		};
	}
}