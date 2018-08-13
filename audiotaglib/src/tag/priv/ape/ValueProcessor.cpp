#include "ValueProcessor.hpp"
#include <tag/priv/read_util.hpp>
#include <tag/priv/ape/icomp.hpp>
#include <boost/algorithm/string.hpp>
#include <unordered_map>

namespace tag::priv::ape {
	ValueProcessor::ValueProcessor(const std::string & name)
		: name(name) {
	}



	StringProcessor::StringProcessor(const std::string & name)
		: ValueProcessor(name) {
	}

	void StringProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size, ValueType valueType) {
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

	void MultiStringProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size, ValueType valueType) {
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

	void NumberProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size, ValueType valueType) {
		if (valueType != ValueType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}

		std::string numStr = readUtf8(readStream, size);
		try {
			unsigned number = static_cast<unsigned>(std::stoul(numStr));
			map.setNumberTag(name, number);
		}
		catch (std::logic_error &) {}
	}



	DoubleNumberProcessor::DoubleNumberProcessor(const std::string & name, const std::string &secondName)
		: ValueProcessor(name), secondName(secondName) {
	}

	void DoubleNumberProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size, ValueType valueType) {
		if (valueType != ValueType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}

		std::string all = readUtf8(readStream, size);
		std::vector<std::string> splitted;
		unsigned number;

		boost::split(splitted, all, boost::is_any_of("/\\"), boost::token_compress_on);

		try {
			if (splitted.size() >= 1) {
				number = static_cast<unsigned>(std::stol(splitted[0]));
				map.setNumberTag(name, number);
			}
			if (splitted.size() >= 2) {
				number = static_cast<unsigned>(std::stol(splitted[1]));
				map.setNumberTag(secondName, number);
			}
		}
		catch (std::logic_error&) {}
	}



	DateProcessor::DateProcessor(const std::string &name)
		: ValueProcessor(name) {}

	void DateProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size, ValueType valueType) {
		if (valueType != ValueType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}

		std::string dateStr = readUtf8(readStream, size);
		types::Date date = types::Date::parseString(dateStr);
		if (!date.isNull())
			map.setDateTag(name, date);
	}



	GenreProcessor::GenreProcessor()
		: ValueProcessor(AudioTagMap::GENRE()) {}

	void GenreProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size, ValueType valueType) {
		if (valueType != ValueType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}

		std::string genreStr = readUtf8(readStream, size);
		if (!genreStr.empty())
			map.setStringTag(name, processGenreString(genreStr));
	}



	ISRCProcessor::ISRCProcessor()
		: ValueProcessor(std::string()) {}

	void ISRCProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size, ValueType valueType) {
		if (valueType != ValueType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}

		std::string isrcStr = readUtf8(readStream, size);
		types::ISRC isrc(isrcStr);
		if (!isrc.isEmpty())
			map.setISRCTag(isrc);
	}



	LyricsProcessor::LyricsProcessor()
		: ValueProcessor(AudioTagMap::LYRICSENG()) {}

	void LyricsProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size, ValueType valueType) {
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

	void FrontImageProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size, ValueType valueType) {
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

		types::Image::MimeType mimeType = types::Image::MimeType::None;
		if (std::equal(PNG_HEADER.begin(), PNG_HEADER.end(), imageData.begin()))
			mimeType = types::Image::MimeType::ImagePng;
		else if (std::equal(JPG_HEADER.begin(), JPG_HEADER.end(), imageData.begin()) &&
			std::equal(JPG_FOOTER.rbegin(), JPG_FOOTER.rend(), imageData.rbegin()))
			mimeType = types::Image::MimeType::ImageJpeg;
		else
			return;


		map.setImageTag(name, types::Image(std::move(imageData), description, mimeType));
	}



    CustomStringProcessor::CustomStringProcessor()
        : StringProcessor(std::string()) {
    }

    void CustomStringProcessor::setName(const std::string &name) {
        this->name = name;
    }



	static const std::unordered_map<std::string, SharedValueProcessor, IHash, IEquals> MAPPED_PROCESSORS = {
        {"ALBUM"s, std::make_shared<StringProcessor>(AudioTagMap::ALBUM())}, //todo: shorten other code this way
		std::make_pair("ALBUMSORT"s, std::make_shared<StringProcessor>(AudioTagMap::ALBUMSORT())),
		std::make_pair("ALBUM ARTIST"s, std::make_shared<StringProcessor>(AudioTagMap::ALBUMARTIST())),
		std::make_pair("ALBUMARTIST"s, std::make_shared<StringProcessor>(AudioTagMap::ALBUMARTIST())),
		std::make_pair("ALBUMARTISTSORT"s, std::make_shared<StringProcessor>(AudioTagMap::ALBUMARTISTSORT())),
		std::make_pair("ALBUMSORT"s, std::make_shared<StringProcessor>(AudioTagMap::ALBUMSORT())),
		std::make_pair("ARRANGER"s, std::make_shared<MultiStringProcessor>(AudioTagMap::ARRANGER())),
		std::make_pair("ARTIST"s, std::make_shared<MultiStringProcessor>(AudioTagMap::ARTIST())),
		std::make_pair("ARTISTSORT"s, std::make_shared<MultiStringProcessor>(AudioTagMap::ARTISTSORT())),
		std::make_pair("BPM"s, std::make_shared<NumberProcessor>(AudioTagMap::BPM())),
		std::make_pair("COMMENT"s, std::make_shared<StringProcessor>(AudioTagMap::COMMENT())),
		std::make_pair("COMPOSER"s, std::make_shared<MultiStringProcessor>(AudioTagMap::COMPOSER())),
		std::make_pair("CONDUCTOR"s, std::make_shared<StringProcessor>(AudioTagMap::CONDUCTOR())),
		std::make_pair("COPYRIGHT"s, std::make_shared<StringProcessor>(AudioTagMap::COPYRIGHT())),
		std::make_pair("DISC"s, std::make_shared<DoubleNumberProcessor>(AudioTagMap::DISCNUMBER(), AudioTagMap::TOTALDISCNUMBER())),
		std::make_pair("DISCNUMBER"s, std::make_shared<DoubleNumberProcessor>(AudioTagMap::DISCNUMBER(), AudioTagMap::TOTALDISCNUMBER())),
		std::make_pair("DJMIXER"s, std::make_shared<StringProcessor>(AudioTagMap::MIXDJ())),
		std::make_pair("DISCSUBTITLE"s, std::make_shared<StringProcessor>(AudioTagMap::SETSUBTITLE())),
		std::make_pair("DISCTOTAL"s, std::make_shared<NumberProcessor>(AudioTagMap::TOTALDISCNUMBER())),
		std::make_pair("ENCODEDBY"s, std::make_shared<StringProcessor>(AudioTagMap::ENCODEDBY())),
		std::make_pair("ENGINEER"s, std::make_shared<StringProcessor>(AudioTagMap::ENGINEER())),
		std::make_pair("GENRE"s, std::make_shared<GenreProcessor>()),
		std::make_pair("GROUPING"s, std::make_shared<StringProcessor>(AudioTagMap::CONTENTGROUP())),
		std::make_pair("ISRC"s, std::make_shared<ISRCProcessor>()),
		std::make_pair("LABEL"s, std::make_shared<StringProcessor>(AudioTagMap::PUBLISHER())),
		std::make_pair("LYRICIST"s, std::make_shared<MultiStringProcessor>(AudioTagMap::LYRICIST())),
		std::make_pair("LYRICS"s, std::make_shared<LyricsProcessor>()),
		std::make_pair("MIXER"s, std::make_shared<StringProcessor>(AudioTagMap::MIXENGINEER())),
		std::make_pair("MOOD"s, std::make_shared<StringProcessor>(AudioTagMap::MOOD())),
        std::make_pair("NETRADIOSTATION"s, std::make_shared<StringProcessor>(AudioTagMap::RADIOSTATION())),
        std::make_pair("NETRADIOSTATIONNAME"s, std::make_shared<StringProcessor>(AudioTagMap::RADIOSTATION())),
        std::make_pair("NETRADIOSTATIONOWNER"s, std::make_shared<StringProcessor>(AudioTagMap::RADIOSTATIONOWNER())),
        std::make_pair("MIXARTIST"s, std::make_shared<StringProcessor>(AudioTagMap::REMIXER())),
        std::make_pair("MOOD"s, std::make_shared<StringProcessor>(AudioTagMap::MOOD())),
        std::make_pair("ORIGINALALBUM"s, std::make_shared<StringProcessor>(AudioTagMap::ORIGINALALBUM())),
		std::make_pair("ORIGINALARTIST"s, std::make_shared<MultiStringProcessor>(AudioTagMap::ORIGINALARTIST())),
		std::make_pair("ORIGINALLYRICIST"s, std::make_shared<MultiStringProcessor>(AudioTagMap::ORIGINALLYRICIST())),
		std::make_pair("ORIGINALYEAR"s, std::make_shared<DateProcessor>(AudioTagMap::ORIGINALDATE())),
		std::make_pair("PRODUCER"s, std::make_shared<StringProcessor>(AudioTagMap::PRODUCER())),
        std::make_pair("RADIOSTATION"s, std::make_shared<StringProcessor>(AudioTagMap::RADIOSTATION())),
        std::make_pair("RADIOSTATIONNAME"s, std::make_shared<StringProcessor>(AudioTagMap::RADIOSTATION())),
        std::make_pair("RADIOSTATIONOWNER"s, std::make_shared<StringProcessor>(AudioTagMap::RADIOSTATIONOWNER())),
        std::make_pair("PUBLISHER"s, std::make_shared<StringProcessor>(AudioTagMap::PUBLISHER())),
        std::make_pair("SUBTITLE"s, std::make_shared<StringProcessor>(AudioTagMap::SUBTITLE())),
		std::make_pair("TITLE"s, std::make_shared<StringProcessor>(AudioTagMap::TITLE())),
		std::make_pair("TITLESORT"s, std::make_shared<StringProcessor>(AudioTagMap::TITLESORT())),
		std::make_pair("TOTALTRACKS"s, std::make_shared<NumberProcessor>(AudioTagMap::TOTALTRACKNUMBER())),
		std::make_pair("TRACK"s, std::make_shared<DoubleNumberProcessor>(AudioTagMap::TRACKNUMBER(), AudioTagMap::TOTALTRACKNUMBER())),
		std::make_pair("TRACKNUMBER"s, std::make_shared<DoubleNumberProcessor>(AudioTagMap::TRACKNUMBER(), AudioTagMap::TOTALTRACKNUMBER())),
		std::make_pair("TRACKTOTAL"s, std::make_shared<NumberProcessor>(AudioTagMap::TOTALTRACKNUMBER())),
		std::make_pair("UNSYNCEDLYRICS"s, std::make_shared<LyricsProcessor>()),
		std::make_pair("WRITER"s, std::make_shared<MultiStringProcessor>(AudioTagMap::LYRICIST())),
		std::make_pair("WWWARTIST"s, std::make_shared<StringProcessor>(AudioTagMap::WWWARTIST())),
		std::make_pair("WWWAUDIOFILE"s, std::make_shared<StringProcessor>(AudioTagMap::WWWFILE())),
		std::make_pair("WWWAUDIOSOURCE"s, std::make_shared<StringProcessor>(AudioTagMap::WWWFILESOURCE())),
        std::make_pair("WWWCOMMERCIAL"s, std::make_shared<StringProcessor>(AudioTagMap::WWWCOMMERCIAL())),
        std::make_pair("WWWCOMMERCIALINFO"s, std::make_shared<StringProcessor>(AudioTagMap::WWWCOMMERCIAL())),
        std::make_pair("WWWCOPYRIGHT"s, std::make_shared<StringProcessor>(AudioTagMap::WWWCOPYRIGHT())),
		std::make_pair("WWWFILE"s, std::make_shared<StringProcessor>(AudioTagMap::WWWFILE())),
		std::make_pair("WWWFILESOURCE"s, std::make_shared<StringProcessor>(AudioTagMap::WWWFILESOURCE())),
        std::make_pair("WWWRADIOPAGE"s, std::make_shared<StringProcessor>(AudioTagMap::WWWRADIOPAGE())),
        std::make_pair("YEAR"s, std::make_shared<DateProcessor>(AudioTagMap::DATE())),

        std::make_pair("COVER ART (ARTIST)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEARTIST())),
        std::make_pair("COVER ART (BACK)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGECOVERBACK())),
        std::make_pair("COVER ART (BAND)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEBAND())),
        std::make_pair("COVER ART (BAND LOGOTYPE)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEBANDLOGO())),
        std::make_pair("COVER ART (COMPOSER)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGECOMPOSER())),
        std::make_pair("COVER ART (CONDUCTOR)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGECONDUCTOR())),
        std::make_pair("COVER ART (DURING PERFORMANCE)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEDURINGPERFORMANCE())),
        std::make_pair("COVER ART (DURING RECORDING)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEDURINGRECORDING())),
        std::make_pair("COVER ART (FISH)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEABRIGHTCOLOUREDFISH())),
        std::make_pair("COVER ART (FRONT)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGECOVERFRONT())),
        std::make_pair("COVER ART (ICON)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEOTHERICON())),
        std::make_pair("COVER ART (ILLUSTRATION)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEILLUSTRATION())),
        std::make_pair("COVER ART (LEAD ARTIST)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGELEADARTIST())),
        std::make_pair("COVER ART (LEAFLET)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGELEAFLET())),
        std::make_pair("COVER ART (LYRICIST)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGELYRICIST())),
        std::make_pair("COVER ART (MEDIA)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEMEDIA())),
        std::make_pair("COVER ART (OTHER)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEOTHER())),
        std::make_pair("COVER ART (PNG ICON)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEICON())),
        std::make_pair("COVER ART (PUBLISHER LOGOTYPE)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEPUBLISHERLOGO())),
        std::make_pair("COVER ART (RECORDING LOCATION)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGERECORDINGLOCATION())),
        std::make_pair("COVER ART (VIDEO CAPTURE)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEVIDEOCAPTURE())),
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