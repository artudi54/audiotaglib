#include "FLACScanner.hpp"
#include <audiotaglib/except/StreamParseException.hpp>
#include <audiotaglib/priv/headers.hpp>
#include <audiotaglib/priv/vorbis/blocks.hpp>

namespace audiotaglib::tag_scanner {
    void FLACScanner::appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                                      common::ReadStream &readStream) const {
		if (!readStream.readHeaderAndEquals(priv::headers::FLAC))
			return;

		bool hasPictures = false;

		std::uint8_t flagAndType = readStream.readOneByteNumber();
		std::uint32_t blockSize = readStream.readThreeBytesBigEndianNumber();
		std::uint8_t blockType = ((flagAndType << 1u) & 0x7Fu) >> 1u;
		bool metadataFinished = (flagAndType & (1u << 7u)) != 0;

		if (blockType != priv::vorbis::STREAMINFO)
			throw except::StreamParseException(readStream.getPosition() - 4);
		if (blockSize > readStream.getRemainingSize() - 4)
			throw except::StreamParseException(readStream.getPosition() - 3);
		
		readStream.setPosition(blockSize, common::ReadStream::Offset::CURRENT);

		while (!metadataFinished && readStream.getRemainingSize() > 0) {
			flagAndType = readStream.readOneByteNumber();
			blockSize = readStream.readThreeBytesBigEndianNumber();
			blockType = ((flagAndType << 1u) & 0x7Fu) >> 1u;
			metadataFinished = (flagAndType & (1u << 7u)) != 0;

			if (blockType == priv::vorbis::STREAMINFO || blockType == priv::vorbis::INVALID)
                throw except::StreamParseException(readStream.getPosition() - 4);
			if (blockSize > readStream.getRemainingSize() - 4)
                throw except::StreamParseException(readStream.getPosition() - 3);

			if (blockType == priv::vorbis::VORBIS_COMMENT)
				tagContainerLocations.emplace_back(TagContainerFormat::VorbisComments, readStream.getPosition(), blockSize);
			else if (blockType == priv::vorbis::PICTURE)
				hasPictures = true;

            readStream.setPosition(blockSize, common::ReadStream::Offset::CURRENT);
		}

		if (hasPictures)
			tagContainerLocations.emplace_back(TagContainerFormat::FLACPictures, 0, readStream.getSize());
	}
}