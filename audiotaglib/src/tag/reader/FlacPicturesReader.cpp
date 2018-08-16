#include "FlacPicturesReader.hpp"
#include <tag/priv/read_util.hpp>
#include <tag/priv/vorbis/blocks.hpp>
#include <tag/priv/vorbis/ValueProcessor.hpp>

namespace tag::reader {
	AudioTagMap FLACPicturesReader::readTag(std::istream & readStream) const {
		static const priv::vorbis::ImageProcessor imageProcessor;
		AudioTagMap map;

		if (!priv::readAndEquals(readStream, priv::headers::FLAC))
			throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 4);

		std::uint8_t flagAndType = readStream.get();
		std::uint32_t blockSize = priv::readThreeBytesBigEndianNumber(readStream);
		std::uint8_t blockType = ((flagAndType << 1) & 0x7F) >> 1;
		bool metadataFinished = (flagAndType & (1 << 7)) != 0;

		if (blockType != priv::vorbis::STREAMINFO)
			throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 4);

		readStream.seekg(blockSize, std::ios::cur);

		while (!metadataFinished) {
			flagAndType = readStream.get();
			blockSize = priv::readThreeBytesBigEndianNumber(readStream);
			blockType = ((flagAndType << 1) & 0x7F) >> 1;
			metadataFinished = (flagAndType & (1 << 7)) != 0;

			if (blockType == priv::vorbis::STREAMINFO || blockType == priv::vorbis::INVALID)
				throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 4);

			if (blockType == priv::vorbis::PICTURE) {
				imageProcessor.processStream(readStream, blockSize, map);
			} else
				readStream.seekg(blockSize, std::ios::cur);
		}

		return map;
	}
}