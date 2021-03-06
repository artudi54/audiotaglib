#pragma once
#include <array>
#include <cstdint>
#include <istream>
#include <audiotaglib/priv/headers.hpp>
#include <audiotaglib/priv/id3/Frame.hpp>
#include <audiotaglib/priv/id3/FrameProcessor.hpp>
#include <audiotaglib/except/StreamParseException.hpp>
#include <audiotaglib/TagContainerFormat.hpp>

namespace audiotaglib::priv::id3 {
	class Header {
	public:
		ByteArray<3> identifier;
		std::uint8_t majorVersion, revisionNumber;
		std::uint8_t flags;
		std::uint32_t size;

		TagContainerFormat tagVersion() const;
		bool hasFooter() const;
		bool hasExtendedHeader() const;
		std::uint32_t totalTagSize() const;

		const std::unordered_map<std::string, priv::id3::SharedFrameProcessor>* frameProcessors() const;
		std::uint32_t frameHeaderSize() const;
		FrameReaderProc frameReaderProc() const;

		static Header readHeader(std::istream &readStream);
	private:
		static const std::uint8_t UNSYNCHRONISATION = 1 << 7;
		static const std::uint8_t EXTENDED_HEADER = 1 << 6;
		static const std::uint8_t EXPERIMENTAL_INDICATOR = 1 << 5;
		static const std::uint8_t FOOTER_PRESENT = 1 << 4;
	};

	std::uint32_t skipExtendedHeaderAndGetSize(std::istream &readStream);
}