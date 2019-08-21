#include "ValueProcessor.hpp"
#include <tag/priv/read_util.hpp>
#include <tag/priv/icomp.hpp>
#include <boost/algorithm/string.hpp>
#include <unordered_map>

namespace tag::priv::ape {
	ValueProcessor::ValueProcessor(const std::string & name)
		: name(name) {
	}



	StringProcessor::StringProcessor(const std::string & name)
		: ValueProcessor(name) {
	}

	void StringProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size, ValueType valueType) {
		if (valueType != ValueType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		std::string text = readUtf8(readStream, size);
		if (!text.empty())
			map.setStringTag(name, text);
	}



	MultiStringProcessor::MultiStringProcessor(const std::string & name)
		: ValueProcessor(name) {
	}

	void MultiStringProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size, ValueType valueType) {
		if (valueType != ValueType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		std::string text = readUtf8(readStream, size);
		if (!text.empty())
			map.setStringTag(name, processMultiString(text));
	}

	

	NumberProcessor::NumberProcessor(const std::string & name)
		: ValueProcessor(name) {
	}

	void NumberProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size, ValueType valueType) {
		if (valueType != ValueType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}

		std::string numStr = readUtf8(readStream, size);
		try {
			std::uint32_t number = static_cast<std::uint32_t>(std::stoul(numStr));
			map.setNumberTag(name, number);
		}
		catch (std::logic_error &) {}
	}



	DoubleNumberProcessor::DoubleNumberProcessor(const std::string & name, const std::string &secondName)
		: ValueProcessor(name), secondName(secondName) {
	}

	void DoubleNumberProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size, ValueType valueType) {
		if (valueType != ValueType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}

		std::string all = readUtf8(readStream, size);
		std::vector<std::string> splitted;
		std::uint32_t number;

		boost::split(splitted, all, boost::is_any_of("/\\"), boost::token_compress_on);

		try {
			if (splitted.size() >= 1) {
				number = static_cast<std::uint32_t>(std::stol(splitted[0]));
				map.setNumberTag(name, number);
			}
			if (splitted.size() >= 2) {
				number = static_cast<std::uint32_t>(std::stol(splitted[1]));
				map.setNumberTag(secondName, number);
			}
		}
		catch (std::logic_error&) {}
	}



	DateProcessor::DateProcessor(const std::string &name)
		: ValueProcessor(name) {}

	void DateProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size, ValueType valueType) {
		if (valueType != ValueType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}

		std::string dateStr = readUtf8(readStream, size);
		types::Date date = types::Date::parseString(dateStr);
		if (!date.isEmpty())
			map.setDateTag(name, date);
	}



	GenreProcessor::GenreProcessor()
		: ValueProcessor(TagMap::GENRE()) {}

	void GenreProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size, ValueType valueType) {
		if (valueType != ValueType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}

		std::string genreStr = readUtf8(readStream, size);
		if (!genreStr.empty())
			map.setStringTag(name, processGenreString(genreStr));
	}



	ISRCProcessor::ISRCProcessor()
		: ValueProcessor(TagMap::ISRC()) {}

	void ISRCProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size, ValueType valueType) {
		if (valueType != ValueType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}

		std::string isrcStr = readUtf8(readStream, size);
		types::ISRC isrc(isrcStr);
		if (!isrc.isEmpty())
			map.setISRCTag(name, isrc);
	}



    BarcodeProcessor::BarcodeProcessor()
            : ValueProcessor(TagMap::BARCODE()) {}

    void BarcodeProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size, ValueType valueType) {
        if (valueType != ValueType::String) {
            readStream.seekg(size, std::ios::cur);
            return;
        }

        std::string barcodeStr = readUtf8(readStream, size);
        types::Barcode barcode(barcodeStr);
        if (!barcode.isEmpty())
            map.setBarcodeTag(name, barcode);
    }



	LyricsProcessor::LyricsProcessor()
		: ValueProcessor(TagMap::LYRICSENG()) {}

	void LyricsProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size, ValueType valueType) {
		if (valueType != ValueType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}

		std::string lyrics = readUtf8(readStream, size);
		if (!lyrics.empty())
			map.setLyricsEng(types::Lyrics(std::string(), lyrics));
	}



	FrontImageProcessor::FrontImageProcessor(const std::string &name)
		: ValueProcessor(name) {}

	void FrontImageProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size, ValueType valueType) {
		static constexpr ByteArray<8>  PNG_HEADER = {
			std::byte(0x89), std::byte(0x50), std::byte(0x4E), std::byte(0x47),
			std::byte(0x0D), std::byte(0x0A), std::byte(0x1A), std::byte(0x0A)
		};

		static constexpr ByteArray<2> JPG_HEADER = { std::byte(0xFF), std::byte(0xD8) };
		static constexpr ByteArray<2> JPG_FOOTER = { std::byte(0xFF), std::byte(0xD9) };
		
		if (valueType != ValueType::Binary) {
			readStream.seekg(size, std::ios::cur);
			return;
		}

		std::uint64_t beforeReadPos = readStream.tellg();
		std::string description = readUtf8(readStream);
		std::uint64_t afterReadPos = readStream.tellg();

		std::uint64_t imageSize = size - (afterReadPos - beforeReadPos);
		std::vector<std::byte> imageData(imageSize);
		readStream.read(reinterpret_cast<char*>(imageData.data()), imageSize);
		
		if (imageSize < 8)
			return;

		types::Image::MimeType mimeType;
		if (std::equal(PNG_HEADER.begin(), PNG_HEADER.end(), imageData.begin()))
			mimeType = types::Image::MimeType::ImagePng;
		else if (std::equal(JPG_HEADER.begin(), JPG_HEADER.end(), imageData.begin()) &&
			std::equal(JPG_FOOTER.rbegin(), JPG_FOOTER.rend(), imageData.rbegin()))
			mimeType = types::Image::MimeType::ImageJpeg;
		else
			return;

		map.setImageTag(name, types::Image(std::move(imageData), description));
	}



    CustomStringProcessor::CustomStringProcessor()
        : StringProcessor(std::string()) {
    }

    void CustomStringProcessor::setName(const std::string &name) {
        this->name = name;
    }



	static const std::unordered_map<std::string, SharedValueProcessor, IHash, IEquals> MAPPED_PROCESSORS = {
		{"ALBUM"s, std::make_shared<StringProcessor>(TagMap::ALBUM())},
		{"ALBUMSORT"s, std::make_shared<StringProcessor>(TagMap::ALBUMSORT())},
		{"ALBUM ARTIST"s, std::make_shared<StringProcessor>(TagMap::ALBUMARTIST())},
		{"ALBUMARTIST"s, std::make_shared<StringProcessor>(TagMap::ALBUMARTIST())},
		{"ALBUMARTISTSORT"s, std::make_shared<StringProcessor>(TagMap::ALBUMARTISTSORT())},
		{"ALBUMSORT"s, std::make_shared<StringProcessor>(TagMap::ALBUMSORT())},
		{"ARRANGER"s, std::make_shared<MultiStringProcessor>(TagMap::ARRANGER())},
		{"ARTIST"s, std::make_shared<MultiStringProcessor>(TagMap::ARTIST())},
		{"ARTISTSORT"s, std::make_shared<MultiStringProcessor>(TagMap::ARTISTSORT())},
		{"BARCODE"s, std::make_shared<BarcodeProcessor>()},
		{"BPM"s, std::make_shared<NumberProcessor>(TagMap::BPM())},
		{"COMMENT"s, std::make_shared<StringProcessor>(TagMap::COMMENT())},
		{"COMPOSER"s, std::make_shared<MultiStringProcessor>(TagMap::COMPOSER())},
		{"CONDUCTOR"s, std::make_shared<StringProcessor>(TagMap::CONDUCTOR())},
		{"COPYRIGHT"s, std::make_shared<StringProcessor>(TagMap::COPYRIGHT())},
		{"DISC"s, std::make_shared<DoubleNumberProcessor>(TagMap::DISCNUMBER(), TagMap::TOTALDISCNUMBER())},
		{"DISCNUMBER"s, std::make_shared<DoubleNumberProcessor>(TagMap::DISCNUMBER(), TagMap::TOTALDISCNUMBER())},
		{"DJMIXER"s, std::make_shared<StringProcessor>(TagMap::MIXDJ())},
		{"DISCSUBTITLE"s, std::make_shared<StringProcessor>(TagMap::SETSUBTITLE())},
		{"DISCTOTAL"s, std::make_shared<NumberProcessor>(TagMap::TOTALDISCNUMBER())},
		{"ENCODEDBY"s, std::make_shared<StringProcessor>(TagMap::ENCODEDBY())},
		{"ENGINEER"s, std::make_shared<StringProcessor>(TagMap::ENGINEER())},
		{"GENRE"s, std::make_shared<GenreProcessor>()},
		{"GROUPING"s, std::make_shared<StringProcessor>(TagMap::CONTENTGROUP())},
		{"ISRC"s, std::make_shared<ISRCProcessor>()},
		{"LABEL"s, std::make_shared<StringProcessor>(TagMap::PUBLISHER())},
		{"LYRICIST"s, std::make_shared<MultiStringProcessor>(TagMap::LYRICIST())},
		{"LYRICS"s, std::make_shared<LyricsProcessor>()},
		{"MIXER"s, std::make_shared<StringProcessor>(TagMap::MIXENGINEER())},
		{"MOOD"s, std::make_shared<StringProcessor>(TagMap::MOOD())},
		{"NETRADIOSTATION"s, std::make_shared<StringProcessor>(TagMap::RADIOSTATION())},
		{"NETRADIOSTATIONNAME"s, std::make_shared<StringProcessor>(TagMap::RADIOSTATION())},
		{"NETRADIOSTATIONOWNER"s, std::make_shared<StringProcessor>(TagMap::RADIOSTATIONOWNER())},
		{"MIXARTIST"s, std::make_shared<StringProcessor>(TagMap::REMIXER())},
		{"MOOD"s, std::make_shared<StringProcessor>(TagMap::MOOD())},
		{"ORIGINALALBUM"s, std::make_shared<StringProcessor>(TagMap::ORIGINALALBUM())},
		{"ORIGINALARTIST"s, std::make_shared<MultiStringProcessor>(TagMap::ORIGINALARTIST())},
		{"ORIGINALLYRICIST"s, std::make_shared<MultiStringProcessor>(TagMap::ORIGINALLYRICIST())},
		{"ORIGINALYEAR"s, std::make_shared<DateProcessor>(TagMap::ORIGINALDATE())},
		{"PRODUCER"s, std::make_shared<StringProcessor>(TagMap::PRODUCER())},
		{"RADIOSTATION"s, std::make_shared<StringProcessor>(TagMap::RADIOSTATION())},
		{"RADIOSTATIONNAME"s, std::make_shared<StringProcessor>(TagMap::RADIOSTATION())},
		{"RADIOSTATIONOWNER"s, std::make_shared<StringProcessor>(TagMap::RADIOSTATIONOWNER())},
		{"PUBLISHER"s, std::make_shared<StringProcessor>(TagMap::PUBLISHER())},
		{"SUBTITLE"s, std::make_shared<StringProcessor>(TagMap::SUBTITLE())},
		{"TITLE"s, std::make_shared<StringProcessor>(TagMap::TITLE())},
		{"TITLESORT"s, std::make_shared<StringProcessor>(TagMap::TITLESORT())},
		{"TOTALTRACKS"s, std::make_shared<NumberProcessor>(TagMap::TOTALTRACKNUMBER())},
		{"TRACK"s, std::make_shared<DoubleNumberProcessor>(TagMap::TRACKNUMBER(), TagMap::TOTALTRACKNUMBER())},
		{"TRACKNUMBER"s, std::make_shared<DoubleNumberProcessor>(TagMap::TRACKNUMBER(), TagMap::TOTALTRACKNUMBER())},
		{"TRACKTOTAL"s, std::make_shared<NumberProcessor>(TagMap::TOTALTRACKNUMBER())},
		{"UNSYNCEDLYRICS"s, std::make_shared<LyricsProcessor>()},
		{"WRITER"s, std::make_shared<MultiStringProcessor>(TagMap::LYRICIST())},
		{"WWWARTIST"s, std::make_shared<StringProcessor>(TagMap::WWWARTIST())},
		{"WWWAUDIOFILE"s, std::make_shared<StringProcessor>(TagMap::WWWFILE())},
		{"WWWAUDIOSOURCE"s, std::make_shared<StringProcessor>(TagMap::WWWFILESOURCE())},
		{"WWWCOMMERCIAL"s, std::make_shared<StringProcessor>(TagMap::WWWCOMMERCIAL())},
		{"WWWCOMMERCIALINFO"s, std::make_shared<StringProcessor>(TagMap::WWWCOMMERCIAL())},
		{"WWWCOPYRIGHT"s, std::make_shared<StringProcessor>(TagMap::WWWCOPYRIGHT())},
		{"WWWFILE"s, std::make_shared<StringProcessor>(TagMap::WWWFILE())},
		{"WWWFILESOURCE"s, std::make_shared<StringProcessor>(TagMap::WWWFILESOURCE())},
		{"WWWPAYMENT"s, std::make_shared<StringProcessor>(TagMap::WWWPAYMENT())},
		{"WWWPODCAST"s, std::make_shared<StringProcessor>(TagMap::WWWPODCAST())},
		{"WWWRADIOPAGE"s, std::make_shared<StringProcessor>(TagMap::WWWRADIOPAGE())},
		{"YEAR"s, std::make_shared<DateProcessor>(TagMap::DATE())},

		{"COVER ART (ARTIST)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGEARTIST())},
		{"COVER ART (BACK)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGECOVERBACK())},
		{"COVER ART (BAND)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGEBAND())},
		{"COVER ART (BAND LOGOTYPE)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGEBANDLOGO())},
		{"COVER ART (COMPOSER)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGECOMPOSER())},
		{"COVER ART (CONDUCTOR)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGECONDUCTOR())},
		{"COVER ART (DURING PERFORMANCE)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGEDURINGPERFORMANCE())},
		{"COVER ART (DURING RECORDING)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGEDURINGRECORDING())},
		{"COVER ART (FISH)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGEABRIGHTCOLOUREDFISH())},
		{"COVER ART (FRONT)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGECOVERFRONT())},
		{"COVER ART (ICON)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGEOTHERICON())},
		{"COVER ART (ILLUSTRATION)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGEILLUSTRATION())},
		{"COVER ART (LEAD ARTIST)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGELEADARTIST())},
		{"COVER ART (LEAFLET)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGELEAFLET())},
		{"COVER ART (LYRICIST)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGELYRICIST())},
		{"COVER ART (MEDIA)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGEMEDIA())},
		{"COVER ART (OTHER)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGEOTHER())},
		{"COVER ART (PNG ICON)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGEICON())},
		{"COVER ART (PUBLISHER LOGOTYPE)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGEPUBLISHERLOGO())},
		{"COVER ART (RECORDING LOCATION)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGERECORDINGLOCATION())},
		{"COVER ART (VIDEO CAPTURE)"s, std::make_shared<FrontImageProcessor>(TagMap::IMAGEVIDEOCAPTURE())}
};

	SharedValueProcessor getValueProcessor(const std::string & name) {
        static thread_local auto customTextProcessor = std::make_shared<CustomStringProcessor>();

        auto it = MAPPED_PROCESSORS.find(name);
		if (it != MAPPED_PROCESSORS.end())
			return it->second;

		customTextProcessor->setName(name);
		return customTextProcessor;
	}
}