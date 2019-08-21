#include "Header.hpp"
#include <audiotaglib/priv/read_util.hpp>

namespace audiotaglib::priv::ape {
	TagContainerFormat Header::tagVersion() const {
		if (version == 1000)
			return TagContainerFormat::APEv1;
		if (version == 2000)
			return TagContainerFormat::APEv2;
		return TagContainerFormat::None;
	}

	std::uint32_t Header::totalTagSize() const {
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