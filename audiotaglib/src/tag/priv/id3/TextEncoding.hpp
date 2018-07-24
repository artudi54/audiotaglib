#pragma once
#include <tag/priv/read_util.hpp>

namespace tag::priv::id3 {
	enum class TextEncoding : std::uint8_t {
		Latin1,
		Utf16BOM,
		Utf16BE,
		Utf8,
	};
	std::string readStringByEncoding(TextEncoding encoding, std::istream &readStream, std::streamsize length = -1);
	std::string readStringWithEncoding(std::istream &readStream, std::streamsize length = -1);
}