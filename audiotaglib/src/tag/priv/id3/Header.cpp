#include "Header.hpp"
#include <tag/priv/read_util.hpp>

namespace tag::priv::id3 {
	
	AudioTagFormat Header::tagVersion() const {
		if (majorVersion == 2)
			return AudioTagFormat::ID3v22;
		if (majorVersion == 3)
			return AudioTagFormat::ID3v23;
		if (majorVersion == 4)
			return AudioTagFormat::ID3v24;
		return AudioTagFormat::None;
	}

	bool Header::hasFooter() const {
		return flags & FOOTER_PRESENT;
	}


	bool Header::hasExtendedHeader() const {
		return flags & EXTENDED_HEADER;
	}



	unsigned Header::totalTagSize() const {
		if (hasFooter())
			return size + 20;
		return size + 10;
	}

	const std::unordered_map<std::string, priv::id3::SharedFrameProcessor>* Header::frameProcessors() const {
		switch (majorVersion) {
		case 2:
			return &FRAME2_PROCESSORS;
		case 3:
			return &FRAME3_PROCESSORS;
		case 4:
			return &FRAME4_PROCESSORS;
		default:
			return nullptr;
		}
	}

	unsigned Header::frameHeaderSize() const {
		switch (majorVersion) {
		case 2:
			return 6;
		case 3:
		case 4:
			return 10;
		default:
			return 0;
		}
	}


	FrameReaderProc Header::frameReaderProc() const {
		switch (majorVersion) {
		case 2:
			return Frame::read2Frame;
		case 3:
			return Frame::read3Frame;
		case 4:
			return Frame::read4Frame;
		default:
			return nullptr;
		}
	}






	Header Header::readHeader(std::istream & readStream) {
		Header header;
		header.identifier = priv::readHeader<3>(readStream);
		header.majorVersion = readStream.get();
		header.revisionNumber = readStream.get();
		header.flags = readStream.get();
		header.size = priv::readSyncSafeBigEndianSize(readStream);
		return header;
	}


	unsigned skipExtendedHeaderAndGetSize(std::istream & readStream) {
		unsigned size = readBigEndianSize(readStream);
		readStream.seekg(size, std::ios::cur);
		return size + 4;
	}
}
