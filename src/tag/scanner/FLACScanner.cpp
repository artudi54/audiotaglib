#include "FLACScanner.hpp"
#include <tag/except/StreamParseException.hpp>
#include <tag/priv/read_util.hpp>
#include <tag/priv/vorbis/blocks.hpp>
#include <fstream>

namespace tag::scanner {
    ContainerFormat FLACScanner::getAssociatedContainerFormat() const noexcept {
        return ContainerFormat::FreeLosslessAudioCodec;
    }

    void FLACScanner::appendAudioTagInformationImpl(std::vector<AudioTagLocation> &informationVector,
                                                         std::istream &readStream, std::uint64_t fileSize) const {
		std::uintmax_t leftSize = fileSize;

		if (!priv::readAndEquals(readStream, priv::headers::FLAC))
			return;

		leftSize -= 4;
		bool hasPictures = false;

		std::uint8_t flagAndType = readStream.get();
		std::uint32_t blockSize = priv::readThreeBytesBigEndianNumber(readStream);
		std::uint8_t blockType = ((flagAndType << 1) & 0x7F) >> 1;
		bool metadataFinished = (flagAndType & (1 << 7)) != 0;

		if (blockType != priv::vorbis::STREAMINFO)
			throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 4);
		if (blockSize > leftSize - 4)
			throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 3);
		
		leftSize -= blockSize + 4;
		readStream.seekg(blockSize, std::ios::cur);

		while (!metadataFinished && leftSize > 0) {
			flagAndType = readStream.get();
			blockSize = priv::readThreeBytesBigEndianNumber(readStream);
			blockType = ((flagAndType << 1) & 0x7F) >> 1;
			metadataFinished = (flagAndType & (1 << 7)) != 0;

			if (blockType == priv::vorbis::STREAMINFO || blockType == priv::vorbis::INVALID)
				throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 4);
			if (blockSize > leftSize - 4)
				throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 3);

			if (blockType == priv::vorbis::VORBIS_COMMENT)
				informationVector.emplace_back(AudioTagFormat::VorbisComments, readStream.tellg(), blockSize);
			else if (blockType == priv::vorbis::PICTURE)
				hasPictures = true;

			leftSize -= blockSize + 4;
			readStream.seekg(blockSize, std::ios::cur);
		}

		if (hasPictures)
			informationVector.emplace_back(AudioTagFormat::FLACPictures, 0, fileSize);
	}
}