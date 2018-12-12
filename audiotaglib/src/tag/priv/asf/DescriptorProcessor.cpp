#include "DescriptorProcessor.hpp"
#include <unordered_map>
#include <tag/priv/read_util.hpp>
#include <boost/algorithm/string.hpp>

namespace tag::priv::asf {
	DescriptorProcessor::DescriptorProcessor(const std::string & name)
		: name(name) {}



	StringDescriptorProcessor::StringDescriptorProcessor(const std::string & name)
		: DescriptorProcessor(name) {}

	void StringDescriptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
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

	void MultiStringDescriptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
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

	void CustomStringDescriptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::ByteArray)
			return;
		std::string name = readUtf16LE(readStream);
		boost::to_upper(name);
		std::string text = readUtf16LE(readStream);
		if (!name.empty())
			map.setStringTag(name, text);
	}


	GenreDescriptorProcessor::GenreDescriptorProcessor()
		: DescriptorProcessor(AudioTagMap::GENRE()) {}

	void GenreDescriptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
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

	void NumberDescriptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
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

    void ZeroBaseNumberDescriptorProcessor::process(std::istream &readStream, AudioTagMap &map, std::uint16_t size, DataType dataType) const {
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

	void DoubleNumberDescriptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
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

	void YearDescriptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		std::string yearString = readUtf16LE(readStream, size);
		if (yearString.size() != 4)
			return;
		try {
			std::uint32_t year = static_cast<std::uint32_t>(std::stoul(yearString));
			SharedDateAudioTag tag = map.getDateTag(name);
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

	void DateDescirptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
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

	void PictureDescriptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::ByteArray) {
			readStream.seekg(size, std::ios::cur);
			return;
		}

		ImageAudioTag::ImageType types = ImageAudioTag::ImageType(readStream.get());
		std::uint32_t imageSize = readLittleEndianNumber(readStream);
		std::string mimeTypeStr = readUtf16LE(readStream);
		std::string description = readUtf16BE(readStream);
		std::vector<std::byte> imageData(imageSize);
		types::Image::MimeType mimeType = string::parseImageMimeType(mimeTypeStr);

		readStream.read(reinterpret_cast<char*>(imageData.data()), imageSize);
		if (mimeType == types::Image::MimeType::None)
			return;

		map.setImageTag(types, types::Image(std::move(imageData), description, mimeType));
	}



	ISRCDescriptorProcessor::ISRCDescriptorProcessor()
		: DescriptorProcessor(std::string()) {}

	void ISRCDescriptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		types::ISRC isrc(readUtf16LE(readStream, size));
		if (!isrc.isEmpty())
			map.setISRCTag(isrc);
	}

	BarcodeDescriptorProcessor::BarcodeDescriptorProcessor()
			: DescriptorProcessor(std::string()) {}

	void BarcodeDescriptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		types::Barcode barcode(readUtf16LE(readStream, size));
		if (!barcode.isEmpty())
			map.setBarcodeTag(barcode);
	}



    CustomStringProcessor::CustomStringProcessor()
        : StringDescriptorProcessor(std::string()){}

    void CustomStringProcessor::setName(const std::string &name) {
        this->name = name;
    }


	LyricsProcessor::LyricsProcessor()
	    : DescriptorProcessor(std::string()) {}

	void LyricsProcessor::process(std::istream &readStream, AudioTagMap &map, std::uint16_t size, DataType dataType) const {
        if (dataType != DataType::String) {
            readStream.seekg(size, std::ios::cur);
            return;
        }
        types::Lyrics lyrics(std::string(), readUtf16LE(readStream, size));
        map.setLyricsTagByLang("eng", lyrics);
	}



	static const std::unordered_map<std::string, SharedDescriptorProcessor> PROCESSORS = {
		std::make_pair("Author"s, std::make_shared<MultiStringDescriptorProcessor>(AudioTagMap::ARTIST())),
		std::make_pair("ID3/TPE1"s, std::make_shared<MultiStringDescriptorProcessor>(AudioTagMap::ARTIST())),

		std::make_pair("Copyright"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::COPYRIGHT())),
		std::make_pair("ID3/TCOP"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::COPYRIGHT())),

		std::make_pair("CopyrightURL"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::WWWCOPYRIGHT())),
		std::make_pair("ID3/WCOP"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::WWWCOPYRIGHT())),

		std::make_pair("Description"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::COMMENT())),
		std::make_pair("WM/Comments"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::COMMENT())),
		std::make_pair("ID3/COMM"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::COMMENT())),

		std::make_pair("Title"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::TITLE())),
		std::make_pair("ID3/TIT2"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::TITLE())),

		std::make_pair("WM/AlbumArtist"s, std::make_shared<MultiStringDescriptorProcessor>(AudioTagMap::ALBUMARTIST())),
		std::make_pair("ID3/TPE2"s, std::make_shared<MultiStringDescriptorProcessor>(AudioTagMap::ALBUMARTIST())),

        std::make_pair("WM/AlbumArtistSortOrder"s, std::make_shared<MultiStringDescriptorProcessor>(AudioTagMap::ALBUMARTISTSORT())),
        std::make_pair("ID3/TSO2"s, std::make_shared<MultiStringDescriptorProcessor>(AudioTagMap::ALBUMARTISTSORT())),

		std::make_pair("WM/AlbumSortOrder"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::ALBUMSORT())),
		std::make_pair("ID3/TSOA"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::ALBUMSORT())),

		std::make_pair("WM/AlbumTitle"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::ALBUM())),
		std::make_pair("ID3/TALB"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::ALBUM())),

		std::make_pair("WM/ArtistSortOrder"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::ARTISTSORT())),
		std::make_pair("ID3/TSOP"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::ARTISTSORT())),

		std::make_pair("WM/AudioFileURL"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::WWWFILE())),
		std::make_pair("ID3/WOAF"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::WWWFILE())),

		std::make_pair("WM/AudioSourceURL"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::WWWFILESOURCE())),
		std::make_pair("ID3/WOAS"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::WWWFILESOURCE())),

		std::make_pair("WM/AuthorURL"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::WWWARTIST())),
		std::make_pair("ID3/WOAR"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::WWWARTIST())),

		std::make_pair("WM/Barcode"s, std::make_shared<BarcodeDescriptorProcessor>()),

		std::make_pair("WM/BeatsPerMinute"s, std::make_shared<NumberDescriptorProcessor>(AudioTagMap::BPM())),
		std::make_pair("ID3/TBMP"s, std::make_shared<NumberDescriptorProcessor>(AudioTagMap::BPM())),
		
		std::make_pair("WM/Composer"s, std::make_shared<MultiStringDescriptorProcessor>(AudioTagMap::COMPOSER())),
		std::make_pair("ID3/TCOM"s, std::make_shared<MultiStringDescriptorProcessor>(AudioTagMap::COMPOSER())),

		std::make_pair("WM/Conductor"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::CONDUCTOR())),
		std::make_pair("ID3/TPE3"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::CONDUCTOR())),

		std::make_pair("WM/ContentGroupDescription"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::CONTENTGROUP())),
		std::make_pair("ID3/TIT1"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::CONTENTGROUP())),

        std::make_pair("WM/DJMixer"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::MIXDJ())),

        std::make_pair("WM/EncodedBy"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::ENCODEDBY())),
		std::make_pair("ID3/TENC"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::ENCODEDBY())),

		std::make_pair("WM/EncodingSettings"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::ENCODERSETTINGS())),
		std::make_pair("ID3/TSSE"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::ENCODERSETTINGS())),

		std::make_pair("WM/EncodingTime"s, std::make_shared<DateDescirptorProcessor>(AudioTagMap::ENCODINGDATE())),
		std::make_pair("ID3/TDEN"s, std::make_shared<DateDescirptorProcessor>(AudioTagMap::ENCODINGDATE())),

		std::make_pair("WM/Genre"s, std::make_shared<GenreDescriptorProcessor>()),
		std::make_pair("WM/GenreID"s, std::make_shared<GenreDescriptorProcessor>()),
		std::make_pair("ID3/TCON"s, std::make_shared<GenreDescriptorProcessor>()),

		std::make_pair("WM/InitialKey"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::INITIALKEY())),
		std::make_pair("IDE3/TKEY"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::INITIALKEY())),

		std::make_pair("WM/ISRC"s, std::make_shared<ISRCDescriptorProcessor>()),
		std::make_pair("IDE3/TSRC"s, std::make_shared<ISRCDescriptorProcessor>()),

        std::make_pair("WM/Lyrics"s, std::make_shared<LyricsProcessor>()),

        std::make_pair("WM/Mixer"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::MIXDJ())),

        std::make_pair("WM/ModifiedBy"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::REMIXER())),
        std::make_pair("IDE3/TPE4"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::REMIXER())),

        std::make_pair("WM/Mood"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::MOOD())),
		std::make_pair("IDE3/TMOO"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::MOOD())),

		std::make_pair("WM/OriginalAlbumTitle"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::ORIGINALALBUM())),
		std::make_pair("IDE3/TOAL"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::ORIGINALALBUM())),

		std::make_pair("WM/OriginalArtist"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::ORIGINALARTIST())),
		std::make_pair("IDE3/TOPE"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::ORIGINALARTIST())),

		std::make_pair("WM/OriginalLyricist"s, std::make_shared<MultiStringDescriptorProcessor>(AudioTagMap::ORIGINALLYRICIST())),
		std::make_pair("IDE3/TOLY"s, std::make_shared<MultiStringDescriptorProcessor>(AudioTagMap::ORIGINALLYRICIST())),

		std::make_pair("WM/OriginalReleaseYear"s, std::make_shared<YearDescriptorProcessor>(AudioTagMap::ORIGINALDATE())),
		std::make_pair("IDE3/TORY"s, std::make_shared<YearDescriptorProcessor>(AudioTagMap::ORIGINALDATE())),

		std::make_pair("WM/PartOfSet"s, std::make_shared<DoubleNumberDescriptorProcessor>(AudioTagMap::DISCNUMBER(), AudioTagMap::TOTALDISCNUMBER())),
		std::make_pair("IDE3/TPOS"s, std::make_shared<DoubleNumberDescriptorProcessor>(AudioTagMap::DISCNUMBER(), AudioTagMap::TOTALDISCNUMBER())),

        std::make_pair("WM/Producer"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::PRODUCER())),

        std::make_pair("WM/PromotionURL"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::WWWCOMMERCIAL())),
        std::make_pair("ID3/WCOM"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::WWWCOMMERCIAL())),

		std::make_pair("WM/Publisher"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::PUBLISHER())),
		std::make_pair("IDE3/TPUB"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::PUBLISHER())),

		std::make_pair("WM/RadioStationName"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::RADIOSTATION())),
		std::make_pair("IDE3/TRSN"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::RADIOSTATION())),

		std::make_pair("WM/RadioStationOwner"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::RADIOSTATIONOWNER())),
		std::make_pair("IDE3/TRSO"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::RADIOSTATIONOWNER())),

		std::make_pair("WM/SetSubTitle"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::SETSUBTITLE())),
		std::make_pair("IDE3/TSST"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::SETSUBTITLE())),

		std::make_pair("WM/SubTitle"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::SUBTITLE())),
		std::make_pair("IDE3/TIT3"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::SUBTITLE())),

		std::make_pair("WM/TEXT"s, std::make_shared<CustomStringDescriptorProcessor>()),
		std::make_pair("ID3/TXXX"s, std::make_shared<CustomStringDescriptorProcessor>()),

        std::make_pair("WM/TitleSortOrder"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::TITLESORT())),
        std::make_pair("IDE3/TSOT"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::TITLESORT())),

		std::make_pair("WM/Track"s, std::make_shared<ZeroBaseNumberDescriptorProcessor>(AudioTagMap::TOTALTRACKNUMBER())),

        std::make_pair("WM/TrackNumber"s, std::make_shared<DoubleNumberDescriptorProcessor>(AudioTagMap::TRACKNUMBER(), AudioTagMap::TOTALTRACKNUMBER())),
		std::make_pair("ID3/TRCK"s, std::make_shared<DoubleNumberDescriptorProcessor>(AudioTagMap::TRACKNUMBER(), AudioTagMap::TOTALTRACKNUMBER())),

		std::make_pair("WM/Writer"s, std::make_shared<MultiStringDescriptorProcessor>(AudioTagMap::LYRICIST())),
		std::make_pair("ID3/TEXT"s, std::make_shared<MultiStringDescriptorProcessor>(AudioTagMap::LYRICIST())),

		std::make_pair("WM/Year"s, std::make_shared<YearDescriptorProcessor>(AudioTagMap::DATE())),
		std::make_pair("ID3/TYER"s, std::make_shared<YearDescriptorProcessor>(AudioTagMap::DATE())),

		std::make_pair("WM/Picture"s, std::make_shared<PictureDescriptorProcessor>()),
		std::make_pair("ID3/APIC"s, std::make_shared<PictureDescriptorProcessor>()),


		//customs
		std::make_pair("NETRADIOOWNER"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::RADIOSTATIONOWNER())),

		std::make_pair("NETRADIOSTATION"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::RADIOSTATION())),

		std::make_pair("SETSUBTITLE"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::SETSUBTITLE())),
		std::make_pair("DISCSUBTITLE"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::SETSUBTITLE())),

		std::make_pair("DISCTOTAL"s, std::make_shared<NumberDescriptorProcessor>(AudioTagMap::TOTALDISCNUMBER())),
		std::make_pair("TOTALDISCS"s, std::make_shared<NumberDescriptorProcessor>(AudioTagMap::TOTALDISCNUMBER())),

		std::make_pair("TRACKTOTAL"s, std::make_shared<NumberDescriptorProcessor>(AudioTagMap::TOTALTRACKNUMBER())),
		std::make_pair("TOTALTRACKS"s, std::make_shared<NumberDescriptorProcessor>(AudioTagMap::TOTALTRACKNUMBER()))
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