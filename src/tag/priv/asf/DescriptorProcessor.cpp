#include "DescriptorProcessor.hpp"
#include <unordered_map>
#include <tag/priv/read_util.hpp>
#include <boost/algorithm/string.hpp>

namespace tag::priv::asf {
	DescriptorProcessor::DescriptorProcessor(const std::string & name)
		: name(name) {}



	StringDescriptorProcessor::StringDescriptorProcessor(const std::string & name)
		: DescriptorProcessor(name) {}

	void StringDescriptorProcessor::process(std::istream & readStream, TagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		std::string text = readUtf16LE(readStream, size);
		if (!text.empty())
			map.setStringTag(name, text);
	}



	MultiStringDescriptorProcessor::MultiStringDescriptorProcessor(const std::string & name)
		: DescriptorProcessor(name) {}

	void MultiStringDescriptorProcessor::process(std::istream & readStream, TagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		std::string text = readUtf16LE(readStream, size);
		if (!text.empty())
			map.setStringTag(name, processMultiString(text));
	}



	CustomStringDescriptorProcessor::CustomStringDescriptorProcessor()
		: DescriptorProcessor(std::string()) {}

	void CustomStringDescriptorProcessor::process(std::istream & readStream, TagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::ByteArray)
			return;
		std::string name = readUtf16LE(readStream);
		boost::to_upper(name);
		std::string text = readUtf16LE(readStream);
		if (!name.empty())
			map.setStringTag(name, text);
	}


	GenreDescriptorProcessor::GenreDescriptorProcessor()
		: DescriptorProcessor(TagMap::GENRE()) {}

	void GenreDescriptorProcessor::process(std::istream & readStream, TagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		std::string text = readUtf16LE(readStream, size);
		if (!text.empty())
			map.setStringTag(name, processGenreString(text));
	}



	NumberDescriptorProcessor::NumberDescriptorProcessor(const std::string & name)
		: DescriptorProcessor(name) {}

	void NumberDescriptorProcessor::process(std::istream & readStream, TagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType == DataType::String) {
			std::string text = readUtf16LE(readStream, size);

			if (!text.empty()) try {
				std::uint32_t number = static_cast<std::uint32_t>(std::stoul(text));
				map.setNumberTag(name, number);
			}
			catch (std::logic_error &) {}

		} else if (dataType == DataType::Dword)
			map.setNumberTag(name, readLittleEndianNumber(readStream));
		else
			readStream.seekg(size, std::ios::cur);
	}



    ZeroBaseNumberDescriptorProcessor::ZeroBaseNumberDescriptorProcessor(const std::string &name)
            : DescriptorProcessor(name) {}

    void ZeroBaseNumberDescriptorProcessor::process(std::istream &readStream, TagMap &map, std::uint16_t size, DataType dataType) const {
        if (dataType == DataType::String) {
            std::string text = readUtf16LE(readStream, size);

            if (!text.empty()) try {
                    std::uint32_t number = static_cast<std::uint32_t>(std::stoul(text));
                    map.setNumberTag(name, number + 1);
                }
                catch (std::logic_error &) {}

        } else if (dataType == DataType::Dword)
            map.setNumberTag(name, readLittleEndianNumber(readStream) + 1);
        else
            readStream.seekg(size, std::ios::cur);
    }



	DoubleNumberDescriptorProcessor::DoubleNumberDescriptorProcessor(const std::string &firstName, const std::string &secondName)
		: DescriptorProcessor(firstName), secondName(secondName) {}

	void DoubleNumberDescriptorProcessor::process(std::istream & readStream, TagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType == DataType::String) {
			std::string all = readUtf16LE(readStream, size);
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
		} else if (dataType == DataType::Dword)
			map.setNumberTag(name, readLittleEndianNumber(readStream));
		else
			readStream.seekg(size, std::ios::cur);

	}



	YearDescriptorProcessor::YearDescriptorProcessor(const std::string & name)
		: DescriptorProcessor(name) {}

	void YearDescriptorProcessor::process(std::istream & readStream, TagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		std::string yearString = readUtf16LE(readStream, size);
		if (yearString.size() != 4)
			return;
		try {
			std::uint32_t year = static_cast<std::uint32_t>(std::stoul(yearString));
			SharedDateAudioTag tag = map.getDateTagPointer(name);
			if (tag != nullptr)
				tag->getDate().setYearOnly(year);
			else
				map.setDateTag(name, types::Date(year));
		}
		catch (std::logic_error &) {}
	}



	DateDescirptorProcessor::DateDescirptorProcessor(const std::string & name)
		: DescriptorProcessor(name) {
	}

	void DateDescirptorProcessor::process(std::istream & readStream, TagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::Qword) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		std::uint64_t fileTime = readLongLittleEndianNumber(readStream);
		std::time_t unixTime = fileTime / 10000000ULL - 11644473600ULL;
		if (unixTime != 0) {
			std::tm &time = *std::gmtime(&unixTime);
			types::Date date(time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
			if (!date.isEmpty())
				map.setDateTag(name, date);
		}
	}



	PictureDescriptorProcessor::PictureDescriptorProcessor()
		: DescriptorProcessor(std::string()) {}

	void PictureDescriptorProcessor::process(std::istream & readStream, TagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::ByteArray) {
			readStream.seekg(size, std::ios::cur);
			return;
		}

		ImageTag::ImageType types = ImageTag::ImageType(readStream.get());
		std::uint32_t imageSize = readLittleEndianNumber(readStream);
		std::string mimeTypeStr = readUtf16LE(readStream);
		std::string description = readUtf16BE(readStream);
		std::vector<std::byte> imageData(imageSize);
		types::Image::MimeType mimeType = string::parseImageMimeType(mimeTypeStr);

		readStream.read(reinterpret_cast<char*>(imageData.data()), imageSize);
		if (mimeType == types::Image::MimeType::None)
			return;

		map.setImageTag(types, types::Image(std::move(imageData), description));
	}



	ISRCDescriptorProcessor::ISRCDescriptorProcessor()
		: DescriptorProcessor(TagMap::ISRC()) {}

	void ISRCDescriptorProcessor::process(std::istream & readStream, TagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		types::ISRC isrc(readUtf16LE(readStream, size));
		if (!isrc.isEmpty())
			map.setISRCTag(name, isrc);
	}

	BarcodeDescriptorProcessor::BarcodeDescriptorProcessor()
			: DescriptorProcessor(TagMap::BARCODE()) {}

	void BarcodeDescriptorProcessor::process(std::istream & readStream, TagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		types::Barcode barcode(readUtf16LE(readStream, size));
		if (!barcode.isEmpty())
			map.setBarcodeTag(name, barcode);
	}



    CustomStringProcessor::CustomStringProcessor()
        : StringDescriptorProcessor(std::string()){}

    void CustomStringProcessor::setName(const std::string &name) {
        this->name = name;
    }


	LyricsProcessor::LyricsProcessor()
	    : DescriptorProcessor(std::string()) {}

	void LyricsProcessor::process(std::istream &readStream, TagMap &map, std::uint16_t size, DataType dataType) const {
        if (dataType != DataType::String) {
            readStream.seekg(size, std::ios::cur);
            return;
        }
        types::Lyrics lyrics(std::string(), readUtf16LE(readStream, size));
        map.setLyricsTagByLang("eng", lyrics);
	}



	static const std::unordered_map<std::string, SharedDescriptorProcessor> PROCESSORS = {
		{"Author"s, std::make_shared<MultiStringDescriptorProcessor>(TagMap::ARTIST())},
		{"ID3/TPE1"s, std::make_shared<MultiStringDescriptorProcessor>(TagMap::ARTIST())},

		{"Copyright"s, std::make_shared<StringDescriptorProcessor>(TagMap::COPYRIGHT())},
		{"ID3/TCOP"s, std::make_shared<StringDescriptorProcessor>(TagMap::COPYRIGHT())},

		{"CopyrightURL"s, std::make_shared<StringDescriptorProcessor>(TagMap::WWWCOPYRIGHT())},
		{"ID3/WCOP"s, std::make_shared<StringDescriptorProcessor>(TagMap::WWWCOPYRIGHT())},

		{"Description"s, std::make_shared<StringDescriptorProcessor>(TagMap::COMMENT())},
		{"WM/Comments"s, std::make_shared<StringDescriptorProcessor>(TagMap::COMMENT())},
		{"ID3/COMM"s, std::make_shared<StringDescriptorProcessor>(TagMap::COMMENT())},

		{"Title"s, std::make_shared<StringDescriptorProcessor>(TagMap::TITLE())},
		{"ID3/TIT2"s, std::make_shared<StringDescriptorProcessor>(TagMap::TITLE())},

		{"WM/AlbumArtist"s, std::make_shared<MultiStringDescriptorProcessor>(TagMap::ALBUMARTIST())},
		{"ID3/TPE2"s, std::make_shared<MultiStringDescriptorProcessor>(TagMap::ALBUMARTIST())},

		{"WM/AlbumArtistSortOrder"s, std::make_shared<MultiStringDescriptorProcessor>(TagMap::ALBUMARTISTSORT())},
		{"ID3/TSO2"s, std::make_shared<MultiStringDescriptorProcessor>(TagMap::ALBUMARTISTSORT())},

		{"WM/AlbumSortOrder"s, std::make_shared<StringDescriptorProcessor>(TagMap::ALBUMSORT())},
		{"ID3/TSOA"s, std::make_shared<StringDescriptorProcessor>(TagMap::ALBUMSORT())},

		{"WM/AlbumTitle"s, std::make_shared<StringDescriptorProcessor>(TagMap::ALBUM())},
		{"ID3/TALB"s, std::make_shared<StringDescriptorProcessor>(TagMap::ALBUM())},

		{"WM/ArtistSortOrder"s, std::make_shared<StringDescriptorProcessor>(TagMap::ARTISTSORT())},
		{"ID3/TSOP"s, std::make_shared<StringDescriptorProcessor>(TagMap::ARTISTSORT())},

		{"WM/AudioFileURL"s, std::make_shared<StringDescriptorProcessor>(TagMap::WWWFILE())},
		{"ID3/WOAF"s, std::make_shared<StringDescriptorProcessor>(TagMap::WWWFILE())},

		{"WM/AudioSourceURL"s, std::make_shared<StringDescriptorProcessor>(TagMap::WWWFILESOURCE())},
		{"ID3/WOAS"s, std::make_shared<StringDescriptorProcessor>(TagMap::WWWFILESOURCE())},

		{"WM/AuthorURL"s, std::make_shared<StringDescriptorProcessor>(TagMap::WWWARTIST())},
		{"ID3/WOAR"s, std::make_shared<StringDescriptorProcessor>(TagMap::WWWARTIST())},

		{"WM/Barcode"s, std::make_shared<BarcodeDescriptorProcessor>()},

		{"WM/BeatsPerMinute"s, std::make_shared<NumberDescriptorProcessor>(TagMap::BPM())},
		{"ID3/TBMP"s, std::make_shared<NumberDescriptorProcessor>(TagMap::BPM())},

		{"WM/Composer"s, std::make_shared<MultiStringDescriptorProcessor>(TagMap::COMPOSER())},
		{"ID3/TCOM"s, std::make_shared<MultiStringDescriptorProcessor>(TagMap::COMPOSER())},

		{"WM/Conductor"s, std::make_shared<StringDescriptorProcessor>(TagMap::CONDUCTOR())},
		{"ID3/TPE3"s, std::make_shared<StringDescriptorProcessor>(TagMap::CONDUCTOR())},

		{"WM/ContentGroupDescription"s, std::make_shared<StringDescriptorProcessor>(TagMap::CONTENTGROUP())},
		{"ID3/TIT1"s, std::make_shared<StringDescriptorProcessor>(TagMap::CONTENTGROUP())},

		{"WM/DJMixer"s, std::make_shared<StringDescriptorProcessor>(TagMap::MIXDJ())},

		{"WM/EncodedBy"s, std::make_shared<StringDescriptorProcessor>(TagMap::ENCODEDBY())},
		{"ID3/TENC"s, std::make_shared<StringDescriptorProcessor>(TagMap::ENCODEDBY())},

		{"WM/EncodingSettings"s, std::make_shared<StringDescriptorProcessor>(TagMap::ENCODERSETTINGS())},
		{"ID3/TSSE"s, std::make_shared<StringDescriptorProcessor>(TagMap::ENCODERSETTINGS())},

		{"WM/EncodingTime"s, std::make_shared<DateDescirptorProcessor>(TagMap::ENCODINGDATE())},
		{"ID3/TDEN"s, std::make_shared<DateDescirptorProcessor>(TagMap::ENCODINGDATE())},

		{"WM/Genre"s, std::make_shared<GenreDescriptorProcessor>()},
		{"WM/GenreID"s, std::make_shared<GenreDescriptorProcessor>()},
		{"ID3/TCON"s, std::make_shared<GenreDescriptorProcessor>()},

		{"WM/InitialKey"s, std::make_shared<StringDescriptorProcessor>(TagMap::INITIALKEY())},
		{"IDE3/TKEY"s, std::make_shared<StringDescriptorProcessor>(TagMap::INITIALKEY())},

		{"WM/ISRC"s, std::make_shared<ISRCDescriptorProcessor>()},
		{"IDE3/TSRC"s, std::make_shared<ISRCDescriptorProcessor>()},

		{"WM/Lyrics"s, std::make_shared<LyricsProcessor>()},

		{"WM/Mixer"s, std::make_shared<StringDescriptorProcessor>(TagMap::MIXDJ())},

		{"WM/ModifiedBy"s, std::make_shared<StringDescriptorProcessor>(TagMap::REMIXER())},
		{"IDE3/TPE4"s, std::make_shared<StringDescriptorProcessor>(TagMap::REMIXER())},

		{"WM/Mood"s, std::make_shared<StringDescriptorProcessor>(TagMap::MOOD())},
		{"IDE3/TMOO"s, std::make_shared<StringDescriptorProcessor>(TagMap::MOOD())},

		{"WM/OriginalAlbumTitle"s, std::make_shared<StringDescriptorProcessor>(TagMap::ORIGINALALBUM())},
		{"IDE3/TOAL"s, std::make_shared<StringDescriptorProcessor>(TagMap::ORIGINALALBUM())},

		{"WM/OriginalArtist"s, std::make_shared<StringDescriptorProcessor>(TagMap::ORIGINALARTIST())},
		{"IDE3/TOPE"s, std::make_shared<StringDescriptorProcessor>(TagMap::ORIGINALARTIST())},

		{"WM/OriginalLyricist"s, std::make_shared<MultiStringDescriptorProcessor>(TagMap::ORIGINALLYRICIST())},
		{"IDE3/TOLY"s, std::make_shared<MultiStringDescriptorProcessor>(TagMap::ORIGINALLYRICIST())},

		{"WM/OriginalReleaseYear"s, std::make_shared<YearDescriptorProcessor>(TagMap::ORIGINALDATE())},
		{"IDE3/TORY"s, std::make_shared<YearDescriptorProcessor>(TagMap::ORIGINALDATE())},

		{"WM/PartOfSet"s, std::make_shared<DoubleNumberDescriptorProcessor>(TagMap::DISCNUMBER(), TagMap::TOTALDISCNUMBER())},
		{"IDE3/TPOS"s, std::make_shared<DoubleNumberDescriptorProcessor>(TagMap::DISCNUMBER(), TagMap::TOTALDISCNUMBER())},

		{"WM/Producer"s, std::make_shared<StringDescriptorProcessor>(TagMap::PRODUCER())},

		{"WM/PromotionURL"s, std::make_shared<StringDescriptorProcessor>(TagMap::WWWCOMMERCIAL())},
		{"ID3/WCOM"s, std::make_shared<StringDescriptorProcessor>(TagMap::WWWCOMMERCIAL())},

		{"WM/Publisher"s, std::make_shared<StringDescriptorProcessor>(TagMap::PUBLISHER())},
		{"IDE3/TPUB"s, std::make_shared<StringDescriptorProcessor>(TagMap::PUBLISHER())},

		{"WM/RadioStationName"s, std::make_shared<StringDescriptorProcessor>(TagMap::RADIOSTATION())},
		{"IDE3/TRSN"s, std::make_shared<StringDescriptorProcessor>(TagMap::RADIOSTATION())},

		{"WM/RadioStationOwner"s, std::make_shared<StringDescriptorProcessor>(TagMap::RADIOSTATIONOWNER())},
		{"IDE3/TRSO"s, std::make_shared<StringDescriptorProcessor>(TagMap::RADIOSTATIONOWNER())},

		{"WM/SetSubTitle"s, std::make_shared<StringDescriptorProcessor>(TagMap::SETSUBTITLE())},
		{"IDE3/TSST"s, std::make_shared<StringDescriptorProcessor>(TagMap::SETSUBTITLE())},

		{"WM/SubTitle"s, std::make_shared<StringDescriptorProcessor>(TagMap::SUBTITLE())},
		{"IDE3/TIT3"s, std::make_shared<StringDescriptorProcessor>(TagMap::SUBTITLE())},

		{"WM/TEXT"s, std::make_shared<CustomStringDescriptorProcessor>()},
		{"ID3/TXXX"s, std::make_shared<CustomStringDescriptorProcessor>()},

		{"WM/TitleSortOrder"s, std::make_shared<StringDescriptorProcessor>(TagMap::TITLESORT())},
		{"IDE3/TSOT"s, std::make_shared<StringDescriptorProcessor>(TagMap::TITLESORT())},

		{"WM/Track"s, std::make_shared<ZeroBaseNumberDescriptorProcessor>(TagMap::TOTALTRACKNUMBER())},

		{"WM/TrackNumber"s, std::make_shared<DoubleNumberDescriptorProcessor>(TagMap::TRACKNUMBER(), TagMap::TOTALTRACKNUMBER())},
		{"ID3/TRCK"s, std::make_shared<DoubleNumberDescriptorProcessor>(TagMap::TRACKNUMBER(), TagMap::TOTALTRACKNUMBER())},

		{"WM/Writer"s, std::make_shared<MultiStringDescriptorProcessor>(TagMap::LYRICIST())},
		{"ID3/TEXT"s, std::make_shared<MultiStringDescriptorProcessor>(TagMap::LYRICIST())},

		{"WM/Year"s, std::make_shared<YearDescriptorProcessor>(TagMap::DATE())},
		{"ID3/TYER"s, std::make_shared<YearDescriptorProcessor>(TagMap::DATE())},

		{"WM/Picture"s, std::make_shared<PictureDescriptorProcessor>()},
		{"ID3/APIC"s, std::make_shared<PictureDescriptorProcessor>()},


		//customs
		{"NETRADIOOWNER"s, std::make_shared<StringDescriptorProcessor>(TagMap::RADIOSTATIONOWNER())},

		{"NETRADIOSTATION"s, std::make_shared<StringDescriptorProcessor>(TagMap::RADIOSTATION())},

		{"SETSUBTITLE"s, std::make_shared<StringDescriptorProcessor>(TagMap::SETSUBTITLE())},
		{"DISCSUBTITLE"s, std::make_shared<StringDescriptorProcessor>(TagMap::SETSUBTITLE())},

		{"DISCTOTAL"s, std::make_shared<NumberDescriptorProcessor>(TagMap::TOTALDISCNUMBER())},
		{"TOTALDISCS"s, std::make_shared<NumberDescriptorProcessor>(TagMap::TOTALDISCNUMBER())},

		{"TRACKTOTAL"s, std::make_shared<NumberDescriptorProcessor>(TagMap::TOTALTRACKNUMBER())},
		{"TOTALTRACKS"s, std::make_shared<NumberDescriptorProcessor>(TagMap::TOTALTRACKNUMBER())}
};


	SharedDescriptorProcessor getDescriptorProcessor(const std::string & descriptorName) {
	    static thread_local auto customStringProcessor = std::make_shared<CustomStringProcessor>();
        static const std::string WM = "WM/";
        static const std::string FOOBAR = "foobar2000/";

		auto it = PROCESSORS.find(descriptorName);
		if (it != PROCESSORS.end())
			return it->second;

		if (boost::starts_with(descriptorName, WM))
		    customStringProcessor->setName(boost::to_upper_copy(descriptorName.substr(WM.size())));
		else if (boost::starts_with(descriptorName, FOOBAR))
            customStringProcessor->setName(boost::to_upper_copy(descriptorName.substr(FOOBAR.size())));
		else
			customStringProcessor->setName(boost::to_upper_copy(descriptorName));

		return customStringProcessor;
    }
}