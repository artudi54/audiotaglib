#include "TextEncoding.hpp"

namespace audiotaglib::priv::id3 {
	std::string readStringByEncoding(TextEncoding encoding, std::istream &readStream, std::uint64_t length) {
		if (encoding == TextEncoding::Latin1)
			return readLatin1(readStream, length);
		else if (encoding == TextEncoding::Utf16BOM)
			return readUtf16BOM(readStream, length);
		else if (encoding == TextEncoding::Utf16BE)
			return readUtf16BE(readStream, length);
		else if (encoding == TextEncoding::Utf8)
			return readUtf8(readStream, length);
		return "";
	}

	std::string readStringWithEncoding(std::istream & readStream, std::uint64_t length) {
		if (length != std::uint64_t(-1))
			--length;
		return readStringByEncoding(static_cast<TextEncoding>(readStream.get()), readStream, length);
	}
}