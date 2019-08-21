#include "Frame.hpp"
#include <audiotaglib/priv/read_util.hpp>

namespace audiotaglib::priv::id3 {
	bool Frame::isCompressed() const {
		return flags & IS_COMPRESSED;
	}


	Frame Frame::read2Frame(std::istream & readStream) {
		Frame frame = {};
		frame.identifier.resize(3);
		readStream.read(frame.identifier.data(), 3);

		frame.size = readStream.get();
		frame.size = (frame.size << 8) | readStream.get();
		frame.size = (frame.size << 8) | readStream.get();

		return frame;
	}

	Frame Frame::read3Frame(std::istream & readStream) {
		Frame frame = {};
		frame.identifier.resize(4);
		readStream.read(frame.identifier.data(), 4);
		frame.size = readBigEndianNumber(readStream);
		frame.flags = priv::readShortBigEndianNumber(readStream);

		return frame;
	}

	Frame Frame::read4Frame(std::istream & readStream) {
		Frame frame = {};
		frame.identifier.resize(4);
		readStream.read(frame.identifier.data(), 4);
		frame.size = readSyncSafeBigEndianNumber(readStream);
		frame.flags = (readStream.get() << 8);
		frame.flags |= readStream.get();
		if (frame.flags & Frame::HAS_DATA_LENGTH_INDICATOR) {
			frame.size -= 4;
			readStream.seekg(4, std::ios::cur);
		}
		if (frame.flags & Frame::IS_COMPRESSED) {
			frame.size -= 4;
			readStream.seekg(4, std::ios::cur);
		}

		return frame;
	}
}