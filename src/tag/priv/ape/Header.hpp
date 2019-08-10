#pragma once
#include <array>
#include <cstdint>
#include <istream>
#include <tag/priv/headers.hpp>
#include <tag/TagContainerFormat.hpp>

namespace tag::priv::ape {
	class Header {
	public:
		ByteArray<8> preamble;
		std::uint32_t version;
		std::uint32_t size;
		std::uint32_t itemCount;
		std::uint32_t flags;
		ByteArray<8> reserved;

		TagContainerFormat tagVersion() const;
		std::uint32_t totalTagSize() const;

		static Header readHeader(std::istream &readStream);
	private:
		static const std::uint32_t HAS_HEADER = 1 << 31;
	};
}