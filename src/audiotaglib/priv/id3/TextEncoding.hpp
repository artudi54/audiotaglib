#pragma once
#include <audiotaglib/priv/read_util.hpp>

namespace audiotaglib::priv::id3 {
	enum class TextEncoding : std::uint8_t {
		Latin1,
		Utf16BOM,
		Utf16BE,
		Utf8,
	};
	std::string readStringByEncoding(TextEncoding encoding, std::istream &readStream, std::uint64_t length = -1);
	std::string readStringWithEncoding(std::istream &readStream, std::uint64_t length = -1);
}