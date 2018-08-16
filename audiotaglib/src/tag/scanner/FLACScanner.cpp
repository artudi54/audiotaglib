#include "FLACScanner.hpp"
#include <tag/priv/read_util.hpp>
#include <tag/priv/vorbis/blocks.hpp>

namespace tag::scanner {
	void FLACScanner::appendAudioTagInformation(AudioTagInformationVector & informationVector,
												const std::filesystem::path & filePath) const {
		auto[size, readStream] = getValidatedSizeAndStream(filePath);
		std::uintmax_t leftSize = size;

		if (!priv::readAndEquals(readStream, priv::headers::FLAC))
			return;

		leftSize -= 4;
		bool hasPictures = false;

		std::uint8_t flagAndType = readStream.get();
		std::uint32_t blockSize = priv::readThreeBytesBigEndianNumber(readStream);
		std::uint8_t blockType = ((flagAndType << 1) & 0x7F) >> 1;
		bool metadataFinished = (flagAndType & (1 << 7)) != 0;

		if (blockType != priv::vorbis::STREAMINFO)
			throw except::FileParseException(filePath, std::uint64_t(readStream.tellg()) - 4, except::FileParseException::PositionType::Offset);
		if (blockSize > leftSize - 4)
			throw except::FileParseException(filePath, std::uint64_t(readStream.tellg()) - 3, except::FileParseException::PositionType::Offset);
		
		leftSize -= blockSize + 4;
		readStream.seekg(blockSize, std::ios::cur);

		while (!metadataFinished && leftSize > 0) {
			flagAndType = readStream.get();
			blockSize = priv::readThreeBytesBigEndianNumber(readStream);
			blockType = ((flagAndType << 1) & 0x7F) >> 1;
			metadataFinished = (flagAndType & (1 << 7)) != 0;

			if (blockType == priv::vorbis::STREAMINFO || blockType == priv::vorbis::INVALID)
				throw except::FileParseException(filePath, std::uint64_t(readStream.tellg()) - 4, except::FileParseException::PositionType::Offset);
			if (blockSize > leftSize - 4)
				throw except::FileParseException(filePath, std::uint64_t(readStream.tellg()) - 3, except::FileParseException::PositionType::Offset);

			if (blockType == priv::vorbis::VORBIS_COMMENT)
				informationVector.emplace_back(AudioTagFormat::VorbisComments, readStream.tellg(), blockSize);
			else if (blockType == priv::vorbis::PICTURE)
				hasPictures = true;

			leftSize -= blockSize + 4;
			readStream.seekg(blockSize, std::ios::cur);
		}

		if (hasPictures)
			informationVector.emplace_back(AudioTagFormat::FLACPictures, 0, size);
	}

	AudioContainerFormat FLACScanner::getSpecificFormat() const {
		return AudioContainerFormat::FreeLosslessAudioCodec;
	}
}