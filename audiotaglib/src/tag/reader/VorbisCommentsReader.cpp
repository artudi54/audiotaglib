#include "VorbisCommentsReader.hpp"
#include <tag/priv/read_util.hpp>
#include <tag/priv/vorbis/split.hpp>
#include <tag/priv/vorbis/ValueProcessor.hpp>

namespace tag::reader {
    AudioTagMap VorbisCommentsReader::readTag(std::istream &readStream) const {
        AudioTagMap map;

        std::uint32_t vendorSize = priv::readLittleEndianNumber(readStream);
        std::string vendorString = priv::readUtf8(readStream, vendorSize);
        std::uint32_t commentsCount = priv::readLittleEndianNumber(readStream);

        std::ignore = vendorString;

        while (commentsCount-- > 0) {
            std::uint32_t commentSize = priv::readLittleEndianNumber(readStream);
            std::string commentPair = priv::readUtf8(readStream, commentSize);
            auto[valid, key, value] = priv::vorbis::split(commentPair);

            if (!valid)
                continue;

            priv::vorbis::SharedValueProcessor processor = priv::vorbis::getValueProcessor(key);
            if (processor != nullptr)
                processor->process(value, map);
        }

        bool framingBit = readStream.get() != 0;

        if (!framingBit)
            throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 1);

        return map;
    }
}