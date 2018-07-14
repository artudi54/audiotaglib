#pragma once
#include <array>
#include <cstdint>
#include <istream>
#include <tag/priv/headers.hpp>
#include <tag/AudioTagFormat.hpp>

namespace tag::priv::ape {
	class Header {
	public:
		ByteArray<8> preamble;
		unsigned version;
		unsigned size;
		unsigned itemCount;
		unsigned flags;
		ByteArray<8> reserved;

		AudioTagFormat tagVersion() const;
		unsigned totalTagSize() const;

		static Header readHeader(std::istream &readStream);
	private:
		static const unsigned HAS_HEADER = 1 << 31;
	};
}