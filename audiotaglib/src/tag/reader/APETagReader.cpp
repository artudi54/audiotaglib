#include "APETagReader.hpp"
#include <tag/priv/read_util.hpp>
#include <tag/priv/ape/ValueProcessor.hpp>

//todo: priority over ID3v1
namespace tag::reader {
	AudioTagMap APETagReader::readTag(std::istream & readStream) const {
		AudioTagMap map;

		if (!priv::readAndEquals(readStream, priv::headers::APE))
			throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 8);

		unsigned version = priv::readLittleEndianNumber(readStream);
		unsigned size = priv::readLittleEndianNumber(readStream);
		unsigned itemCount = priv::readLittleEndianNumber(readStream);
		unsigned flags = priv::readLittleEndianNumber(readStream);

        std::ignore = version;
        std::ignore = flags;

		readStream.seekg(8 - std::streamoff(size), std::ios::cur);

		while (itemCount-- > 0 && size > 0) {
			unsigned valueSize = priv::readLittleEndianNumber(readStream);
			unsigned itemFlags = priv::readLittleEndianNumber(readStream);
			std::string key = priv::readUtf8(readStream);
			priv::ape::SharedValueProcessor processor = priv::ape::getValueProcessor(key);
			if (processor != nullptr)
				processor->process(readStream, map, valueSize, priv::ape::typeFromFlags(itemFlags));
			else
				readStream.seekg(valueSize, std::ios::cur);
			size -= static_cast<unsigned>(8 + key.size() + 1 + valueSize);
		}

		return map;
	}


}