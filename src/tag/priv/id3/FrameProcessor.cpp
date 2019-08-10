#include "FrameProcessor.hpp"
#include <tag/priv/id3/TextEncoding.hpp>
#include <tag/priv/id3/MonthDayDate.hpp>
#include <boost/algorithm/string.hpp>

namespace tag::priv::id3 {

	FrameProcessor::FrameProcessor(const std::string & name)
		: name(name) {}

	FrameProcessor::~FrameProcessor() {}



	TextProcessor::TextProcessor(const std::string & name)
		: FrameProcessor(name) {}

	void TextProcessor::process(std::istream& readStream, TagMap & map, std::uint32_t size) const {
		std::string text = readStringWithEncoding(readStream, size);
		if (!text.empty())
			map.setStringTag(name, text);
	}



	MultiStringTextProcessor::MultiStringTextProcessor(const std::string & name)
		: FrameProcessor(name) {}

	void MultiStringTextProcessor::process(std::istream& readStream, TagMap & map, std::uint32_t size) const {
		std::string text = readStringWithEncoding(readStream, size);
		if (!text.empty())
			map.setStringTag(name, processMultiString(text));
	}



	URLProcessor::URLProcessor(const std::string & name)
		: FrameProcessor(name) {}

	void URLProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size) const {
		map.setStringTag(name, readUtf8(readStream, size));
	}



	SingleNumberTextProcessor::SingleNumberTextProcessor(const std::string &name)
		: FrameProcessor(name) {}

	void SingleNumberTextProcessor::process(std::istream& readStream, TagMap & map, std::uint32_t size) const {
		std::string numStr = readStringWithEncoding(readStream, size);
		try {
			std::uint32_t number = static_cast<std::uint32_t>(std::stol(numStr));
			map.setNumberTag(name, number);
		}
		catch (std::logic_error&) {}
	}



	DoubleNumberTextProcessor::DoubleNumberTextProcessor(const std::string & firstName, const std::string & secondName)
		: FrameProcessor(firstName), secondName(secondName) {}

	void DoubleNumberTextProcessor::process(std::istream& readStream, TagMap & map, std::uint32_t size) const {
		std::string all = readStringWithEncoding(readStream, size);
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



	FullDateProcessor::FullDateProcessor(const std::string & name)
		: FrameProcessor(name) {}

	void FullDateProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size) const {
		std::string text = readStringWithEncoding(readStream, size);
		types::Date date = types::Date::parseString(text);

		if (!date.isEmpty())
			map.setDateTag(name, date);
	}



	DateProcessor::DateProcessor(const std::string & name)
		: FrameProcessor(name) {}

	void DateProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size) const {
		std::string date = readStringWithEncoding(readStream, size);
		if (date.size() != 4)
			return;

        std::uint32_t day = 10 * (date[0] - '0') + date[1] - '0';
        std::uint32_t month = 10 * (date[2] - '0') + date[3] - '0';

		auto dateTag = map.getDateTagPointer(name);
		if (dateTag != nullptr)
			dateTag->getDate().setAll(dateTag->getDate().getYear(), month, day);
		else
			map.setDateTag(name, MonthDayDate(month, day));
	}



	YearProcessor::YearProcessor(const std::string & name)
		: FrameProcessor(name) {}

	void YearProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size) const {
		std::string yearStr = readStringWithEncoding(readStream, size);
		if (yearStr.size() != 4)
			return;
		try {
			std::uint32_t year = std::stoul(yearStr);
			auto dateTag = map.getDateTagPointer(name);
			if (dateTag != nullptr)
				dateTag->getDate().setAll(year, dateTag->getDate().getMonth(), dateTag->getDate().getDay());
			else
				map.setDateTag(name, types::Date(year));
		}
		catch (std::logic_error&) {}
	}



	GenreProcessor::GenreProcessor()
		: FrameProcessor(TagMap::GENRE()) {}

	void GenreProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size) const {
		std::string genres = readStringWithEncoding(readStream, size);
		if (!genres.empty())
			map.setStringTag(name, processGenreString(std::move(genres)));
	}



	CustomTextProcessor::CustomTextProcessor()
		: FrameProcessor(TagMap::BARCODE()) {}

	void CustomTextProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size) const {
		std::uint64_t beforeReadPos;
		std::uint64_t afterReadPos;

		beforeReadPos = readStream.tellg();
		TextEncoding encoding = static_cast<TextEncoding>(readStream.get());
		std::string name = readStringByEncoding(encoding, readStream);
		afterReadPos = readStream.tellg();

		std::string description = readStringByEncoding(encoding, readStream, size - (afterReadPos - beforeReadPos));

		if (!name.empty() && !description.empty()) {
			boost::to_upper(name);
			auto it = std::remove_if(name.begin(), name.end(), boost::is_space());
			if (it != name.end())
				name.erase(it, name.end());

			if (name == TagMap::BARCODE()) {
				types::Barcode barcode(description);
				if (!barcode.isEmpty())
					map.setBarcodeTag(name, barcode);
			} else
				map.setStringTag(name, description);
		}
	}



	CommentProcessor::CommentProcessor()
		: FrameProcessor(TagMap::COMMENT()) {}

	void CommentProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size) const {
		std::uint64_t beforeReadPos;
		std::uint64_t afterReadPos;

		beforeReadPos = readStream.tellg();
		TextEncoding encoding = static_cast<TextEncoding>(readStream.get());
		readStream.seekg(3, std::ios::cur);
		std::string shortComm = readStringByEncoding(encoding, readStream);
		afterReadPos = readStream.tellg();

		std::string longComm = readStringByEncoding(encoding, readStream, size - (afterReadPos - beforeReadPos));

		if (!longComm.empty())
			map.setStringTag(name, longComm);
		else if (!shortComm.empty())
			map.setStringTag(name, shortComm);
	}



	ImageProcessor::ImageProcessor()
		: FrameProcessor(std::string()) {}


	void ImageProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size) const {
		std::uint64_t beforeReadPos;
		std::uint64_t afterReadPos;

		beforeReadPos = readStream.tellg();
		TextEncoding encoding = static_cast<TextEncoding>(readStream.get());
		std::string mimeTypeString = readStringByEncoding(encoding, readStream);
		afterReadPos = readStream.tellg();

		types::Image::MimeType mimeType = string::parseImageMimeType(mimeTypeString);
		if (mimeType == types::Image::MimeType::None) {
			readStream.seekg(size - (afterReadPos - beforeReadPos), std::ios::cur);
			return;
		}

		ImageTag::ImageType imageType = static_cast<ImageTag::ImageType>(readStream.get());
		std::string description = readStringByEncoding(encoding, readStream);
		afterReadPos = readStream.tellg();

		std::vector<std::byte> image(size - (afterReadPos - beforeReadPos));
		readStream.read(reinterpret_cast<char*>(image.data()), image.size());
		if (!image.empty())
			map.setImageTag(imageType, types::Image(std::move(image), description, mimeType));
	}



	LyricsProcessor::LyricsProcessor()
		: FrameProcessor(TagMap::LYRICS()) {}

	void LyricsProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size) const {
		std::uint64_t beforeReadPos;
		std::uint64_t afterReadPos;

		beforeReadPos = readStream.tellg();
		TextEncoding encoding = static_cast<TextEncoding>(readStream.get());

		std::string language(3, '\0');
		readStream.read(language.data(), 3);
		std::string description = readStringByEncoding(encoding, readStream);

		afterReadPos = readStream.tellg();

		std::string lyrics = readStringByEncoding(encoding, readStream, size - (afterReadPos - beforeReadPos));

		if (!description.empty() && !lyrics.empty())
			map.setLyricsTagByLang(language, types::Lyrics(description, lyrics));
	}



	ISRCProcessor::ISRCProcessor()
		: FrameProcessor(TagMap::ISRC()) {}

	void ISRCProcessor::process(std::istream & readStream, TagMap & map, std::uint32_t size) const {
		std::string text = readStringWithEncoding(readStream, size);
		types::ISRC isrc(text);

		if (!isrc.isEmpty())
			map.setISRCTag(name, isrc);
	}



	/*todo: add more support
	 *todo: add support for IPLS in ID3
	 */
    const std::unordered_map<std::string, SharedFrameProcessor> FRAME2_PROCESSORS = {
        {"TT1"s, std::make_shared<TextProcessor>(TagMap::CONTENTGROUP())},
        {"TT2"s, std::make_shared<TextProcessor>(TagMap::TITLE())},
        {"TT3"s, std::make_shared<TextProcessor>(TagMap::SUBTITLE())},
        {"TAL"s, std::make_shared<TextProcessor>(TagMap::ALBUM())},
        {"TOT"s, std::make_shared<TextProcessor>(TagMap::ORIGINALALBUM())},
        {"TP3"s, std::make_shared<TextProcessor>(TagMap::CONDUCTOR())},
        {"TP4"s, std::make_shared<TextProcessor>(TagMap::REMIXER())},
        {"TCR"s, std::make_shared<TextProcessor>(TagMap::COPYRIGHT())},
        {"TPB"s, std::make_shared<TextProcessor>(TagMap::PUBLISHER())},
        {"TKE"s, std::make_shared<TextProcessor>(TagMap::INITIALKEY())},
        {"TRN"s, std::make_shared<TextProcessor>(TagMap::RADIOSTATION())},
        {"TRO"s, std::make_shared<TextProcessor>(TagMap::RADIOSTATIONOWNER())},
        {"TEN"s, std::make_shared<TextProcessor>(TagMap::ENCODEDBY())},
        {"TSS"s, std::make_shared<TextProcessor>(TagMap::ENCODERSETTINGS())},

        {"TCM"s, std::make_shared<MultiStringTextProcessor>(TagMap::COMPOSER())},
        {"TP1"s, std::make_shared<MultiStringTextProcessor>(TagMap::ARTIST())},
        {"TP2"s, std::make_shared<MultiStringTextProcessor>(TagMap::ALBUMARTIST())},
        {"TOA"s, std::make_shared<MultiStringTextProcessor>(TagMap::ORIGINALARTIST())},


        {"WCM"s, std::make_shared<URLProcessor>(TagMap::WWWCOMMERCIAL())},
        {"WCP"s, std::make_shared<URLProcessor>(TagMap::WWWCOPYRIGHT())},
        {"WAF"s, std::make_shared<URLProcessor>(TagMap::WWWFILE())},
        {"WAR"s, std::make_shared<URLProcessor>(TagMap::WWWARTIST())},
        {"WAS"s, std::make_shared<URLProcessor>(TagMap::WWWFILESOURCE())},
        {"WPB"s, std::make_shared<URLProcessor>(TagMap::WWWPUBLISHER())},


        {"TDA"s, std::make_shared<DateProcessor>(TagMap::DATE())},
        {"TYE"s, std::make_shared<YearProcessor>(TagMap::DATE())},
        {"TOR"s, std::make_shared<YearProcessor>(TagMap::ORIGINALDATE())},

        {"TCO"s, std::make_shared<GenreProcessor>()},

        {"TXT"s, std::make_shared<MultiStringTextProcessor>(TagMap::LYRICIST())},
        {"TOL"s, std::make_shared<MultiStringTextProcessor>(TagMap::ORIGINALLYRICIST())},

        {"TBP"s, std::make_shared<SingleNumberTextProcessor>(TagMap::BPM())},

        {"TRK"s, std::make_shared<DoubleNumberTextProcessor>(TagMap::TRACKNUMBER(), TagMap::TOTALTRACKNUMBER())},
        {"TPA"s, std::make_shared<DoubleNumberTextProcessor>(TagMap::DISCNUMBER(), TagMap::TOTALDISCNUMBER())},

        {"COM"s, std::make_shared<CommentProcessor>()},
        //todo: add custom mapping
        {"TXX"s, std::make_shared<CustomTextProcessor>()},

        {"PIC"s, std::make_shared<ImageProcessor>()},

        {"ULT"s, std::make_shared<LyricsProcessor>()},

        {"TRC"s, std::make_shared<ISRCProcessor>()}
    };


    //todo: add support for v4 frames
    const std::unordered_map<std::string, SharedFrameProcessor> FRAME3_PROCESSORS = {
        {"TIT1"s, std::make_shared<TextProcessor>(TagMap::CONTENTGROUP())},
        {"TIT2"s, std::make_shared<TextProcessor>(TagMap::TITLE())},
        {"TIT3"s, std::make_shared<TextProcessor>(TagMap::SUBTITLE())},
        {"TALB"s, std::make_shared<TextProcessor>(TagMap::ALBUM())},
        {"TOAL"s, std::make_shared<TextProcessor>(TagMap::ORIGINALALBUM())},
        {"TPE3"s, std::make_shared<TextProcessor>(TagMap::CONDUCTOR())},
        {"TPE4"s, std::make_shared<TextProcessor>(TagMap::REMIXER())},
        {"TCOP"s, std::make_shared<TextProcessor>(TagMap::COPYRIGHT())},
        {"TPUB"s, std::make_shared<TextProcessor>(TagMap::PUBLISHER())},
        {"TKEY"s, std::make_shared<TextProcessor>(TagMap::INITIALKEY())},
        {"TRSN"s, std::make_shared<TextProcessor>(TagMap::RADIOSTATION())},
        {"TRSO"s, std::make_shared<TextProcessor>(TagMap::RADIOSTATIONOWNER())},
        {"TENC"s, std::make_shared<TextProcessor>(TagMap::ENCODEDBY())},
        {"TSSE"s, std::make_shared<TextProcessor>(TagMap::ENCODERSETTINGS())},

        {"TCOM"s, std::make_shared<MultiStringTextProcessor>(TagMap::COMPOSER())},
        {"TPE1"s, std::make_shared<MultiStringTextProcessor>(TagMap::ARTIST())},
        {"TPE2"s, std::make_shared<MultiStringTextProcessor>(TagMap::ALBUMARTIST())},
        {"TOPE"s, std::make_shared<MultiStringTextProcessor>(TagMap::ORIGINALARTIST())},


        {"WCOM"s, std::make_shared<URLProcessor>(TagMap::WWWCOMMERCIAL())},
        {"WCOP"s, std::make_shared<URLProcessor>(TagMap::WWWCOPYRIGHT())},
        {"WFED"s, std::make_shared<URLProcessor>(TagMap::WWWPODCAST())},
        {"WOAF"s, std::make_shared<URLProcessor>(TagMap::WWWFILE())},
        {"WOAR"s, std::make_shared<URLProcessor>(TagMap::WWWARTIST())},
        {"WOAS"s, std::make_shared<URLProcessor>(TagMap::WWWFILESOURCE())},
        {"WORS"s, std::make_shared<URLProcessor>(TagMap::WWWRADIOPAGE())},
        {"WPAY"s, std::make_shared<URLProcessor>(TagMap::WWWPAYMENT())},
        {"WPUB"s, std::make_shared<URLProcessor>(TagMap::WWWPUBLISHER())},


        {"TDAT"s, std::make_shared<DateProcessor>(TagMap::DATE())},
        {"TYER"s, std::make_shared<YearProcessor>(TagMap::DATE())},
        {"TORY"s, std::make_shared<YearProcessor>(TagMap::ORIGINALDATE())},

        {"TCON"s, std::make_shared<GenreProcessor>()},

        {"TEXT"s, std::make_shared<MultiStringTextProcessor>(TagMap::LYRICIST())},
        {"TOLY"s, std::make_shared<MultiStringTextProcessor>(TagMap::ORIGINALLYRICIST())},

        {"TBMP"s, std::make_shared<SingleNumberTextProcessor>(TagMap::BPM())},

        {"TRCK"s, std::make_shared<DoubleNumberTextProcessor>(TagMap::TRACKNUMBER(), TagMap::TOTALTRACKNUMBER())},
        {"TPOS"s, std::make_shared<DoubleNumberTextProcessor>(TagMap::DISCNUMBER(), TagMap::TOTALDISCNUMBER())},

        {"COMM"s, std::make_shared<CommentProcessor>()},

        {"TXXX"s, std::make_shared<CustomTextProcessor>()},

        {"APIC"s, std::make_shared<ImageProcessor>()},

        {"USLT"s, std::make_shared<LyricsProcessor>()},

        {"TSRC"s, std::make_shared<ISRCProcessor>()}
    };


    //todo: add support for more frames
    const std::unordered_map<std::string, SharedFrameProcessor> FRAME4_PROCESSORS = {
        {"TIT1"s, std::make_shared<TextProcessor>(TagMap::CONTENTGROUP())},
        {"TIT2"s, std::make_shared<TextProcessor>(TagMap::TITLE())},
        {"TIT3"s, std::make_shared<TextProcessor>(TagMap::SUBTITLE())},
        {"TALB"s, std::make_shared<TextProcessor>(TagMap::ALBUM())},
        {"TOAL"s, std::make_shared<TextProcessor>(TagMap::ORIGINALALBUM())},
        {"TPE3"s, std::make_shared<TextProcessor>(TagMap::CONDUCTOR())},
        {"TPE4"s, std::make_shared<TextProcessor>(TagMap::REMIXER())},
        {"TCOP"s, std::make_shared<TextProcessor>(TagMap::COPYRIGHT())},
        {"TPUB"s, std::make_shared<TextProcessor>(TagMap::PUBLISHER())},
        {"TKEY"s, std::make_shared<TextProcessor>(TagMap::INITIALKEY())},
        {"TRSN"s, std::make_shared<TextProcessor>(TagMap::RADIOSTATION())},
        {"TRSO"s, std::make_shared<TextProcessor>(TagMap::RADIOSTATIONOWNER())},
        {"TSST"s, std::make_shared<TextProcessor>(TagMap::SETSUBTITLE())},
        {"TENC"s, std::make_shared<TextProcessor>(TagMap::ENCODEDBY())},
        {"TSSE"s, std::make_shared<TextProcessor>(TagMap::ENCODERSETTINGS())},
        {"TMOO"s, std::make_shared<TextProcessor>(TagMap::MOOD())},

        {"TSO2"s, std::make_shared<MultiStringTextProcessor>(TagMap::ALBUMARTISTSORT())},
        {"TSOA"s, std::make_shared<TextProcessor>(TagMap::ALBUMSORT())},
        {"TSOP"s, std::make_shared<MultiStringTextProcessor>(TagMap::ARTISTSORT())},
        {"TSOC"s, std::make_shared<MultiStringTextProcessor>(TagMap::COMPOSERSORT())},
        {"TSOT"s, std::make_shared<TextProcessor>(TagMap::TITLESORT())},


        {"TCOM"s, std::make_shared<MultiStringTextProcessor>(TagMap::COMPOSER())},
        {"TPE1"s, std::make_shared<MultiStringTextProcessor>(TagMap::ARTIST())},
        {"TPE2"s, std::make_shared<MultiStringTextProcessor>(TagMap::ALBUMARTIST())},
        {"TOPE"s, std::make_shared<MultiStringTextProcessor>(TagMap::ORIGINALARTIST())},

        {"TDRC"s, std::make_shared<FullDateProcessor>(TagMap::DATE())},
        {"TDEN"s, std::make_shared<FullDateProcessor>(TagMap::ENCODINGDATE())},
        {"TDOR"s, std::make_shared<FullDateProcessor>(TagMap::ORIGINALDATE())},

        {"WCOM"s, std::make_shared<URLProcessor>(TagMap::WWWCOMMERCIAL())},
        {"WCOP"s, std::make_shared<URLProcessor>(TagMap::WWWCOPYRIGHT())},
        {"WFED"s, std::make_shared<URLProcessor>(TagMap::WWWPODCAST())},
        {"WOAF"s, std::make_shared<URLProcessor>(TagMap::WWWFILE())},
        {"WOAR"s, std::make_shared<URLProcessor>(TagMap::WWWARTIST())},
        {"WOAS"s, std::make_shared<URLProcessor>(TagMap::WWWFILESOURCE())},
        {"WORS"s, std::make_shared<URLProcessor>(TagMap::WWWRADIOPAGE())},
        {"WPAY"s, std::make_shared<URLProcessor>(TagMap::WWWPAYMENT())},
        {"WPUB"s, std::make_shared<URLProcessor>(TagMap::WWWPUBLISHER())},


        {"TCON"s, std::make_shared<GenreProcessor>()},

        {"TEXT"s, std::make_shared<MultiStringTextProcessor>(TagMap::LYRICIST())},

        {"TBMP"s, std::make_shared<SingleNumberTextProcessor>(TagMap::BPM())},

        {"TRCK"s, std::make_shared<DoubleNumberTextProcessor>(TagMap::TRACKNUMBER(), TagMap::TOTALTRACKNUMBER())},
        {"TPOS"s, std::make_shared<DoubleNumberTextProcessor>(TagMap::DISCNUMBER(), TagMap::TOTALDISCNUMBER())},

        {"COMM"s, std::make_shared<CommentProcessor>()},

        {"TXXX"s, std::make_shared<CustomTextProcessor>()},

        {"APIC"s, std::make_shared<ImageProcessor>()},

        {"USLT"s, std::make_shared<LyricsProcessor>()},

        {"TSRC"s, std::make_shared<ISRCProcessor>()}
    };
}