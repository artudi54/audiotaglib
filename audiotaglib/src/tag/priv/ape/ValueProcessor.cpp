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

	void StringProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint32_t size, ValueType valueType) {
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

	void MultiStringProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint32_t size, ValueType valueType) {
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

	void NumberProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint32_t size, ValueType valueType) {
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

	void DoubleNumberProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint32_t size, ValueType valueType) {
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

	void DateProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint32_t size, ValueType valueType) {
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
		: ValueProcessor(AudioTagMap::GENRE()) {}

	void GenreProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint32_t size, ValueType valueType) {
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

	void ISRCProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint32_t size, ValueType valueType) {
		if (valueType != ValueType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}

		std::string isrcStr = readUtf8(readStream, size);
		types::ISRC isrc(isrcStr);
		if (!isrc.isEmpty())
			map.setISRCTag(isrc);
	}



    BarcodeProcessor::BarcodeProcessor()
            : ValueProcessor(std::string()) {}

    void BarcodeProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint32_t size, ValueType valueType) {
        if (valueType != ValueType::String) {
            readStream.seekg(size, std::ios::cur);
            return;
        }

        std::string barcodeStr = readUtf8(readStream, size);
        types::Barcode barcode(barcodeStr);
        if (!barcode.isEmpty())
            map.setBarcodeTag(barcode);
    }



	LyricsProcessor::LyricsProcessor()
		: ValueProcessor(AudioTagMap::LYRICSENG()) {}

	void LyricsProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint32_t size, ValueType valueType) {
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

	void FrontImageProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint32_t size, ValueType valueType) {
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


		map.setImageTag(name, types::Image(std::move(imageData), description, mimeType));
	}



    CustomStringProcessor::CustomStringProcessor()
        : StringProcessor(std::string()) {
    }

    void CustomStringProcessor::setName(const std::string &name) {
        this->name = name;
    }



	static const std::unordered_map<std::string, SharedValueProcessor, IHash, IEquals> MAPPED_PROCESSORS = {
		{"ALBUM"s, std::make_shared<StringProcessor>(AudioTagMap::ALBUM())},
		{"ALBUMSORT"s, std::make_shared<StringProcessor>(AudioTagMap::ALBUMSORT())},
		{"ALBUM ARTIST"s, std::make_shared<StringProcessor>(AudioTagMap::ALBUMARTIST())},
		{"ALBUMARTIST"s, std::make_shared<StringProcessor>(AudioTagMap::ALBUMARTIST())},
		{"ALBUMARTISTSORT"s, std::make_shared<StringProcessor>(AudioTagMap::ALBUMARTISTSORT())},
		{"ALBUMSORT"s, std::make_shared<StringProcessor>(AudioTagMap::ALBUMSORT())},
		{"ARRANGER"s, std::make_shared<MultiStringProcessor>(AudioTagMap::ARRANGER())},
		{"ARTIST"s, std::make_shared<MultiStringProcessor>(AudioTagMap::ARTIST())},
		{"ARTISTSORT"s, std::make_shared<MultiStringProcessor>(AudioTagMap::ARTISTSORT())},
		{"BARCODE"s, std::make_shared<BarcodeProcessor>()},
		{"BPM"s, std::make_shared<NumberProcessor>(AudioTagMap::BPM())},
		{"COMMENT"s, std::make_shared<StringProcessor>(AudioTagMap::COMMENT())},
		{"COMPOSER"s, std::make_shared<MultiStringProcessor>(AudioTagMap::COMPOSER())},
		{"CONDUCTOR"s, std::make_shared<StringProcessor>(AudioTagMap::CONDUCTOR())},
		{"COPYRIGHT"s, std::make_shared<StringProcessor>(AudioTagMap::COPYRIGHT())},
		{"DISC"s, std::make_shared<DoubleNumberProcessor>(AudioTagMap::DISCNUMBER(), AudioTagMap::TOTALDISCNUMBER())},
		{"DISCNUMBER"s, std::make_shared<DoubleNumberProcessor>(AudioTagMap::DISCNUMBER(), AudioTagMap::TOTALDISCNUMBER())},
		{"DJMIXER"s, std::make_shared<StringProcessor>(AudioTagMap::MIXDJ())},
		{"DISCSUBTITLE"s, std::make_shared<StringProcessor>(AudioTagMap::SETSUBTITLE())},
		{"DISCTOTAL"s, std::make_shared<NumberProcessor>(AudioTagMap::TOTALDISCNUMBER())},
		{"ENCODEDBY"s, std::make_shared<StringProcessor>(AudioTagMap::ENCODEDBY())},
		{"ENGINEER"s, std::make_shared<StringProcessor>(AudioTagMap::ENGINEER())},
		{"GENRE"s, std::make_shared<GenreProcessor>()},
		{"GROUPING"s, std::make_shared<StringProcessor>(AudioTagMap::CONTENTGROUP())},
		{"ISRC"s, std::make_shared<ISRCProcessor>()},
		{"LABEL"s, std::make_shared<StringProcessor>(AudioTagMap::PUBLISHER())},
		{"LYRICIST"s, std::make_shared<MultiStringProcessor>(AudioTagMap::LYRICIST())},
		{"LYRICS"s, std::make_shared<LyricsProcessor>()},
		{"MIXER"s, std::make_shared<StringProcessor>(AudioTagMap::MIXENGINEER())},
		{"MOOD"s, std::make_shared<StringProcessor>(AudioTagMap::MOOD())},
		{"NETRADIOSTATION"s, std::make_shared<StringProcessor>(AudioTagMap::RADIOSTATION())},
		{"NETRADIOSTATIONNAME"s, std::make_shared<StringProcessor>(AudioTagMap::RADIOSTATION())},
		{"NETRADIOSTATIONOWNER"s, std::make_shared<StringProcessor>(AudioTagMap::RADIOSTATIONOWNER())},
		{"MIXARTIST"s, std::make_shared<StringProcessor>(AudioTagMap::REMIXER())},
		{"MOOD"s, std::make_shared<StringProcessor>(AudioTagMap::MOOD())},
		{"ORIGINALALBUM"s, std::make_shared<StringProcessor>(AudioTagMap::ORIGINALALBUM())},
		{"ORIGINALARTIST"s, std::make_shared<MultiStringProcessor>(AudioTagMap::ORIGINALARTIST())},
		{"ORIGINALLYRICIST"s, std::make_shared<MultiStringProcessor>(AudioTagMap::ORIGINALLYRICIST())},
		{"ORIGINALYEAR"s, std::make_shared<DateProcessor>(AudioTagMap::ORIGINALDATE())},
		{"PRODUCER"s, std::make_shared<StringProcessor>(AudioTagMap::PRODUCER())},
		{"RADIOSTATION"s, std::make_shared<StringProcessor>(AudioTagMap::RADIOSTATION())},
		{"RADIOSTATIONNAME"s, std::make_shared<StringProcessor>(AudioTagMap::RADIOSTATION())},
		{"RADIOSTATIONOWNER"s, std::make_shared<StringProcessor>(AudioTagMap::RADIOSTATIONOWNER())},
		{"PUBLISHER"s, std::make_shared<StringProcessor>(AudioTagMap::PUBLISHER())},
		{"SUBTITLE"s, std::make_shared<StringProcessor>(AudioTagMap::SUBTITLE())},
		{"TITLE"s, std::make_shared<StringProcessor>(AudioTagMap::TITLE())},
		{"TITLESORT"s, std::make_shared<StringProcessor>(AudioTagMap::TITLESORT())},
		{"TOTALTRACKS"s, std::make_shared<NumberProcessor>(AudioTagMap::TOTALTRACKNUMBER())},
		{"TRACK"s, std::make_shared<DoubleNumberProcessor>(AudioTagMap::TRACKNUMBER(), AudioTagMap::TOTALTRACKNUMBER())},
		{"TRACKNUMBER"s, std::make_shared<DoubleNumberProcessor>(AudioTagMap::TRACKNUMBER(), AudioTagMap::TOTALTRACKNUMBER())},
		{"TRACKTOTAL"s, std::make_shared<NumberProcessor>(AudioTagMap::TOTALTRACKNUMBER())},
		{"UNSYNCEDLYRICS"s, std::make_shared<LyricsProcessor>()},
		{"WRITER"s, std::make_shared<MultiStringProcessor>(AudioTagMap::LYRICIST())},
		{"WWWARTIST"s, std::make_shared<StringProcessor>(AudioTagMap::WWWARTIST())},
		{"WWWAUDIOFILE"s, std::make_shared<StringProcessor>(AudioTagMap::WWWFILE())},
		{"WWWAUDIOSOURCE"s, std::make_shared<StringProcessor>(AudioTagMap::WWWFILESOURCE())},
		{"WWWCOMMERCIAL"s, std::make_shared<StringProcessor>(AudioTagMap::WWWCOMMERCIAL())},
		{"WWWCOMMERCIALINFO"s, std::make_shared<StringProcessor>(AudioTagMap::WWWCOMMERCIAL())},
		{"WWWCOPYRIGHT"s, std::make_shared<StringProcessor>(AudioTagMap::WWWCOPYRIGHT())},
		{"WWWFILE"s, std::make_shared<StringProcessor>(AudioTagMap::WWWFILE())},
		{"WWWFILESOURCE"s, std::make_shared<StringProcessor>(AudioTagMap::WWWFILESOURCE())},
		{"WWWPAYMENT"s, std::make_shared<StringProcessor>(AudioTagMap::WWWPAYMENT())},
		{"WWWPODCAST"s, std::make_shared<StringProcessor>(AudioTagMap::WWWPODCAST())},
		{"WWWRADIOPAGE"s, std::make_shared<StringProcessor>(AudioTagMap::WWWRADIOPAGE())},
		{"YEAR"s, std::make_shared<DateProcessor>(AudioTagMap::DATE())},

		{"COVER ART (ARTIST)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEARTIST())},
		{"COVER ART (BACK)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGECOVERBACK())},
		{"COVER ART (BAND)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEBAND())},
		{"COVER ART (BAND LOGOTYPE)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEBANDLOGO())},
		{"COVER ART (COMPOSER)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGECOMPOSER())},
		{"COVER ART (CONDUCTOR)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGECONDUCTOR())},
		{"COVER ART (DURING PERFORMANCE)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEDURINGPERFORMANCE())},
		{"COVER ART (DURING RECORDING)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEDURINGRECORDING())},
		{"COVER ART (FISH)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEABRIGHTCOLOUREDFISH())},
		{"COVER ART (FRONT)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGECOVERFRONT())},
		{"COVER ART (ICON)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEOTHERICON())},
		{"COVER ART (ILLUSTRATION)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEILLUSTRATION())},
		{"COVER ART (LEAD ARTIST)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGELEADARTIST())},
		{"COVER ART (LEAFLET)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGELEAFLET())},
		{"COVER ART (LYRICIST)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGELYRICIST())},
		{"COVER ART (MEDIA)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEMEDIA())},
		{"COVER ART (OTHER)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEOTHER())},
		{"COVER ART (PNG ICON)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEICON())},
		{"COVER ART (PUBLISHER LOGOTYPE)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEPUBLISHERLOGO())},
		{"COVER ART (RECORDING LOCATION)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGERECORDINGLOCATION())},
		{"COVER ART (VIDEO CAPTURE)"s, std::make_shared<FrontImageProcessor>(AudioTagMap::IMAGEVIDEOCAPTURE())}
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