#include "FrameProcessor.hpp"
#include <tag/priv/id3/TextEncoding.hpp>
#include <tag/priv/id3/MonthDayDate.hpp>
#include <boost/algorithm/string.hpp>
#include "..\vorbis\ValueProcessor.hpp"

namespace tag::priv::id3 {

	FrameProcessor::FrameProcessor(const std::string & name)
		: name(name) {}

	FrameProcessor::~FrameProcessor() {}



	TextProcessor::TextProcessor(const std::string & name)
		: FrameProcessor(name) {}

	void TextProcessor::process(std::istream& readStream, AudioTagMap & map, unsigned size) const {
		std::string text = readStringWithEncoding(readStream, size);
		if (!text.empty())
			map.setStringTag(name, text);
	}



	MultiStringTextProcessor::MultiStringTextProcessor(const std::string & name)
		: FrameProcessor(name) {}

	void MultiStringTextProcessor::process(std::istream& readStream, AudioTagMap & map, unsigned size) const {
		std::string text = readStringWithEncoding(readStream, size);
		if (!text.empty())
			map.setStringTag(name, processMultiString(text));
	}



	URLProcessor::URLProcessor(const std::string & name)
		: FrameProcessor(name) {}

	void URLProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
		map.setStringTag(name, readUtf8(readStream, size));
	}



	SingleNumberTextProcessor::SingleNumberTextProcessor(const std::string &name)
		: FrameProcessor(name) {}

	void SingleNumberTextProcessor::process(std::istream& readStream, AudioTagMap & map, unsigned size) const {
		std::string numStr = readStringWithEncoding(readStream, size);
		try {
			unsigned number = static_cast<unsigned>(std::stol(numStr));
			map.setNumberTag(name, number);
		}
		catch (std::logic_error&) {}
	}



	DoubleNumberTextProcessor::DoubleNumberTextProcessor(const std::string & firstName, const std::string & secondName)
		: FrameProcessor(firstName), secondName(secondName) {}

	void DoubleNumberTextProcessor::process(std::istream& readStream, AudioTagMap & map, unsigned size) const {
		std::string all = readStringWithEncoding(readStream, size);
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



	FullDateProcessor::FullDateProcessor(const std::string & name)
		: FrameProcessor(name) {}

	void FullDateProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
		std::string text = readStringWithEncoding(readStream, size);
		types::Date date = types::Date::parseString(text);

		if (!date.isNull())
			map.setDateTag(name, date);
	}



	DateProcessor::DateProcessor(const std::string & name)
		: FrameProcessor(name) {}

	void DateProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
		std::string date = readStringWithEncoding(readStream, size);
		if (date.size() != 4)
			return;

        unsigned day = 10 * (date[0] - '0') + date[1] - '0';
        unsigned month = 10 * (date[2] - '0') + date[3] - '0';

		auto dateTag = map.getDateTag(name);
		if (dateTag != nullptr)
			dateTag->getDate().setAll(dateTag->getDate().getYear(), month, day);
		else
			map.setDateTag(name, MonthDayDate(month, day));
	}



	YearProcessor::YearProcessor(const std::string & name)
		: FrameProcessor(name) {}

	void YearProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
		std::string yearStr = readStringWithEncoding(readStream, size);
		if (yearStr.size() != 4)
			return;
		try {
			unsigned year = std::stoul(yearStr);
			auto dateTag = map.getDateTag(name);
			if (dateTag != nullptr)
				dateTag->getDate().setAll(year, dateTag->getDate().getMonth(), dateTag->getDate().getDay());
			else
				map.setDateTag(name, types::Date(year));
		}
		catch (std::logic_error&) {}
	}



	GenreProcessor::GenreProcessor()
		: FrameProcessor(AudioTagMap::GENRE()) {}

	void GenreProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
		std::string genres = readStringWithEncoding(readStream, size);
		if (!genres.empty())
			map.setStringTag(name, processGenreString(std::move(genres)));
	}



	CustomTextProcessor::CustomTextProcessor()
		: FrameProcessor(std::string()) {}

	void CustomTextProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
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
			map.setStringTag(name, description);
		}
	}



	CommentProcessor::CommentProcessor()
		: FrameProcessor(AudioTagMap::COMMENT()) {}

	void CommentProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
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


	void ImageProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
		std::uint64_t beforeReadPos;
		std::uint64_t afterReadPos;

		beforeReadPos = readStream.tellg();
		TextEncoding encoding = static_cast<TextEncoding>(readStream.get());
		std::string mimeTypeStr = readStringByEncoding(encoding, readStream);
		afterReadPos = readStream.tellg();

		types::Image::MimeType mimeType;
		if (mimeTypeStr == "image/jpeg"s)
			mimeType = types::Image::MimeType::ImageJpeg;
		else if (mimeTypeStr == "image/png"s)
			mimeType = types::Image::MimeType::ImagePng;
		else {
			readStream.seekg(size - (afterReadPos - beforeReadPos), std::ios::cur);
			return;
		}
		ImageAudioTag::ImageType imageType = static_cast<ImageAudioTag::ImageType>(readStream.get());

		std::string description = readStringByEncoding(encoding, readStream);
		afterReadPos = readStream.tellg();

		std::vector<std::byte> image(size - (afterReadPos - beforeReadPos));
		readStream.read(reinterpret_cast<char*>(image.data()), image.size());
		if (!image.empty())
			map.setImageTag(imageType, types::Image(std::move(image), description, mimeType));
	}



	LyricsProcessor::LyricsProcessor()
		: FrameProcessor(AudioTagMap::LYRICS()) {}

	void LyricsProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
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
		: FrameProcessor(AudioTagMap::ISRC()) {}

	void ISRCProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
		std::string text = readStringWithEncoding(readStream, size);
		types::ISRC isrc(text);

		if (!isrc.isEmpty())
			map.setISRCTag(isrc);
	}



	/*todo: add more support
	 *todo: add support for IPLS in ID3
	 */
	const std::unordered_map<std::string, SharedFrameProcessor> FRAME2_PROCESSORS = {
		std::make_pair("TT1"s, std::make_shared<TextProcessor>(AudioTagMap::CONTENTGROUP())),
		std::make_pair("TT2"s, std::make_shared<TextProcessor>(AudioTagMap::TITLE())),
		std::make_pair("TT3"s, std::make_shared<TextProcessor>(AudioTagMap::SUBTITLE())),
		std::make_pair("TAL"s, std::make_shared<TextProcessor>(AudioTagMap::ALBUM())),
		std::make_pair("TOT"s, std::make_shared<TextProcessor>(AudioTagMap::ORIGINALALBUM())),
		std::make_pair("TP3"s, std::make_shared<TextProcessor>(AudioTagMap::CONDUCTOR())),
		std::make_pair("TP4"s, std::make_shared<TextProcessor>(AudioTagMap::REMIXER())),
		std::make_pair("TCR"s, std::make_shared<TextProcessor>(AudioTagMap::COPYRIGHT())),
		std::make_pair("TPB"s, std::make_shared<TextProcessor>(AudioTagMap::PUBLISHER())),
		std::make_pair("TKE"s, std::make_shared<TextProcessor>(AudioTagMap::INITIALKEY())),
		std::make_pair("TRN"s, std::make_shared<TextProcessor>(AudioTagMap::RADIOSTATION())),
		std::make_pair("TRO"s, std::make_shared<TextProcessor>(AudioTagMap::RADIOSTATIONOWNER())),
		std::make_pair("TEN"s, std::make_shared<TextProcessor>(AudioTagMap::ENCODEDBY())),
		std::make_pair("TSS"s, std::make_shared<TextProcessor>(AudioTagMap::ENCODERSETTINGS())),

		std::make_pair("TCM"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::COMPOSER())),
		std::make_pair("TP1"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::ARTIST())),
		std::make_pair("TP2"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::ALBUMARTIST())),
		std::make_pair("TOA"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::ORIGINALARTIST())),


		std::make_pair("WCM"s, std::make_shared<URLProcessor>(AudioTagMap::WWWCOMMERCIAL())),
		std::make_pair("WCP"s, std::make_shared<URLProcessor>(AudioTagMap::WWWCOPYRIGHT())),
		std::make_pair("WAF"s, std::make_shared<URLProcessor>(AudioTagMap::WWWFILE())),
		std::make_pair("WAR"s, std::make_shared<URLProcessor>(AudioTagMap::WWWARTIST())),
		std::make_pair("WAS"s, std::make_shared<URLProcessor>(AudioTagMap::WWWFILESOURCE())),
		std::make_pair("WPB"s, std::make_shared<URLProcessor>(AudioTagMap::WWWPUBLISHER())),


		std::make_pair("TDA"s, std::make_shared<DateProcessor>(AudioTagMap::DATE())),
		std::make_pair("TYE"s, std::make_shared<YearProcessor>(AudioTagMap::DATE())),
		std::make_pair("TOR"s, std::make_shared<YearProcessor>(AudioTagMap::ORIGINALDATE())),

		std::make_pair("TCO"s, std::make_shared<GenreProcessor>()),

		std::make_pair("TXT"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::LYRICIST())),
		std::make_pair("TOL"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::ORIGINALLYRICIST())),

		std::make_pair("TBP"s, std::make_shared<SingleNumberTextProcessor>(AudioTagMap::BPM())),

		std::make_pair("TRK"s, std::make_shared<DoubleNumberTextProcessor>(AudioTagMap::TRACKNUMBER(), AudioTagMap::TOTALTRACKNUMBER())),
		std::make_pair("TPA"s, std::make_shared<DoubleNumberTextProcessor>(AudioTagMap::DISCNUMBER(), AudioTagMap::TOTALDISCNUMBER())),

		std::make_pair("COM"s, std::make_shared<CommentProcessor>()),
		//todo: add custom mapping
		std::make_pair("TXX"s, std::make_shared<CustomTextProcessor>()),

		std::make_pair("PIC"s, std::make_shared<ImageProcessor>()),

		std::make_pair("ULT"s, std::make_shared<LyricsProcessor>()),

		std::make_pair("TRC"s, std::make_shared<ISRCProcessor>())
	};


	//todo: add support for v4 frames
	const std::unordered_map<std::string, SharedFrameProcessor> FRAME3_PROCESSORS = {
		std::make_pair("TIT1"s, std::make_shared<TextProcessor>(AudioTagMap::CONTENTGROUP())),
		std::make_pair("TIT2"s, std::make_shared<TextProcessor>(AudioTagMap::TITLE())),
		std::make_pair("TIT3"s, std::make_shared<TextProcessor>(AudioTagMap::SUBTITLE())),
		std::make_pair("TALB"s, std::make_shared<TextProcessor>(AudioTagMap::ALBUM())),
		std::make_pair("TOAL"s, std::make_shared<TextProcessor>(AudioTagMap::ORIGINALALBUM())),
		std::make_pair("TPE3"s, std::make_shared<TextProcessor>(AudioTagMap::CONDUCTOR())),
		std::make_pair("TPE4"s, std::make_shared<TextProcessor>(AudioTagMap::REMIXER())),
		std::make_pair("TCOP"s, std::make_shared<TextProcessor>(AudioTagMap::COPYRIGHT())),
		std::make_pair("TPUB"s, std::make_shared<TextProcessor>(AudioTagMap::PUBLISHER())),
		std::make_pair("TKEY"s, std::make_shared<TextProcessor>(AudioTagMap::INITIALKEY())),
		std::make_pair("TRSN"s, std::make_shared<TextProcessor>(AudioTagMap::RADIOSTATION())),
		std::make_pair("TRSO"s, std::make_shared<TextProcessor>(AudioTagMap::RADIOSTATIONOWNER())),
		std::make_pair("TENC"s, std::make_shared<TextProcessor>(AudioTagMap::ENCODEDBY())),
		std::make_pair("TSSE"s, std::make_shared<TextProcessor>(AudioTagMap::ENCODERSETTINGS())),

		std::make_pair("TCOM"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::COMPOSER())),
		std::make_pair("TPE1"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::ARTIST())),
		std::make_pair("TPE2"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::ALBUMARTIST())),
		std::make_pair("TOPE"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::ORIGINALARTIST())),


		std::make_pair("WCOM"s, std::make_shared<URLProcessor>(AudioTagMap::WWWCOMMERCIAL())),
		std::make_pair("WCOP"s, std::make_shared<URLProcessor>(AudioTagMap::WWWCOPYRIGHT())),
		std::make_pair("WOAF"s, std::make_shared<URLProcessor>(AudioTagMap::WWWFILE())),
		std::make_pair("WOAR"s, std::make_shared<URLProcessor>(AudioTagMap::WWWARTIST())),
		std::make_pair("WOAS"s, std::make_shared<URLProcessor>(AudioTagMap::WWWFILESOURCE())),
		std::make_pair("WORS"s, std::make_shared<URLProcessor>(AudioTagMap::WWWRADIOPAGE())),
		std::make_pair("WPUB"s, std::make_shared<URLProcessor>(AudioTagMap::WWWPUBLISHER())),


		std::make_pair("TDAT"s, std::make_shared<DateProcessor>(AudioTagMap::DATE())),
		std::make_pair("TYER"s, std::make_shared<YearProcessor>(AudioTagMap::DATE())),
		std::make_pair("TORY"s, std::make_shared<YearProcessor>(AudioTagMap::ORIGINALDATE())),

		std::make_pair("TCON"s, std::make_shared<GenreProcessor>()),

		std::make_pair("TEXT"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::LYRICIST())),
		std::make_pair("TOLY"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::ORIGINALLYRICIST())),

		std::make_pair("TBMP"s, std::make_shared<SingleNumberTextProcessor>(AudioTagMap::BPM())),

		std::make_pair("TRCK"s, std::make_shared<DoubleNumberTextProcessor>(AudioTagMap::TRACKNUMBER(), AudioTagMap::TOTALTRACKNUMBER())),
		std::make_pair("TPOS"s, std::make_shared<DoubleNumberTextProcessor>(AudioTagMap::DISCNUMBER(), AudioTagMap::TOTALDISCNUMBER())),

		std::make_pair("COMM"s, std::make_shared<CommentProcessor>()),

		std::make_pair("TXXX"s, std::make_shared<CustomTextProcessor>()),

		std::make_pair("APIC"s, std::make_shared<ImageProcessor>()),

		std::make_pair("USLT"s, std::make_shared<LyricsProcessor>()),

		std::make_pair("TSRC"s, std::make_shared<ISRCProcessor>())
	};


	//todo: add support for more frames
	const std::unordered_map<std::string, SharedFrameProcessor> FRAME4_PROCESSORS = {
		std::make_pair("TIT1"s, std::make_shared<TextProcessor>(AudioTagMap::CONTENTGROUP())),
		std::make_pair("TIT2"s, std::make_shared<TextProcessor>(AudioTagMap::TITLE())),
		std::make_pair("TIT3"s, std::make_shared<TextProcessor>(AudioTagMap::SUBTITLE())),
		std::make_pair("TALB"s, std::make_shared<TextProcessor>(AudioTagMap::ALBUM())),
		std::make_pair("TOAL"s, std::make_shared<TextProcessor>(AudioTagMap::ORIGINALALBUM())),
		std::make_pair("TPE3"s, std::make_shared<TextProcessor>(AudioTagMap::CONDUCTOR())),
		std::make_pair("TPE4"s, std::make_shared<TextProcessor>(AudioTagMap::REMIXER())),
		std::make_pair("TCOP"s, std::make_shared<TextProcessor>(AudioTagMap::COPYRIGHT())),
		std::make_pair("TPUB"s, std::make_shared<TextProcessor>(AudioTagMap::PUBLISHER())),
		std::make_pair("TKEY"s, std::make_shared<TextProcessor>(AudioTagMap::INITIALKEY())),
		std::make_pair("TRSN"s, std::make_shared<TextProcessor>(AudioTagMap::RADIOSTATION())),
		std::make_pair("TRSO"s, std::make_shared<TextProcessor>(AudioTagMap::RADIOSTATIONOWNER())),
		std::make_pair("TSST"s, std::make_shared<TextProcessor>(AudioTagMap::SETSUBTITLE())),
		std::make_pair("TENC"s, std::make_shared<TextProcessor>(AudioTagMap::ENCODEDBY())),
		std::make_pair("TSSE"s, std::make_shared<TextProcessor>(AudioTagMap::ENCODERSETTINGS())),
		std::make_pair("TMOO"s, std::make_shared<TextProcessor>(AudioTagMap::MOOD())),

        std::make_pair("TSO2"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::ALBUMARTISTSORT())),
        std::make_pair("TSOA"s, std::make_shared<TextProcessor>(AudioTagMap::ALBUMSORT())),
		std::make_pair("TSOP"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::ARTISTSORT())),
		std::make_pair("TSOC"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::COMPOSERSORT())),
		std::make_pair("TSOT"s, std::make_shared<TextProcessor>(AudioTagMap::TITLESORT())),


		std::make_pair("TCOM"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::COMPOSER())),
		std::make_pair("TPE1"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::ARTIST())),
		std::make_pair("TPE2"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::ALBUMARTIST())),
		std::make_pair("TOPE"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::ORIGINALARTIST())),

		std::make_pair("TDRC"s, std::make_shared<FullDateProcessor>(AudioTagMap::DATE())),
		std::make_pair("TDEN"s, std::make_shared<FullDateProcessor>(AudioTagMap::ENCODINGDATE())),
		std::make_pair("TDOR"s, std::make_shared<FullDateProcessor>(AudioTagMap::ORIGINALDATE())),

		std::make_pair("WCOM"s, std::make_shared<URLProcessor>(AudioTagMap::WWWCOMMERCIAL())),
		std::make_pair("WCOP"s, std::make_shared<URLProcessor>(AudioTagMap::WWWCOPYRIGHT())),
		std::make_pair("WOAF"s, std::make_shared<URLProcessor>(AudioTagMap::WWWFILE())),
		std::make_pair("WOAR"s, std::make_shared<URLProcessor>(AudioTagMap::WWWARTIST())),
		std::make_pair("WOAS"s, std::make_shared<URLProcessor>(AudioTagMap::WWWFILESOURCE())),
		std::make_pair("WORS"s, std::make_shared<URLProcessor>(AudioTagMap::WWWRADIOPAGE())),
		std::make_pair("WPUB"s, std::make_shared<URLProcessor>(AudioTagMap::WWWPUBLISHER())),


		std::make_pair("TCON"s, std::make_shared<GenreProcessor>()),

		std::make_pair("TEXT"s, std::make_shared<MultiStringTextProcessor>(AudioTagMap::LYRICIST())),

		std::make_pair("TBMP"s, std::make_shared<SingleNumberTextProcessor>(AudioTagMap::BPM())),

		std::make_pair("TRCK"s, std::make_shared<DoubleNumberTextProcessor>(AudioTagMap::TRACKNUMBER(), AudioTagMap::TOTALTRACKNUMBER())),
		std::make_pair("TPOS"s, std::make_shared<DoubleNumberTextProcessor>(AudioTagMap::DISCNUMBER(), AudioTagMap::TOTALDISCNUMBER())),

		std::make_pair("COMM"s, std::make_shared<CommentProcessor>()),

		std::make_pair("TXXX"s, std::make_shared<CustomTextProcessor>()),

		std::make_pair("APIC"s, std::make_shared<ImageProcessor>()),

		std::make_pair("USLT"s, std::make_shared<LyricsProcessor>()),

		std::make_pair("TSRC"s, std::make_shared<ISRCProcessor>())
	};
}