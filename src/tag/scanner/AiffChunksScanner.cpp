#include "AiffChunksScanner.hpp"
#include <tag/except/StreamParseException.hpp>
#include <tag/priv/read_util.hpp>
#include <tag/priv/id3/Header.hpp>
#include <fstream>

namespace tag::scanner {
    static void findID3Chunk(std::vector<TagContainerLocation> & tagContainerLocations, std::istream & readStream, std::uint32_t size) {
        std::uint32_t leftSize = size;
        while (leftSize > 0) {
            priv::ByteArray<4> chunkId = priv::readHeader<4>(readStream);
            std::uint32_t chunkSize = priv::readBigEndianNumber(readStream);

            if (chunkSize + 8 > leftSize)
                throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 4);

            if (chunkId == priv::headers::ID3_CHUNK || chunkId == priv::headers::ID3_CHUNK_LOWER) {
                std::uint64_t id3Offset = static_cast<std::uint64_t>(readStream.tellg());
                priv::id3::Header header = priv::id3::Header::readHeader(readStream);

                if (header.totalTagSize() != chunkSize)
                    throw except::StreamParseException(id3Offset);
                if (header.tagVersion() == TagContainerFormat::None)
                    throw except::StreamParseException(id3Offset + 3);

                tagContainerLocations.emplace_back(header.tagVersion(), id3Offset, chunkSize);
                return;
            }

            readStream.seekg(chunkSize, std::ios::cur);
            leftSize -= chunkSize + 8;
        }
    }

    ContainerFormat AiffChunksScanner::getAssociatedContainerFormat() const noexcept {
        return ContainerFormat::AudioInterchangeFileFormat;
    }

	void AiffChunksScanner::appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                                            std::istream &readStream, std::uint64_t fileSize) const {
		if (priv::readAndEquals(readStream, priv::headers::FORM_CHUNK)) {
			std::uint32_t formSize = priv::readBigEndianNumber(readStream);
			if (formSize + 4 > fileSize)
				throw except::StreamParseException(static_cast<std::uint64_t>(readStream.tellg()) - 4);

			if (priv::readAndEquals(readStream, priv::headers::AIFF_CHUNK))
				tagContainerLocations.emplace_back(TagContainerFormat::AiffChunks, 0, formSize + 4);

			findID3Chunk(tagContainerLocations, readStream, formSize - 4);
		}
	}
}
