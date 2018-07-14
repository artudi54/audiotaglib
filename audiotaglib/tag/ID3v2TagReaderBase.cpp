#include "ID3v2TagReaderBase.hpp"

namespace tag::base {


	ID3v2TagReaderBase::Header ID3v2TagReaderBase::readID3Header(std::istream & readStream) {
		Header header;
		header.identifier = readHeader<3>(readStream);
		header.majorVersion = readStream.get();
		header.revisionNumber = readStream.get();
		header.flags = readStream.get();
		header.size = readSyncSafeBigEndianSize(readStream);
		return header;
	}

	ID3v2TagReaderBase::Frame ID3v2TagReaderBase::read4Frame(std::istream & readStream) {
		Frame frame;
		frame.identifier.resize(4);
		readStream.read(frame.identifier.data(), 4);
		frame.size = readSyncSafeBigEndianSize(readStream);
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
		frame.data.resize(frame.size);
		readStream.read(reinterpret_cast<char*>(frame.data.data()), frame.size);
		return frame;
	}


	ID3v2TagReaderBase::Frame ID3v2TagReaderBase::read3Frame(std::istream & readStream) {
		Frame frame;
		frame.identifier.resize(4);
		readStream.read(frame.identifier.data(), 4);
		frame.size = readBigEndianSize(readStream);
		frame.flags = (readStream.get() << 8) | readStream.get();
		frame.data.resize(frame.size);
		readStream.read(reinterpret_cast<char*>(frame.data.data()), frame.size);
		return frame;
	}

	ID3v2TagReaderBase::Frame ID3v2TagReaderBase::read2Frame(std::istream & readStream) {
		Frame frame = {};
		frame.identifier.resize(3);
		readStream.read(frame.identifier.data(), 3);
		frame.size = readStream.get();
		frame.size = (frame.size << 8) | readStream.get();
		frame.size = (frame.size << 8) | readStream.get();
		frame.data.resize(frame.size);
		readStream.read(reinterpret_cast<char*>(frame.data.data()), frame.size);
		return frame;
	}


	unsigned ID3v2TagReaderBase::skipExtendedHeader(std::istream & readStream) {
		unsigned size = readBigEndianSize(readStream);
		readStream.seekg(size, std::ios::cur);
		return size + 4;
	}


	std::string ID3v2TagReaderBase::readStringByEncoding(TextEncoding encoding, std::istream &readStream, std::streamsize length) {
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

}