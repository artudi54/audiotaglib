#pragma once
#include <string>
#include <vector>
#include <istream>

namespace tag::priv::id3 {
	class Frame {
	public:
		std::string identifier;
		unsigned size;
		std::uint16_t flags;

		bool isCompressed() const;

		static Frame read2Frame(std::istream &readStream);
		static Frame read3Frame(std::istream &readStream);
		static Frame read4Frame(std::istream &readStream);
	private:
		static const std::uint8_t HAS_DATA_LENGTH_INDICATOR = 1;
		static const std::uint8_t IS_COMPRESSED = 1 << 3;
	};
	using FrameReaderProc = Frame(*)(std::istream&);
}