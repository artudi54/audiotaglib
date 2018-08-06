#include "AiffChunksScanner.hpp"
#include <tag/priv/read_util.hpp>
#include <tag/priv/id3/Header.hpp>


namespace tag::scanner {
	void AiffChunksScanner::appendAudioTagInformation(AudioTagInformationVector & informationVector,
													  const std::filesystem::path & filePath) const {
		auto[size, readStream] = getValidatedSizeAndStream(filePath);
		
		if (priv::readAndEquals(readStream, priv::headers::FORM_CHUNK)) {
			unsigned formSize = priv::readBigEndianSize(readStream);
			if (formSize + 4 > size)
				throw except::FileParseException(filePath, 4, except::FileParseException::PositionType::Offset);

			if (priv::readAndEquals(readStream, priv::headers::AIFF_CHUNK))
				informationVector.emplace_back(AudioTagFormat::AiffChunks, 0, formSize + 4);

			findID3Chunk(informationVector, readStream, formSize - 4, filePath);
		}
	}


	AudioContainerFormat AiffChunksScanner::getSpecificFormat() const {
		return AudioContainerFormat::AudioInterchangeFileFormat;
	}





	void AiffChunksScanner::findID3Chunk(AudioTagInformationVector & informationVector, std::istream & readStream,
										 unsigned size, const std::filesystem::path & filePath) const {
		unsigned leftSize = size;
		while (leftSize > 0) {
			priv::ByteArray<4> chunkId = priv::readHeader<4>(readStream);
			unsigned chunkSize = priv::readBigEndianSize(readStream);

			if (chunkSize + 8 > leftSize)
				throw except::FileParseException(filePath, std::uint64_t(readStream.tellg()) - 4,
									 			 except::FileParseException::PositionType::Offset);

			if (chunkId == priv::headers::ID3_CHUNK || chunkId == priv::headers::ID3_CHUNK_LOWER) {
				std::uint64_t id3Offset = readStream.tellg();
				priv::id3::Header header = priv::id3::Header::readHeader(readStream);

				if (header.totalTagSize() != chunkSize)
					throw except::FileParseException(filePath, id3Offset,
						except::FileParseException::PositionType::Offset);
				if (header.tagVersion() == AudioTagFormat::None)
					throw except::FileParseException(filePath,id3Offset + 3,
													 except::FileParseException::PositionType::Offset);

				informationVector.emplace_back(header.tagVersion(), id3Offset, chunkSize);
				return;
			}
			
			readStream.seekg(chunkSize, std::ios::cur);
			leftSize -= chunkSize + 8;
		}
	}
}