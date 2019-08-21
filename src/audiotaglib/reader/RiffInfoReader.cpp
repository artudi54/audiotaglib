#include "RiffInfoReader.hpp"
#include <audiotaglib/priv/read_util.hpp>
#include <audiotaglib/priv/riff/ChunkProcessor.hpp>

namespace audiotaglib::reader{
	TagMap RiffInfoReader::readTag(std::istream & readStream) const {
		TagMap map;

		if (!priv::readAndEquals(readStream, priv::headers::LIST_CHUNK))
			throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 4);

		std::uint32_t size = priv::readLittleEndianNumber(readStream);
		if (size <= 4)
			return map;

		if (!priv::readAndEquals(readStream, priv::headers::INFO_CHUNK))
			throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 4);

		size -= 4;

		while (size > 0) {
			std::string header = priv::readUtf8(readStream, 4);
			std::uint32_t chunkSize = priv::readLittleEndianNumber(readStream);
				if (chunkSize + 8 > size)
				throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 4);

				priv::riff::SharedChunkProcessor processor = priv::riff::getProcessor(header);
			if (processor != nullptr)
				processor->process(readStream, chunkSize, map);
			else
				readStream.seekg(chunkSize, std::ios::cur);

			size -= chunkSize + 8;
			if (chunkSize % 2 == 1) {
				char next = readStream.get();
				if (next == '\0')
					--size;
				else
					readStream.unget();
			}
		}
		return map;
	}
}