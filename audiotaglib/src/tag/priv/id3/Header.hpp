#pragma once
#include <array>
#include <cstdint>
#include <istream>
#include <tag/priv/headers.hpp>
#include <tag/AudioTagFormat.hpp>

namespace tag::priv::id3 {
	class Header {
	public:
		ByteArray<3> identifier;
		std::uint8_t majorVersion, revisionNumber;
		std::uint8_t flags;
		unsigned size;

		AudioTagFormat tagVersion() const;
		bool hasExtendedHeader() const;
		unsigned totalTagSize() const;

		static Header readHeader(std::istream &readStream);
	private:
		static const std::uint8_t UNSYNCHRONISATION = 1 << 7;
		static const std::uint8_t EXTENDED_HEADER = 1 << 6;
		static const std::uint8_t EXPERIMENTAL_INDICATOR = 1 << 5;
		static const std::uint8_t FOOTER_PRESENT = 1 << 4;
	};
}