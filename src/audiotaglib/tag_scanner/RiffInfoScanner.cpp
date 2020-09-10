#include "RiffInfoScanner.hpp"
#include <audiotaglib/except/StreamParseException.hpp>
#include <audiotaglib/priv/headers.hpp>
#include <audiotaglib/priv/id3/Header.hpp>
namespace fs = std::filesystem;

namespace audiotaglib::tag_scanner {
    ContainerFormat RiffInfoScanner::getAssociatedContainerFormat() const noexcept {
        return ContainerFormat::WaveAudio;
    }

    void RiffInfoScanner::appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                                          common::ReadStream &readStream) const {
		if (readStream.getSize() >= 44 && readStream.readHeaderAndEquals(priv::headers::RIFF_CHUNK)) {
			std::uint32_t riffChunkSize = readStream.readLittleEndianNumber();
			if (riffChunkSize + 8 > readStream.getSize())
				throw except::StreamParseException(4);

			if (readStream.readHeaderAndEquals(priv::headers::WAVE))
				findAndScanTagChunks(tagContainerLocations, readStream, riffChunkSize - 4);
		}
	}

    void RiffInfoScanner::findAndScanTagChunks(std::vector<TagContainerLocation> & tagContainerLocations,
                                               common::ReadStream & readStream, std::uint32_t riffChunkSize) {
        std::uint32_t leftChunkSize, totalChunkSize;

        while (riffChunkSize >= 8) {
            priv::ByteArray<4> header = readStream.readHeader<4>();
            totalChunkSize = leftChunkSize = readStream.readLittleEndianNumber();
            if (totalChunkSize + 8 > riffChunkSize)
                throw except::StreamParseException(readStream.getPosition() - 4);

            if (header == priv::headers::LIST_CHUNK && leftChunkSize >= 4) {
                leftChunkSize -= 4;
                if (readStream.readHeaderAndEquals(priv::headers::INFO_CHUNK))
                    tagContainerLocations.emplace_back(TagContainerFormat::RiffInfo,
                                                       readStream.getPosition() - 12,
                                                       totalChunkSize + 8);
            }

            else if ((header == priv::headers::ID3_CHUNK || header == priv::headers::ID3_CHUNK_LOWER)
                     && leftChunkSize >= 10) {
                priv::id3::Header header = priv::id3::Header::readHeader(readStream.getNativeStream());
                tagContainerLocations.emplace_back(header.tagVersion(),
                                                   readStream.getPosition() - 10,
                                                   header.totalTagSize());
                leftChunkSize -= 10;
            }

            readStream.setPosition(leftChunkSize, common::ReadStream::Offset::CURRENT);
            riffChunkSize -= totalChunkSize + 8;
        }
    }
}
