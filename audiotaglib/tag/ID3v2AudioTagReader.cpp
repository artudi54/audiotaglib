#include "ID3v2AudioTagReader.hpp"

namespace io = boost::iostreams;

namespace tag::reader {
	AudioTagMap ID3v2AudioTagReader::readTag(std::istream & readStream) const {
		AudioTagMap map;
		Header header = readID3Header(readStream);
		unsigned leftSize = header.size;

		if (header.majorVersion > 2 && header.flags & Header::EXTENDED_HEADER)
			leftSize -= skipExtendedHeader(readStream);
		if (header.majorVersion == 4 && header.flags & Header::FOOTER_PRESENT)
			leftSize -= 10;

		const std::unordered_map<std::string, SharedFrameProcessor> *PROCESSORS = nullptr;
		Frame (*readFrame)(std::istream&) = nullptr;
		unsigned framesHeaderSize = 0;

		if (header.majorVersion == 2) {
			PROCESSORS = &FRAME2_PROCESSORS;
			readFrame = read2Frame;
			framesHeaderSize = 6;
		} else if (header.majorVersion == 3) {
			PROCESSORS = &FRAME3_PROCESSORS;
			readFrame = read3Frame;
			framesHeaderSize = 10;
		} else if (header.majorVersion == 4) {
			PROCESSORS = &FRAME4_PROCESSORS;
			readFrame = read4Frame;
			framesHeaderSize = 10;
		}

		//todo: fix padding
		Frame frame;
		while (leftSize > 0) {
			int next = readStream.get();
			if (next != 0) {
				readStream.unget();
				frame = readFrame(readStream);
				leftSize -= framesHeaderSize + frame.size;
				processFrame(frame, map, *PROCESSORS);
			} else
				--leftSize;
		}
		return map;
	}



	void ID3v2AudioTagReader::processFrame(Frame & frame, AudioTagMap &map, const std::unordered_map<std::string, SharedFrameProcessor>& PROCESSORS) const {
		auto it = PROCESSORS.find(frame.identifier);
		if (it != PROCESSORS.end()) {
			io::array_source source(reinterpret_cast<char*>(frame.data.data()), frame.size);
			io::stream<boost::iostreams::array_source> stream(source);
			it->second->process(stream, map, frame.size);
		}
	}









	ID3v2AudioTagReader::FrameProcessor::FrameProcessor(const std::string & name)
		: name(name) {
	}

	ID3v2AudioTagReader::FrameProcessor::~FrameProcessor() {}



	ID3v2AudioTagReader::TextProcessor::TextProcessor(const std::string & name)
		: FrameProcessor(name) {
	}

	void ID3v2AudioTagReader::TextProcessor::process(std::istream& readStream, AudioTagMap & map, unsigned size) const {
		TextEncoding encoding = static_cast<TextEncoding>(readStream.get());
		std::string text = readStringByEncoding(encoding, readStream, size - 1);
		if (!text.empty())
			map.setStringTag(name, text);
	}





	ID3v2AudioTagReader::MultistringTextProcessor::MultistringTextProcessor(const std::string & name)
		: FrameProcessor(name) {
	}

	void ID3v2AudioTagReader::MultistringTextProcessor::process(std::istream& readStream, AudioTagMap & map, unsigned size) const {
		static const std::regex PATTERN(R"(\s*[;,/\\0\\]\s*)"s);

		TextEncoding encoding = static_cast<TextEncoding>(readStream.get());
		std::string text = readStringByEncoding(encoding, readStream, size - 1);
		if (!text.empty())
			map.setStringTag(name, processMultistring(text));
	}


	ID3v2AudioTagReader::URLProcessor::URLProcessor(const std::string & name)
		: FrameProcessor(name) {
	}

	void ID3v2AudioTagReader::URLProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
		map.setStringTag(name, readUtf8(readStream, size));
	}



	ID3v2AudioTagReader::SingleNumberTextProcessor::SingleNumberTextProcessor(const std::string &name)
		: FrameProcessor(name) {
	}

	void ID3v2AudioTagReader::SingleNumberTextProcessor::process(std::istream& readStream, AudioTagMap & map, unsigned size) const {
		TextEncoding encoding = static_cast<TextEncoding>(readStream.get());
		std::string numStr = readStringByEncoding(encoding, readStream, size -1);
		try {
			unsigned number = static_cast<unsigned>(std::stol(numStr));
			map.setNumberTag(name, number);
		}
		catch (std::logic_error&) {}
	}



	ID3v2AudioTagReader::DoubleNumberTextProcessor::DoubleNumberTextProcessor(const std::string & firstName, const std::string & secondName)
		: FrameProcessor(firstName), secondName(secondName) {
	}

	void ID3v2AudioTagReader::DoubleNumberTextProcessor::process(std::istream& readStream, AudioTagMap & map, unsigned size) const {
		TextEncoding encoding = static_cast<TextEncoding>(readStream.get());
		std::string all = readStringByEncoding(encoding, readStream, size - 1);
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





	ID3v2AudioTagReader::FullDateProcessor::FullDateProcessor(const std::string & name)
		: FrameProcessor(name) {}

	void ID3v2AudioTagReader::FullDateProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
		TextEncoding endoding = static_cast<TextEncoding>(readStream.get());
		std::string text = readStringByEncoding(endoding, readStream, std::min(size, 10u));
		type::Date date = type::Date::parseString(text);

		if (!date.isNull())
			map.setDateTag(name, date);
	}







	ID3v2AudioTagReader::DateProcessor::DateProcessor(const std::string & name)
		: FrameProcessor(name) {}

	void ID3v2AudioTagReader::DateProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
		TextEncoding encoding = static_cast<TextEncoding>(readStream.get());
		std::string date = readStringByEncoding(encoding, readStream, size - 1);
		if (date.size() != 4)
			return;
		std::uint8_t month = 10 * (date[0] - '0') + date[1] - '0';
		std::uint8_t day = 10 * (date[2] - '0') + date[3] - '0';
		auto it = map.getDateTag(name);
		if (it != nullptr)
			it->getDate().setAll(it->getDate().getYear(), month, day);
		else
			map.setDateTag(name, type::Date(month, day));
	}



	ID3v2AudioTagReader::YearProcessor::YearProcessor(const std::string & name)
		: FrameProcessor(name) {
	}


	void ID3v2AudioTagReader::YearProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
		TextEncoding encoding = static_cast<TextEncoding>(readStream.get());
		std::string yearStr = readStringByEncoding(encoding, readStream, size -1);
		if (yearStr.size() != 4)
			return;
		try {
			unsigned year = std::stoi(yearStr);
			auto it = map.getDateTag(name);
			if (it != nullptr)
				it->getDate().setAll(year, it->getDate().getMonth(), it->getDate().getDay());
			else
				map.setDateTag(name, type::Date(year));
		}
		catch (std::logic_error&) {}
	}




	ID3v2AudioTagReader::GenreProcessor::GenreProcessor()
		: FrameProcessor(AudioTagMap::GENRE()) {
	}

	void ID3v2AudioTagReader::GenreProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
		TextEncoding encoding = static_cast<TextEncoding>(readStream.get());
		std::string genres = readStringByEncoding(encoding, readStream, size -1);
		if (!genres.empty())
			map.setStringTag(name, processGenreString(std::move(genres)));
	}






	ID3v2AudioTagReader::CustomTextProcessor::CustomTextProcessor()
		: FrameProcessor(std::string()) {
	}

	void ID3v2AudioTagReader::CustomTextProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
		TextEncoding encoding = static_cast<TextEncoding>(readStream.get());
		std::string name = readStringByEncoding(encoding, readStream);
		std::string description = readStringByEncoding(encoding, readStream);

		if (!name.empty() && !description.empty()) {
			boost::to_upper(name);
			auto it = std::remove_if(name.begin(), name.end(), boost::is_space());
			if (it != name.end())
				name.erase(it, name.end());
			map.setStringTag(name, description);
		}
	}



	ID3v2AudioTagReader::CommentProcessor::CommentProcessor()
		: FrameProcessor(AudioTagMap::COMMENT()) {
	}

	void ID3v2AudioTagReader::CommentProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
		TextEncoding encoding = static_cast<TextEncoding>(readStream.get());
		readStream.seekg(3, std::ios::cur);
		std::string shortComm = readStringByEncoding(encoding, readStream);
		std::string longComm = readStringByEncoding(encoding, readStream);
		if (!longComm.empty())
			map.setStringTag(name, longComm);
		else if (!shortComm.empty())
			map.setStringTag(name, shortComm);
	}



	ID3v2AudioTagReader::ImageProcessor::ImageProcessor()
		: FrameProcessor(std::string()) {
	}

	void ID3v2AudioTagReader::ImageProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
		TextEncoding encoding = static_cast<TextEncoding>(readStream.get());
		std::string mimeTypeStr = readStringByEncoding(encoding, readStream);

		type::Image::MimeType mimeType;
		if (mimeTypeStr == "image/jpeg"s)
			mimeType = type::Image::MimeType::ImageJpeg;
		else if (mimeTypeStr == "image/png"s)
			mimeType = type::Image::MimeType::ImagePng;
		else
			return;

		ImageAudioTag::ImageType imageType = static_cast<ImageAudioTag::ImageType>(readStream.get());
		std::string description = readStringByEncoding(encoding, readStream);
		std::vector<std::byte> image(size - readStream.tellg());
		readStream.read(reinterpret_cast<char*>(image.data()), image.size());
		if (!image.empty())
			map.setImageTag(imageType, type::Image(std::move(image), description, mimeType));
	}




	ID3v2AudioTagReader::LyricsProcessor::LyricsProcessor()
		: FrameProcessor(AudioTagMap::LYRICS()) {}

	void ID3v2AudioTagReader::LyricsProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size) const {
		TextEncoding encoding = static_cast<TextEncoding>(readStream.get());
		std::string language(3, '\0');
		readStream.read(language.data(), 3);
		std::string description = readStringByEncoding(encoding, readStream);
		std::string lyrics = readStringByEncoding(encoding, readStream);
		if (!description.empty() && !lyrics.empty())
			map.setLyricsTagByLang(language, type::Lyrics(description, lyrics));
	}







	//todo: add more support
	const std::unordered_map<std::string, ID3v2AudioTagReader::SharedFrameProcessor> ID3v2AudioTagReader::FRAME2_PROCESSORS = {
		std::make_pair("TT2"s, std::make_shared<TextProcessor>(AudioTagMap::TITLE())),
		std::make_pair("TT3"s, std::make_shared<TextProcessor>(AudioTagMap::SUBTITLE())),
		std::make_pair("TAL"s, std::make_shared<TextProcessor>(AudioTagMap::ALBUM())),
		std::make_pair("TOT"s, std::make_shared<TextProcessor>(AudioTagMap::ORIGINALALBUM())),
		std::make_pair("TP3"s, std::make_shared<TextProcessor>(AudioTagMap::CONDUCTOR())),
		std::make_pair("TPB"s, std::make_shared<TextProcessor>(AudioTagMap::PUBLISHER())),

		std::make_pair("TCM"s, std::make_shared<MultistringTextProcessor>(AudioTagMap::COMPOSER())),
		std::make_pair("TP1"s, std::make_shared<MultistringTextProcessor>(AudioTagMap::ARTIST())),
		std::make_pair("TP2"s, std::make_shared<MultistringTextProcessor>(AudioTagMap::ALBUMARTIST())),
		std::make_pair("TOA"s, std::make_shared<MultistringTextProcessor>(AudioTagMap::ORIGINALARTIST())),


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

		std::make_pair("TXT"s, std::make_shared<MultistringTextProcessor>(AudioTagMap::LYRICIST())),
		std::make_pair("TOL"s, std::make_shared<MultistringTextProcessor>(AudioTagMap::ORIGINALLYRICIST())),

		std::make_pair("TBP"s, std::make_shared<SingleNumberTextProcessor>(AudioTagMap::BPM())),

		std::make_pair("TRK"s, std::make_shared<DoubleNumberTextProcessor>(AudioTagMap::TRACKNUMBER(), AudioTagMap::TOTALTRACKNUMBER())),
		std::make_pair("TPA"s, std::make_shared<DoubleNumberTextProcessor>(AudioTagMap::DISCNUMBER(), AudioTagMap::TOTALDISCNUMBER())),

		std::make_pair("COM"s, std::make_shared<CommentProcessor>()),

		std::make_pair("TXX"s, std::make_shared<CustomTextProcessor>()),

		std::make_pair("PIC"s, std::make_shared<ImageProcessor>()),

		std::make_pair("ULT"s, std::make_shared<LyricsProcessor>())
	};




	//todo: add support for v4 frames
	const std::unordered_map<std::string, ID3v2AudioTagReader::SharedFrameProcessor> ID3v2AudioTagReader::FRAME3_PROCESSORS = {
		std::make_pair("TIT2"s, std::make_shared<TextProcessor>(AudioTagMap::TITLE())),
		std::make_pair("TIT3"s, std::make_shared<TextProcessor>(AudioTagMap::SUBTITLE())),
		std::make_pair("TALB"s, std::make_shared<TextProcessor>(AudioTagMap::ALBUM())),
		std::make_pair("TOAL"s, std::make_shared<TextProcessor>(AudioTagMap::ORIGINALALBUM())),
		std::make_pair("TPE3"s, std::make_shared<TextProcessor>(AudioTagMap::CONDUCTOR())),
		std::make_pair("TPUB"s, std::make_shared<TextProcessor>(AudioTagMap::PUBLISHER())),

		std::make_pair("TCOM"s, std::make_shared<MultistringTextProcessor>(AudioTagMap::COMPOSER())),
		std::make_pair("TPE1"s, std::make_shared<MultistringTextProcessor>(AudioTagMap::ARTIST())),
		std::make_pair("TPE2"s, std::make_shared<MultistringTextProcessor>(AudioTagMap::ALBUMARTIST())),
		std::make_pair("TOPE"s, std::make_shared<MultistringTextProcessor>(AudioTagMap::ORIGINALARTIST())),


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

		std::make_pair("TEXT"s, std::make_shared<MultistringTextProcessor>(AudioTagMap::LYRICIST())),
		std::make_pair("TOLY"s, std::make_shared<MultistringTextProcessor>(AudioTagMap::ORIGINALLYRICIST())),

		std::make_pair("TBMP"s, std::make_shared<SingleNumberTextProcessor>(AudioTagMap::BPM())),

		std::make_pair("TRCK"s, std::make_shared<DoubleNumberTextProcessor>(AudioTagMap::TRACKNUMBER(), AudioTagMap::TOTALTRACKNUMBER())),
		std::make_pair("TPOS"s, std::make_shared<DoubleNumberTextProcessor>(AudioTagMap::DISCNUMBER(), AudioTagMap::TOTALDISCNUMBER())),

		std::make_pair("COMM"s, std::make_shared<CommentProcessor>()),

		std::make_pair("TXXX"s, std::make_shared<CustomTextProcessor>()),

		std::make_pair("APIC"s, std::make_shared<ImageProcessor>()),

		std::make_pair("USLT"s, std::make_shared<LyricsProcessor>())
	};

	//todo: add support for more frames
	const std::unordered_map<std::string, ID3v2AudioTagReader::SharedFrameProcessor> ID3v2AudioTagReader::FRAME4_PROCESSORS = {
		std::make_pair("TIT2"s, std::make_shared<TextProcessor>(AudioTagMap::TITLE())),
		std::make_pair("TIT3"s, std::make_shared<TextProcessor>(AudioTagMap::SUBTITLE())),
		std::make_pair("TALB"s, std::make_shared<TextProcessor>(AudioTagMap::ALBUM())),
		std::make_pair("TOAL"s, std::make_shared<TextProcessor>(AudioTagMap::ORIGINALALBUM())),
		std::make_pair("TPE3"s, std::make_shared<TextProcessor>(AudioTagMap::CONDUCTOR())),
		std::make_pair("TPUB"s, std::make_shared<TextProcessor>(AudioTagMap::PUBLISHER())),

		std::make_pair("TSOA"s, std::make_shared<TextProcessor>(AudioTagMap::ALBUMSORT())),
		std::make_pair("TSOP"s, std::make_shared<TextProcessor>(AudioTagMap::ARTISTSORT())),
		std::make_pair("TSOT"s, std::make_shared<TextProcessor>(AudioTagMap::TITLESORT())),


		std::make_pair("TCOM"s, std::make_shared<MultistringTextProcessor>(AudioTagMap::COMPOSER())),
		std::make_pair("TPE1"s, std::make_shared<MultistringTextProcessor>(AudioTagMap::ARTIST())),
		std::make_pair("TPE2"s, std::make_shared<MultistringTextProcessor>(AudioTagMap::ALBUMARTIST())),
		std::make_pair("TOPE"s, std::make_shared<MultistringTextProcessor>(AudioTagMap::ORIGINALARTIST())),

		std::make_pair("TDRC"s, std::make_shared<FullDateProcessor>(AudioTagMap::DATE())),
		std::make_pair("TDOR"s, std::make_shared<FullDateProcessor>(AudioTagMap::ORIGINALDATE())),

		std::make_pair("WCOM"s, std::make_shared<URLProcessor>(AudioTagMap::WWWCOMMERCIAL())),
		std::make_pair("WCOP"s, std::make_shared<URLProcessor>(AudioTagMap::WWWCOPYRIGHT())),
		std::make_pair("WOAF"s, std::make_shared<URLProcessor>(AudioTagMap::WWWFILE())),
		std::make_pair("WOAR"s, std::make_shared<URLProcessor>(AudioTagMap::WWWARTIST())),
		std::make_pair("WOAS"s, std::make_shared<URLProcessor>(AudioTagMap::WWWFILESOURCE())),
		std::make_pair("WORS"s, std::make_shared<URLProcessor>(AudioTagMap::WWWRADIOPAGE())),
		std::make_pair("WPUB"s, std::make_shared<URLProcessor>(AudioTagMap::WWWPUBLISHER())),


		std::make_pair("TCON"s, std::make_shared<GenreProcessor>()),

		std::make_pair("TEXT"s, std::make_shared<MultistringTextProcessor>(AudioTagMap::LYRICIST())),

		std::make_pair("TBMP"s, std::make_shared<SingleNumberTextProcessor>(AudioTagMap::BPM())),

		std::make_pair("TRCK"s, std::make_shared<DoubleNumberTextProcessor>(AudioTagMap::TRACKNUMBER(), AudioTagMap::TOTALTRACKNUMBER())),
		std::make_pair("TPOS"s, std::make_shared<DoubleNumberTextProcessor>(AudioTagMap::DISCNUMBER(), AudioTagMap::TOTALDISCNUMBER())),

		std::make_pair("COMM"s, std::make_shared<CommentProcessor>()),

		std::make_pair("TXXX"s, std::make_shared<CustomTextProcessor>()),

		std::make_pair("APIC"s, std::make_shared<ImageProcessor>()),

		std::make_pair("USLT"s, std::make_shared<LyricsProcessor>())
	};

}