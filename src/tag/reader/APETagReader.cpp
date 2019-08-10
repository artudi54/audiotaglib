#include "APETagReader.hpp"
#include <tag/priv/read_util.hpp>
#include <tag/priv/ape/ValueProcessor.hpp>

//todo: priority over ID3v1
namespace tag::reader {
	TagMap APETagReader::readTag(std::istream & readStream) const {
		TagMap map;

		if (!priv::readAndEquals(readStream, priv::headers::APE))
			throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 8);

		std::uint32_t version = priv::readLittleEndianNumber(readStream);
		std::uint32_t size = priv::readLittleEndianNumber(readStream);
		std::uint32_t itemCount = priv::readLittleEndianNumber(readStream);
		std::uint32_t flags = priv::readLittleEndianNumber(readStream);

        std::ignore = version;
        std::ignore = flags;

		readStream.seekg(8 - std::streamoff(size), std::ios::cur);

		while (itemCount-- > 0 && size > 0) {
			std::uint32_t valueSize = priv::readLittleEndianNumber(readStream);
			std::uint32_t itemFlags = priv::readLittleEndianNumber(readStream);
			std::string key = priv::readUtf8(readStream);
			priv::ape::SharedValueProcessor processor = priv::ape::getValueProcessor(key);
			if (processor != nullptr)
				processor->process(readStream, map, valueSize, priv::ape::typeFromFlags(itemFlags));
			else
				readStream.seekg(valueSize, std::ios::cur);
			size -= static_cast<std::uint32_t>(8 + key.size() + 1 + valueSize);
		}

		return map;
	}
}