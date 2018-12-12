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
    ValueProcessor::ValueProcessor(const std::string &name)
        : name(name) {
    }



    StringProcessor::StringProcessor(const std::string &name)
     : ValueProcessor(name) {
    }

    void StringProcessor::process(const std::string_view &value, AudioTagMap &map) const {
        map.setStringTag(name, std::string(value));
    }



    MultiStringProcessor::MultiStringProcessor(const std::string &name)
        : ValueProcessor(name){
    }

    void MultiStringProcessor::process(const std::string_view &value, AudioTagMap &map) const {
        SharedStringAudioTag stringAudioTag = map.getStringTag(name);
        if (stringAudioTag != nullptr)
            stringAudioTag->getText() += "; " + processMultiString(std::string(value));
        else
            map.setStringTag(name, std::string(value));
    }



    NumberProcessor::NumberProcessor(const std::string &name)
        : ValueProcessor(name) {
    }

    void NumberProcessor::process(const std::string_view &value, AudioTagMap &map) const {
        try {
            std::uint32_t number = std::stoul(std::string(value));
            map.setNumberTag(name, number);
        }
        catch (std::logic_error&) {}
    }



    DateProcessor::DateProcessor(const std::string &name)
        : ValueProcessor(name) {
    }

    void DateProcessor::process(const std::string_view &value, AudioTagMap &map) const {
        types::Date date = types::Date::parseString(value);
        if (!date.isEmpty())
            map.setDateTag(name, date);
    }



    ISRCProcessor::ISRCProcessor()
            : ValueProcessor(std::string()) {
    }

    void ISRCProcessor::process(const std::string_view &value, AudioTagMap &map) const {
        types::ISRC isrc(value);
        if (!isrc.isEmpty())
            map.setISRCTag(isrc);
    }



    BarcodeProcessor::BarcodeProcessor()
            : ValueProcessor(std::string()) {
    }

    void BarcodeProcessor::process(const std::string_view &value, AudioTagMap &map) const {
        types::Barcode barcode(value);
        if (!barcode.isEmpty())
            map.setBarcodeTag(barcode);
    }



	ImageProcessor::ImageProcessor()
		: ValueProcessor(std::string()) {
	}

	void ImageProcessor::process(const std::string_view & value, AudioTagMap & map) const {
		io::array_source source(value.data(), value.size());
		io::stream<io::array_source> readStream(source);
		processStream(readStream, static_cast<std::uint32_t>(value.size()), map);
	}

	void ImageProcessor::processStream(std::istream & readStream, std::uint32_t size, AudioTagMap & map) const {
		std::uint64_t before, after;

		before = readStream.tellg();
		ImageAudioTag::ImageType imageType = static_cast<ImageAudioTag::ImageType>(priv::readBigEndianNumber(readStream));
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

		map.setImageTag(imageType, types::Image(std::move(imageData), description, mimeType));
		
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
        {"ALBUM"s, std::make_shared<StringProcessor>(AudioTagMap::ALBUM())},
        {"ALBUMARTIST"s, std::make_shared<MultiStringProcessor>(AudioTagMap::ALBUMARTIST())},
        {"ALBUMARTISTSORT"s, std::make_shared<MultiStringProcessor>(AudioTagMap::ALBUMARTISTSORT())},
        {"ALBUMSORT"s, std::make_shared<StringProcessor>(AudioTagMap::ALBUMSORT())},
        {"ARRANGER"s, std::make_shared<MultiStringProcessor>(AudioTagMap::ARRANGER())},
        {"ARTIST"s, std::make_shared<MultiStringProcessor>(AudioTagMap::ARTIST())},
        {"AUTHOR"s, std::make_shared<MultiStringProcessor>(AudioTagMap::LYRICIST())},
        {"BARCODE"s, std::make_shared<BarcodeProcessor>()},
        {"BPM"s, std::make_shared<NumberProcessor>(AudioTagMap::BPM())},
        {"COMPOSER"s, std::make_shared<MultiStringProcessor>(AudioTagMap::COMPOSER())},
        {"CONDUCTOR"s, std::make_shared<MultiStringProcessor>(AudioTagMap::CONDUCTOR())},
        {"COPYRIGHT"s, std::make_shared<StringProcessor>(AudioTagMap::COPYRIGHT())},
        {"DATE"s, std::make_shared<DateProcessor>(AudioTagMap::DATE())},
        {"DISCNUMBER"s, std::make_shared<NumberProcessor>(AudioTagMap::DISCNUMBER())},
        {"DISCSUBTITLE"s, std::make_shared<StringProcessor>(AudioTagMap::SETSUBTITLE())},
        {"DISCTOTAL"s, std::make_shared<NumberProcessor>(AudioTagMap::TOTALDISCNUMBER())},
        {"DJMIXER"s, std::make_shared<StringProcessor>(AudioTagMap::MIXDJ())},
        {"ENCODED-BY"s, std::make_shared<StringProcessor>(AudioTagMap::ENCODEDBY())},
        {"ENCODING"s, std::make_shared<StringProcessor>(AudioTagMap::ENCODERSETTINGS())},
        {"ENCODERSETTINGS"s, std::make_shared<StringProcessor>(AudioTagMap::ENCODERSETTINGS())},
        {"ENCODERSETTINGS"s, std::make_shared<StringProcessor>(AudioTagMap::ENCODERSETTINGS())},
        {"ENCODER-SETTINGS"s, std::make_shared<StringProcessor>(AudioTagMap::ENCODERSETTINGS())},
        {"ENGINEER"s, std::make_shared<StringProcessor>(AudioTagMap::ENGINEER())},
        {"GENRE"s, std::make_shared<MultiStringProcessor>(AudioTagMap::GENRE())},
        {"GROUPING"s, std::make_shared<StringProcessor>(AudioTagMap::CONTENTGROUP())},
        {"ISRC"s, std::make_shared<ISRCProcessor>()},
        {"LABEL"s, std::make_shared<StringProcessor>(AudioTagMap::PUBLISHER())},
        {"LYRICIST"s, std::make_shared<MultiStringProcessor>(AudioTagMap::LYRICIST())},
        {"METADATA_BLOCK_PICTURE"s, std::make_shared<ImageProcessor>()},
        {"MIXER"s, std::make_shared<StringProcessor>(AudioTagMap::MIXENGINEER())},
        {"MOOD"s, std::make_shared<StringProcessor>(AudioTagMap::MOOD())},
        {"ORGANIZATION"s, std::make_shared<StringProcessor>(AudioTagMap::PUBLISHER())},
        {"ORIGINALALBUM"s, std::make_shared<StringProcessor>(AudioTagMap::ORIGINALALBUM())},
        {"ORIGINALDATE"s, std::make_shared<DateProcessor>(AudioTagMap::ORIGINALDATE())},
        {"ORIGINALLYRICIST"s, std::make_shared<MultiStringProcessor>(AudioTagMap::ORIGINALLYRICIST())},
        {"PRODUCER"s, std::make_shared<StringProcessor>(AudioTagMap::PRODUCER())},
        {"PUBLISHER"s, std::make_shared<StringProcessor>(AudioTagMap::PUBLISHER())},
        {"REMIXER"s, std::make_shared<StringProcessor>(AudioTagMap::REMIXER())},
        {"SUBTITLE"s, std::make_shared<StringProcessor>(AudioTagMap::SUBTITLE())},
        {"TITLE"s, std::make_shared<StringProcessor>(AudioTagMap::TITLE())},
        {"TITLESORT"s, std::make_shared<StringProcessor>(AudioTagMap::TITLESORT())},
        {"TOTALDISCS"s, std::make_shared<NumberProcessor>(AudioTagMap::TOTALDISCNUMBER())},
        {"TOTALTRACKS"s, std::make_shared<NumberProcessor>(AudioTagMap::TOTALTRACKNUMBER())},
        {"TRACKNUMBER"s, std::make_shared<NumberProcessor>(AudioTagMap::TRACKNUMBER())},
        {"TRACKTOTAL"s, std::make_shared<NumberProcessor>(AudioTagMap::TOTALTRACKNUMBER())},
        {"WRITER"s, std::make_shared<MultiStringProcessor>(AudioTagMap::LYRICIST())}
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


