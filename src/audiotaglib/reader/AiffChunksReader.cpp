#include "AiffChunksReader.hpp"
#include <audiotaglib/priv/read_util.hpp>

namespace audiotaglib::reader {

	TagMap AiffChunksReader::readTag(std::istream & readStream) const {
		TagMap map;
		if (!priv::readAndEquals(readStream, priv::headers::FORM_CHUNK))
			throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 4);
		std::uint32_t formSize = priv::readBigEndianNumber(readStream) - 4;

		if (!priv::readAndEquals(readStream, priv::headers::AIFF_CHUNK))
			throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 4);

		while (formSize >= 8) {
			priv::ByteArray<4> chunkId = priv::readHeader<4>(readStream);
			std::uint32_t chunkSize = priv::readBigEndianNumber(readStream);

			if (chunkSize + 8 > formSize)
				throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 4);


			if (chunkId == priv::headers::NAME_CHUNK)
				map.setTitle(priv::readUtf8(readStream, chunkSize));
			else if (chunkId == priv::headers::AUTHOR_CHUNK)
				map.setArtist(priv::readUtf8(readStream, chunkSize));
			else if (chunkId == priv::headers::COPYRIGHT_CHUNK)
				map.setCopyright(priv::readUtf8(readStream, chunkSize));
			else if (chunkId == priv::headers::ANNOTATION_CHUNK)
				map.setComment(priv::readUtf8(readStream, chunkSize));
			else
				readStream.seekg(chunkSize, std::ios::cur);
			formSize -= chunkSize + 8;
		}
		return map;
	}
}