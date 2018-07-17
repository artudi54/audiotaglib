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



	bool Header::hasExtendedHeader() const {
		return flags & EXTENDED_HEADER;
	}



	unsigned Header::totalTagSize() const {
		if (flags & FOOTER_PRESENT)
			return size + 20;
		return size + 10;
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
}
