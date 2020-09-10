#include "AiffChunksScanner.hpp"
#include <audiotaglib/except/StreamParseException.hpp>
#include <audiotaglib/priv/headers.hpp>
#include <audiotaglib/priv/id3/Header.hpp>

namespace audiotaglib::tag_scanner {
    ContainerFormat AiffChunksScanner::getAssociatedContainerFormat() const noexcept {
        return ContainerFormat::AudioInterchangeFileFormat;
    }

	void AiffChunksScanner::appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                                            common::ReadStream &readStream) const {
		if (readStream.readHeaderAndEquals(priv::headers::FORM_CHUNK)) {
			std::uint32_t formSize = readStream.readBigEndianNumber();
			if (formSize + 4 > readStream.getSize())
				throw except::StreamParseException(readStream.getSize() - 4);

			if (readStream.readHeaderAndEquals(priv::headers::AIFF_CHUNK))
				tagContainerLocations.emplace_back(TagContainerFormat::AiffChunks, 0, formSize + 4);

			findID3Chunk(tagContainerLocations, readStream, formSize - 4);
		}
	}

    void AiffChunksScanner::findID3Chunk(std::vector<TagContainerLocation> & tagContainerLocations,
                                         common::ReadStream &readStream, std::uint32_t size) {
        std::uint32_t leftSize = size;
        while (leftSize > 0) {
            priv::ByteArray<4> chunkId = readStream.readHeader<4>();
            std::uint32_t chunkSize = readStream.readBigEndianNumber();

            if (chunkSize + 8 > leftSize)
                throw except::StreamParseException(readStream.getPosition() - 4);

            if (chunkId == priv::headers::ID3_CHUNK || chunkId == priv::headers::ID3_CHUNK_LOWER) {
                std::uint64_t id3Offset = readStream.getPosition();
                priv::id3::Header header = priv::id3::Header::readHeader(readStream.getNativeStream());

                if (header.totalTagSize() != chunkSize)
                    throw except::StreamParseException(id3Offset);
                if (header.tagVersion() == TagContainerFormat::None)
                    throw except::StreamParseException(id3Offset + 3);

                tagContainerLocations.emplace_back(header.tagVersion(), id3Offset, chunkSize);
                return;
            }

            readStream.setPosition(chunkSize, common::ReadStream::Offset::CURRENT);
            leftSize -= chunkSize + 8;
        }
    }
}
