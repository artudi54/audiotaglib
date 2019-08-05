#include "RiffInfoScanner.hpp"
#include <tag/except/StreamParseException.hpp>
#include <tag/priv/read_util.hpp>
#include <tag/priv/id3/Header.hpp>
#include <fstream>
namespace fs = std::filesystem;

namespace tag::scanner {
    static void findAndScanTagChunks(std::vector<AudioTagLocation> & informationVector, std::istream & readStream,
                                        std::uint32_t riffChunkSize) {
        std::uint32_t leftChunkSize, totalChunkSize;

        while (riffChunkSize >= 8) {
            priv::ByteArray<4> header = priv::readHeader<4>(readStream);
            totalChunkSize = leftChunkSize = priv::readLittleEndianNumber(readStream);
            if (totalChunkSize + 8 > riffChunkSize)
                throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 4);

            if (header == priv::headers::LIST_CHUNK && leftChunkSize >= 4) {
                leftChunkSize -= 4;
                if (priv::readAndEquals(readStream, priv::headers::INFO_CHUNK))
                    informationVector.emplace_back(AudioTagFormat::RiffInfo,
                                                   std::uint64_t(readStream.tellg()) - 12,
                                                   totalChunkSize + 8);
            }

            else if ((header == priv::headers::ID3_CHUNK || header == priv::headers::ID3_CHUNK_LOWER)
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

    AudioContainerFormat RiffInfoScanner::getSpecificFormat() const noexcept {
        return AudioContainerFormat::WaveAudio;
    }

    void RiffInfoScanner::appendAudioTagInformationImpl(std::vector<AudioTagLocation> &informationVector,
                                                        std::istream &readStream, std::uint64_t fileSize) const {
		if (fileSize >= 44 && priv::readAndEquals(readStream, priv::headers::RIFF_CHUNK)) {
			std::uint32_t riffChunkSize = priv::readLittleEndianNumber(readStream);
			if (riffChunkSize + 8 > fileSize)
				throw except::StreamParseException(4);

			if (priv::readAndEquals(readStream, priv::headers::WAVE))
				findAndScanTagChunks(informationVector, readStream, riffChunkSize - 4);
		}
	}
}
