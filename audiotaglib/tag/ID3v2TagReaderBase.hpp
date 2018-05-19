#pragma once
#include <cstdint>
#include <cstddef>
#include <array>
#include <vector>
#include <sstream>
#include "AudioTagReader.hpp"

namespace tag::base {
	class ID3v2TagReaderBase : public reader::AudioTagReader {
	protected:
		struct Header {
			std::array<std::byte, 3> identifier;
			std::uint8_t majorVersion, revisionNumber;
			std::uint8_t flags;
			unsigned size;

			static const std::uint8_t UNSYNCHRONISATION = 1 << 7;
			static const std::uint8_t EXTENDED_HEADER = 1 << 6;
			static const std::uint8_t EXPERIMENTAL_INDICATOR = 1 << 5;
			static const std::uint8_t FOOTER_PRESENT = 1 << 4;
		};

		struct Frame {
			std::string identifier;
			unsigned size;
			std::uint16_t flags;
			std::vector<std::byte> data;
		};

		enum class TextEncoding : std::uint8_t {
			Latin1,
			Utf16BOM,
			Utf16BE,
			Utf8,
		};

		static unsigned readSyncSafeSize(std::istream &readStream);
		static Header readID3Header(std::istream &readStream);
		static Frame read4Frame(std::istream &readStream);
		static Frame read3Frame(std::istream &readStream);
		static Frame read2Frame(std::istream &readStream);
		static unsigned skipExtendedHeader(std::istream &readStream);
		static std::string readStringByEncoding(TextEncoding encoding, std::istream &readStream, std::streamsize length = -1);
	};
}