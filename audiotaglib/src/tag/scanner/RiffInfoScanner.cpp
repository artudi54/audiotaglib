#include <tag/scanner/RiffInfoScanner.hpp>
#include <tag/priv/read_util.hpp>
#include <tag/priv/id3/Header.hpp>
namespace fs = std::filesystem;

namespace tag::scanner {

	void RiffInfoScanner::appendAudioTagInformation(AudioTagInformationVector& informationVector,
													const fs::path & filePath) const {
		auto[size, readStream] = getValidatedSizeAndStream(filePath);

		if (size >= 44 && priv::readAndEquals(readStream, priv::headers::RIFF_CHUNK)) {
			unsigned riffChunkSize = priv::readLittleEndianSize(readStream);
			if (riffChunkSize + 8 > size)
				throw except::FileParseException(filePath, 4, except::FileParseException::PositionType::Offset);

			if (priv::readAndEquals(readStream, priv::headers::WAVE))
				findAndScanTagChunks(informationVector, readStream, riffChunkSize - 4, filePath);
		}
	}




	AudioContainerFormat RiffInfoScanner::getSpecificFormat() const {
		return AudioContainerFormat::WaveAudio;
	}




	void RiffInfoScanner::findAndScanTagChunks(AudioTagInformationVector & informationVector,
											   std::ifstream & readStream,
											   unsigned riffChunkSize,
											   const fs::path &filePath) const {
		unsigned leftChunkSize, totalChunkSize;

		while (riffChunkSize >= 4) {
			priv::ByteArray<4> header = priv::readHeader<4>(readStream);
			totalChunkSize = leftChunkSize = priv::readLittleEndianSize(readStream);
			if (totalChunkSize + 8 > riffChunkSize)
				throw except::FileParseException(filePath, std::uint64_t(readStream.tellg()) - 4,
												 except::FileParseException::PositionType::Offset);
			
			if (header == priv::headers::LIST_CHUNK && leftChunkSize >= 4) {
				leftChunkSize -= 4;
				if (priv::readAndEquals(readStream, priv::headers::INFO_CHUNK))
					informationVector.emplace_back(AudioTagFormat::RiffInfo,
												   std::uint64_t(readStream.tellg()) - 12,
												   totalChunkSize + 8);
			}
			
			else if ((header == priv::headers::ID3_CHUNK || header == priv::headers::ID3_CHUNK_SMALL)
					&& leftChunkSize >= 10) {
				priv::id3::Header header = priv::id3::Header::readHeader(readStream);
				informationVector.emplace_back(header.tagVersion(),
											   std::uint64_t(readStream.tellg()) - 10,
											   header.totalTagSize());
				leftChunkSize -= 10;
			}

			readStream.seekg(leftChunkSize, std::ios::cur);
			riffChunkSize -= totalChunkSize + 8;
		}
	}
}
