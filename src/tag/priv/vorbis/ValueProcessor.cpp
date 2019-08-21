#include "ValueProcessor.hpp"
#include <unordered_map>
#include <tag/priv/icomp.hpp>
#include <tag/priv/read_util.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/algorithm/string.hpp>
namespace mi = boost::multi_index;
namespace io = boost::iostreams;
using namespace std::literals;

namespace tag::priv::vorbis {
    // TODO: multiple repeating keys
    ValueProcessor::ValueProcessor(const std::string &name)
        : name(name) {
    }



    StringProcessor::StringProcessor(const std::string &name)
     : ValueProcessor(name) {
    }

    void StringProcessor::process(const std::string_view &value, TagMap &map) const {
        map.setStringTag(name, std::string(value));
    }



    MultiStringProcessor::MultiStringProcessor(const std::string &name)
        : ValueProcessor(name){
    }

    void MultiStringProcessor::process(const std::string_view &value, TagMap &map) const {
        SharedStringAudioTag stringAudioTag = map.getStringTagPointer(name);
        if (stringAudioTag != nullptr)
            stringAudioTag->getText() += "; " + processMultiString(std::string(value));
        else
            map.setStringTag(name, std::string(value));
    }



    NumberProcessor::NumberProcessor(const std::string &name)
        : ValueProcessor(name) {
    }

    void NumberProcessor::process(const std::string_view &value, TagMap &map) const {
        try {
            std::uint32_t number = std::stoul(std::string(value));
            map.setNumberTag(name, number);
        }
        catch (std::logic_error&) {}
    }



    DateProcessor::DateProcessor(const std::string &name)
        : ValueProcessor(name) {
    }

    void DateProcessor::process(const std::string_view &value, TagMap &map) const {
        types::Date date = types::Date::parseString(value);
        if (!date.isEmpty())
            map.setDateTag(name, date);
    }



    ISRCProcessor::ISRCProcessor()
            : ValueProcessor(TagMap::ISRC()) {
    }

    void ISRCProcessor::process(const std::string_view &value, TagMap &map) const {
        types::ISRC isrc(value);
        if (!isrc.isEmpty())
            map.setISRCTag(name, isrc);
    }



    BarcodeProcessor::BarcodeProcessor()
            : ValueProcessor(TagMap::BARCODE()) {
    }

    void BarcodeProcessor::process(const std::string_view &value, TagMap &map) const {
        types::Barcode barcode(value);
        if (!barcode.isEmpty())
            map.setBarcodeTag(name, barcode);
    }



	ImageProcessor::ImageProcessor()
		: ValueProcessor(std::string()) {
	}

	void ImageProcessor::process(const std::string_view & value, TagMap & map) const {
		io::array_source source(value.data(), value.size());
		io::stream<io::array_source> readStream(source);
		processStream(readStream, static_cast<std::uint32_t>(value.size()), map);
	}

	void ImageProcessor::processStream(std::istream & readStream, std::uint32_t size, TagMap & map) const {
		std::uint64_t before, after;

		before = readStream.tellg();
		ImageTag::ImageType imageType = static_cast<ImageTag::ImageType>(priv::readBigEndianNumber(readStream));
		std::uint32_t mimeLength = priv::readBigEndianNumber(readStream);
		std::string mimeTypeStr = priv::readUtf8(readStream, mimeLength);
		types::Image::MimeType mimeType = string::parseImageMimeType(mimeTypeStr);
		after = readStream.tellg();

		if (mimeType == types::Image::MimeType::None) {
			readStream.seekg(size - (after - before), std::ios::cur);
			return;
		}

		std::uint32_t descriptionLength = priv::readBigEndianNumber(readStream);
		std::string description = priv::readUtf8(readStream, descriptionLength);
		std::uint32_t width = priv::readBigEndianNumber(readStream);
		std::uint32_t height = priv::readBigEndianNumber(readStream);
		std::uint32_t colorDepth = priv::readBigEndianNumber(readStream);
		std::uint32_t colorCount = priv::readBigEndianNumber(readStream);
		std::uint32_t imageLength = priv::readBigEndianNumber(readStream);
		std::vector<std::byte> imageData(imageLength);
		readStream.read(reinterpret_cast<char*>(imageData.data()), imageLength);

		std::ignore = width;
		std::ignore = height;
		std::ignore = colorDepth;
		std::ignore = colorCount;

		map.setImageTag(imageType, types::Image(std::move(imageData), description));
		
		after = readStream.tellg();
		readStream.seekg(size - (after - before), std::ios::cur);
	}



    CustomStringProcessor::CustomStringProcessor()
        : StringProcessor(std::string()) {}

    void CustomStringProcessor::setName(const std::string &name) {
        this->name = name;
    }


    using Map = mi::multi_index_container<
                    std::pair<std::string, SharedValueProcessor>,
                    mi::indexed_by<
                        mi::hashed_unique<
                            mi::member<
                                std::pair<std::string, SharedValueProcessor>,
                                std::string,
                                &std::pair<std::string, SharedValueProcessor>::first
                            >,
                            IHash,
                            IEquals
                        >
                    >
    >;

    // todo: review multistring and string options in all processors
    static const Map MAPPED_PROCESSORS = {
        {"ALBUM"s, std::make_shared<StringProcessor>(TagMap::ALBUM())},
        {"ALBUMARTIST"s, std::make_shared<MultiStringProcessor>(TagMap::ALBUMARTIST())},
        {"ALBUMARTISTSORT"s, std::make_shared<MultiStringProcessor>(TagMap::ALBUMARTISTSORT())},
        {"ALBUMSORT"s, std::make_shared<StringProcessor>(TagMap::ALBUMSORT())},
        {"ARRANGER"s, std::make_shared<MultiStringProcessor>(TagMap::ARRANGER())},
        {"ARTIST"s, std::make_shared<MultiStringProcessor>(TagMap::ARTIST())},
        {"AUTHOR"s, std::make_shared<MultiStringProcessor>(TagMap::LYRICIST())},
        {"BARCODE"s, std::make_shared<BarcodeProcessor>()},
        {"BPM"s, std::make_shared<NumberProcessor>(TagMap::BPM())},
        {"COMPOSER"s, std::make_shared<MultiStringProcessor>(TagMap::COMPOSER())},
        {"CONDUCTOR"s, std::make_shared<MultiStringProcessor>(TagMap::CONDUCTOR())},
        {"COPYRIGHT"s, std::make_shared<StringProcessor>(TagMap::COPYRIGHT())},
        {"DATE"s, std::make_shared<DateProcessor>(TagMap::DATE())},
        {"DISCNUMBER"s, std::make_shared<NumberProcessor>(TagMap::DISCNUMBER())},
        {"DISCSUBTITLE"s, std::make_shared<StringProcessor>(TagMap::SETSUBTITLE())},
        {"DISCTOTAL"s, std::make_shared<NumberProcessor>(TagMap::TOTALDISCNUMBER())},
        {"DJMIXER"s, std::make_shared<StringProcessor>(TagMap::MIXDJ())},
        {"ENCODED-BY"s, std::make_shared<StringProcessor>(TagMap::ENCODEDBY())},
        {"ENCODING"s, std::make_shared<StringProcessor>(TagMap::ENCODERSETTINGS())},
        {"ENCODERSETTINGS"s, std::make_shared<StringProcessor>(TagMap::ENCODERSETTINGS())},
        {"ENCODERSETTINGS"s, std::make_shared<StringProcessor>(TagMap::ENCODERSETTINGS())},
        {"ENCODER-SETTINGS"s, std::make_shared<StringProcessor>(TagMap::ENCODERSETTINGS())},
        {"ENGINEER"s, std::make_shared<StringProcessor>(TagMap::ENGINEER())},
        {"GENRE"s, std::make_shared<MultiStringProcessor>(TagMap::GENRE())},
        {"GROUPING"s, std::make_shared<StringProcessor>(TagMap::CONTENTGROUP())},
        {"ISRC"s, std::make_shared<ISRCProcessor>()},
        {"LABEL"s, std::make_shared<StringProcessor>(TagMap::PUBLISHER())},
        {"LYRICIST"s, std::make_shared<MultiStringProcessor>(TagMap::LYRICIST())},
        {"METADATA_BLOCK_PICTURE"s, std::make_shared<ImageProcessor>()},
        {"MIXER"s, std::make_shared<StringProcessor>(TagMap::MIXENGINEER())},
        {"MOOD"s, std::make_shared<StringProcessor>(TagMap::MOOD())},
        {"ORGANIZATION"s, std::make_shared<StringProcessor>(TagMap::PUBLISHER())},
        {"ORIGINALALBUM"s, std::make_shared<StringProcessor>(TagMap::ORIGINALALBUM())},
        {"ORIGINALDATE"s, std::make_shared<DateProcessor>(TagMap::ORIGINALDATE())},
        {"ORIGINALLYRICIST"s, std::make_shared<MultiStringProcessor>(TagMap::ORIGINALLYRICIST())},
        {"PRODUCER"s, std::make_shared<StringProcessor>(TagMap::PRODUCER())},
        {"PUBLISHER"s, std::make_shared<StringProcessor>(TagMap::PUBLISHER())},
        {"REMIXER"s, std::make_shared<StringProcessor>(TagMap::REMIXER())},
        {"SUBTITLE"s, std::make_shared<StringProcessor>(TagMap::SUBTITLE())},
        {"TITLE"s, std::make_shared<StringProcessor>(TagMap::TITLE())},
        {"TITLESORT"s, std::make_shared<StringProcessor>(TagMap::TITLESORT())},
        {"TOTALDISCS"s, std::make_shared<NumberProcessor>(TagMap::TOTALDISCNUMBER())},
        {"TOTALTRACKS"s, std::make_shared<NumberProcessor>(TagMap::TOTALTRACKNUMBER())},
        {"TRACKNUMBER"s, std::make_shared<NumberProcessor>(TagMap::TRACKNUMBER())},
        {"TRACKTOTAL"s, std::make_shared<NumberProcessor>(TagMap::TOTALTRACKNUMBER())},
        {"WRITER"s, std::make_shared<MultiStringProcessor>(TagMap::LYRICIST())}
    };


    SharedValueProcessor getValueProcessor(const std::string_view &name) {
        static thread_local auto customStringProcessor = std::make_shared<CustomStringProcessor>();

        auto it = MAPPED_PROCESSORS.find(name);
        if (it != MAPPED_PROCESSORS.end())
            return it->second;

        customStringProcessor->setName(boost::to_upper_copy(std::string(name)));
        return customStringProcessor;
    }
}


