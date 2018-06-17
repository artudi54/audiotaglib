#include "ASFMetadataReader.hpp"
using namespace std::literals;

namespace tag::reader {
	AudioTagMap ASFMetadataReader::readTag(std::istream & readStream) const {
		AudioTagMap map;
		if (!readAndEquals(readStream, Headers::ASF_HEADER_GUID))
			return map;

		std::uint64_t headerSize = readLongLittleEndianSize(readStream);
		if (headerSize < 30)
			return map;

		unsigned objectsNumber = readLittleEndianSize(readStream);
		readStream.ignore();
		if (readStream.get() != 0x02)
			return map;

		processHeader(map, readStream, headerSize - 30, objectsNumber);
		return map;
	}




	void ASFMetadataReader::processHeader(AudioTagMap & map, std::istream & readStream, std::uint64_t size, unsigned objectsNumber) const {
		std::array<std::byte, 16> objectGuid;
		std::uint64_t objectSize;

		while (objectsNumber-- > 0 && size > 0) {
			objectGuid = readHeader<16>(readStream);
			objectSize = readLongLittleEndianSize(readStream);

			if (objectGuid == Headers::ASF_CONTENT_DESCRIPTION_GUID)
				processContentDescription(map, readStream, objectSize);
			else if (objectGuid == Headers::ASF_EXTENDED_CONTENT_DESCRIPTION_GUID)
				processExtendedContentDescription(map, readStream, objectSize);
			else
				readStream.seekg(objectSize - 24, std::ios::cur);
			size -= objectSize;
		}
	}





	void ASFMetadataReader::processContentDescription(AudioTagMap & map, std::istream & readStream, std::uint64_t size) const {
		std::uint16_t titleLength = readShortLittleEndianSize(readStream);
		std::uint16_t authorLength = readShortLittleEndianSize(readStream);
		std::uint16_t copyrightLength = readShortLittleEndianSize(readStream);
		std::uint16_t descriptionLength = readShortLittleEndianSize(readStream);
		std::uint16_t ratingLength = readShortLittleEndianSize(readStream);

		std::string title = readUtf16LE(readStream, titleLength);
		std::string artist = readUtf16LE(readStream, authorLength);
		std::string copyright = readUtf16LE(readStream, copyrightLength);
		std::string comment = readUtf16LE(readStream, descriptionLength);
		readStream.seekg(ratingLength, std::ios::cur);

		if (!title.empty())
			map.setTitle(title);
		if (!artist.empty())
			map.setArtist(artist);
		if (!copyright.empty())
			map.setCopyright(copyright);
		if (!comment.empty())
			map.setComment(comment);
	}




	void ASFMetadataReader::processExtendedContentDescription(AudioTagMap & map, std::istream & readStream, std::uint64_t size) const {
		std::uint16_t descriptorsCount = readShortLittleEndianSize(readStream);

		DataType valueType;
		std::uint16_t nameLength, valueLength;
		std::string name;

		while (descriptorsCount--) {
			nameLength = readShortLittleEndianSize(readStream);
			name = readUtf16LE(readStream, nameLength);
			valueType = static_cast<DataType>(readShortLittleEndianSize(readStream));
			valueLength = readShortLittleEndianSize(readStream);
			auto it = PROCESSORS.find(name);
			if (it != PROCESSORS.end())
				it->second->process(readStream, map, valueLength, valueType);
			else
				readStream.seekg(valueLength, std::ios::cur);
		}
	}



	ASFMetadataReader::DescriptorProcessor::DescriptorProcessor(const std::string & name)
		: name(name) {}






	ASFMetadataReader::StringDescriptorProcessor::StringDescriptorProcessor(const std::string & name)
		: DescriptorProcessor(name) {
	}

	void ASFMetadataReader::StringDescriptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		std::string text = readUtf16LE(readStream, size);
		if (!text.empty())
			map.setStringTag(name, text);
	}




	ASFMetadataReader::MultiStringDescriptorProcessor::MultiStringDescriptorProcessor(const std::string & name)
		: DescriptorProcessor(name) {}

	void ASFMetadataReader::MultiStringDescriptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		std::string text = readUtf16LE(readStream, size);
		if (!text.empty())
			map.setStringTag(name, processMultistring(text));
	}






	ASFMetadataReader::CustomStringDescriptorProcessor::CustomStringDescriptorProcessor()
		: DescriptorProcessor(std::string()) {}

	void ASFMetadataReader::CustomStringDescriptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::ByteArray)
			return;
		std::string name = readUtf16LE(readStream);
		boost::to_upper(name);
		std::string text = readUtf16LE(readStream);
		if (!name.empty())
			map.setStringTag(name, text);
	}
	







	ASFMetadataReader::GenreDescriptorProcessor::GenreDescriptorProcessor()
		: DescriptorProcessor(AudioTagMap::GENRE()) {
	}

	void ASFMetadataReader::GenreDescriptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		std::string text = readUtf16LE(readStream, size);
		if (!text.empty())
			map.setStringTag(name, processGenreString(text));
	}






	ASFMetadataReader::NumberDescriptorProcessor::NumberDescriptorProcessor(const std::string & name)
		: DescriptorProcessor(name) {
	}

	void ASFMetadataReader::NumberDescriptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType == DataType::String) {
			std::string text = readUtf16LE(readStream, size);

			if (!text.empty()) try {
				unsigned number = static_cast<unsigned>(std::stoul(text));
				map.setNumberTag(name, number);
			}
			catch (std::logic_error &) {}

		} else if (dataType == DataType::Dword)
			map.setNumberTag(name, readLittleEndianSize(readStream));
		else
			readStream.seekg(size, std::ios::cur);

	}









	ASFMetadataReader::DoubleNumberDescriptorProcessor::DoubleNumberDescriptorProcessor(const std::string &firstName, const std::string &secondName)
		: DescriptorProcessor(firstName), secondName(secondName) {
	}

	void ASFMetadataReader::DoubleNumberDescriptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType == DataType::String) {
			std::string all = readUtf16LE(readStream, size);
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
		} else if (dataType == DataType::Dword)
			map.setNumberTag(name, readLittleEndianSize(readStream));
		else
			readStream.seekg(size, std::ios::cur);

	}










	ASFMetadataReader::YearDescriptorProcessor::YearDescriptorProcessor(const std::string & name)
		: DescriptorProcessor(name) {
	}

	void ASFMetadataReader::YearDescriptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		std::string yearString = readUtf16LE(readStream);
		if (yearString.size() != 4)
			return;
		try {
			unsigned year = static_cast<unsigned>(std::stoul(yearString));
			SharedDateAudioTag tag = map.getDateTag(name);
			if (tag != nullptr)
				tag->getDate().setYearOnly(year);
			else
				map.setDateTag(name, type::Date(year));
		}
		catch (std::logic_error &) {}
	}








	ASFMetadataReader::DateDescirptorProcessor::DateDescirptorProcessor(const std::string & name)
		: DescriptorProcessor(name) {}

	void ASFMetadataReader::DateDescirptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::Qword) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		std::uint64_t fileTime = readLongLittleEndianSize(readStream);
		std::time_t unixTime = fileTime / 10000000ULL - 11644473600ULL;
		if (unixTime != 0) {
			std::tm &time = *std::gmtime(&unixTime);
			type::Date date(time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);
			if (!date.isNull())
				map.setDateTag(name, date);
		}
	}







	ASFMetadataReader::PictureDescriptorProcessor::PictureDescriptorProcessor()
		: DescriptorProcessor(std::string()) {
	}

	void ASFMetadataReader::PictureDescriptorProcessor::process(std::istream & readStream, AudioTagMap & map, std::uint16_t size, DataType dataType) const {
		if (dataType != DataType::ByteArray) {
			readStream.seekg(size, std::ios::cur);
			return;
		}

		ImageAudioTag::ImageType type = ImageAudioTag::ImageType(readStream.get());
		unsigned imageSize = readLittleEndianSize(readStream);
		std::string mimeTypeStr = readUtf16LE(readStream);
		std::string description = readUtf16BE(readStream);
		std::vector<std::byte> imageData(imageSize);
		type::Image::MimeType mimeType;

		readStream.read(reinterpret_cast<char*>(imageData.data()), imageSize);
		if (mimeTypeStr == "image/jpeg"s)
			mimeType = type::Image::MimeType::ImageJpeg;
		else if (mimeTypeStr == "image/png"s)
			mimeType = type::Image::MimeType::ImagePng;
		else
			return;

		map.setImageTag(type, type::Image(std::move(imageData), description, mimeType));
	}





	const std::unordered_map<std::string, ASFMetadataReader::SharedDescriptorProcessor> ASFMetadataReader::PROCESSORS = {
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

		std::make_pair("WM/BeatsPerMinute"s, std::make_shared<NumberDescriptorProcessor>(AudioTagMap::BPM())),
		std::make_pair("ID3/TBMP"s, std::make_shared<NumberDescriptorProcessor>(AudioTagMap::BPM())),

		std::make_pair("WM/Composer"s, std::make_shared<MultiStringDescriptorProcessor>(AudioTagMap::COMPOSER())),
		std::make_pair("ID3/TCOM"s, std::make_shared<MultiStringDescriptorProcessor>(AudioTagMap::COMPOSER())),

		std::make_pair("WM/Conductor"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::CONDUCTOR())),
		std::make_pair("ID3/TPE3"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::CONDUCTOR())),

		std::make_pair("WM/ContentGroupDescription"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::CONTENTGROUP())),
		std::make_pair("ID3/TIT1"s, std::make_shared<StringDescriptorProcessor>(AudioTagMap::CONTENTGROUP())),

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
}