#include "VorbisCommentsReader.hpp"
#include <tag/priv/read_util.hpp>
#include <tag/priv/vorbis/split.hpp>
#include <tag/priv/vorbis/ValueProcessor.hpp>
#include <tag/priv/ogg/Header.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
namespace io = boost::iostreams;
namespace arc = boost::archive::iterators;

namespace tag::reader {
    enum class Option {
        FLAC_IMAGE,
        VORBIS_IMAGE
    };
    static AudioTagMap readTagImpl(std::istream &readStream, Option option) {
        std::string decoded;
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

            if (option == Option::VORBIS_IMAGE && key == "METADATA_BLOCK_PICTURE"s) {
                using Transform = arc::transform_width<arc::binary_from_base64<std::string_view::const_iterator>, 8, 6>;
                decoded = std::string(Transform(value.begin()), Transform(value.end()));
                value = decoded;
            }

            priv::vorbis::SharedValueProcessor processor = priv::vorbis::getValueProcessor(key);
            if (processor != nullptr)
                processor->process(value, map);
        }

        bool framingBit = readStream.get() != 0;

        if (!framingBit)
            throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 1);

        return map;
    }

    static std::vector<std::byte> unpackData(std::istream &readStream) {
        std::vector<std::byte> data;
        priv::ogg::Header header = priv::ogg::Header::readHeader(readStream);
        if (!header.isValid())
            throw except::StreamParseException(static_cast<std::uint64_t>(readStream.tellg()) - priv::ogg::Header::HEADER_SIZE);
        if (!priv::readAndEquals(readStream, priv::headers::OGG_VORBIS))
            throw except::StreamParseException(static_cast<std::uint64_t>(readStream.tellg()) - priv::headers::OGG_VORBIS.size());
        data.resize(header.getPageSize() - priv::headers::OGG_VORBIS.size());
        readStream.read(reinterpret_cast<char*>(data.data()), data.size());

        std::uint32_t pageNumber = header.getPageSequenceNumber() + 1;
        while (!header.isContinuation()) {
            header = priv::ogg::Header::readHeader(readStream);
            if (!header.isValid())
                throw except::StreamParseException(static_cast<std::uint64_t>(readStream.tellg()) - priv::ogg::Header::HEADER_SIZE);
            if (pageNumber != header.getPageSequenceNumber())
                throw except::StreamParseException(static_cast<std::uint64_t>(readStream.tellg()) - priv::ogg::Header::HEADER_SIZE + 16);
            readStream.seekg(header.getPageSize(), std::ios::cur);
            ++pageNumber;
            std::size_t offset = data.size();
            data.resize(data.size() + header.getPageSize());
            readStream.read(reinterpret_cast<char*>(data.size() + offset), header.getPageSize());
        }
        return data;
    }

    AudioTagMap VorbisCommentsReader::readTag(std::istream &readStream) const {
        priv::ByteArray<4> header = priv::readHeader<4>(readStream);
        readStream.seekg(-4, std::ios::cur);

        if (header == priv::headers::OGG) {
            std::vector<std::byte> data = unpackData(readStream);
            io::array_source source(reinterpret_cast<char*>(data.data()), data.size());
            io::stream<io::array_source> dataStream(source);
            return readTagImpl(dataStream, Option::VORBIS_IMAGE);
            return {};
        }
        else
            return readTagImpl(readStream, Option::FLAC_IMAGE);
    }
}