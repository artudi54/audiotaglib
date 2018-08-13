#include "Header.hpp"
#include <tag/priv/read_util.hpp>

namespace tag::priv::ape {
	AudioTagFormat Header::tagVersion() const {
		if (version == 1000)
			return AudioTagFormat::APEv1;
		if (version == 2000)
			return AudioTagFormat::APEv2;
		return AudioTagFormat::None;
	}

	unsigned Header::totalTagSize() const {
		if (flags & HAS_HEADER)
			return size + 32;
		return size;
	}


	Header Header::readHeader(std::istream &readStream) {
		Header header;
		header.preamble = priv::readHeader<8>(readStream);
		header.version = priv::readLittleEndianNumber(readStream);
		header.size = priv::readLittleEndianNumber(readStream);
		header.itemCount = priv::readLittleEndianNumber(readStream);
		header.flags = priv::readLittleEndianNumber(readStream);
		header.reserved = priv::readHeader<8>(readStream);
		return header;
	}
}