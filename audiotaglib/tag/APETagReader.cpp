#include "APETagReader.hpp"

namespace tag::reader {
	AudioTagMap APETagReader::readTag(std::istream & readStream) const {
		AudioTagMap map;

		if (!readAndEquals(readStream, Headers::APE))
			return map;
		unsigned version = readLittleEndianSize(readStream);
		unsigned size = readLittleEndianSize(readStream);
		unsigned itemCount = readLittleEndianSize(readStream);
		unsigned flags = readLittleEndianSize(readStream);
		readStream.seekg(8 - std::streamoff(size), std::ios::cur);

		while (itemCount-- > 0 && size > 0) {
			unsigned valueSize = readLittleEndianSize(readStream);
			unsigned itemFlags = readLittleEndianSize(readStream);
			std::string key = readUtf8(readStream);
			auto it = MAPPED_PROCESSORS.find(key);
			if (it != MAPPED_PROCESSORS.end())
				it->second->process(readStream, map, valueSize, fromFlags(itemFlags));
			else
				readStream.seekg(valueSize, std::ios::cur);
			size -= static_cast<unsigned>(8 + key.size() + 1 + valueSize);
		}

		return map;
	}

	APETagReader::ValueType APETagReader::fromFlags(unsigned flags) {
		static const unsigned RESERVED = 0b110;
		static const unsigned EXTERNAL = 0b100;
		static const unsigned BINARY = 0b010;
		if (flags & RESERVED)
			return ValueType::Reserved;
		if (flags & EXTERNAL)
			return ValueType::External;
		if (flags & BINARY)
			return ValueType::Binary;
		return ValueType::String;
	}





	APETagReader::ValueProcessor::ValueProcessor(const std::string & name)
		: name(name) {}







	APETagReader::StringProcessor::StringProcessor(const std::string & name)
		: ValueProcessor(name) {}


	void APETagReader::StringProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size, ValueType valueType) {
		if (valueType != ValueType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		std::string text = readUtf8(readStream, size);
		if (!text.empty())
			map.setStringTag(name, text);
	}






	APETagReader::MultiStringProcessor::MultiStringProcessor(const std::string & name)
		: ValueProcessor(name) {}

	void APETagReader::MultiStringProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size, ValueType valueType) {
		if (valueType != ValueType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}
		std::string text = readUtf8(readStream, size);
		if (!text.empty())
			map.setStringTag(name, processMultistring(text));
	}





	APETagReader::NumberProcessor::NumberProcessor(const std::string & name)
		: ValueProcessor(name) {}

	void APETagReader::NumberProcessor::process(std::istream & readStream, AudioTagMap & map, unsigned size, ValueType valueType) {
		if (valueType != ValueType::String) {
			readStream.seekg(size, std::ios::cur);
			return;
		}

		std::string numStr = readUtf8(readStream, size);
		try {
			unsigned number = static_cast<unsigned>(std::stoul(numStr));
			map.setNumberTag(name, number);
		} catch (std::logic_error &) {}
	}











	bool APETagReader::IEquals::operator()(const std::string & lhs, const std::string & rhs) const {
		return boost::iequals(lhs, rhs);
	}
	std::size_t APETagReader::IHash::operator()(const std::string & str) const {
		std::size_t seed = 0;
		std::locale locale;
		for (auto c : str)
			boost::hash_combine(seed, std::toupper(c, locale));
		return seed;
	}



	const std::unordered_map<std::string, APETagReader::SharedValueProcessor, APETagReader::IHash, APETagReader::IEquals> APETagReader::MAPPED_PROCESSORS = {
		std::make_pair("ALBUM"s, std::make_shared<StringProcessor>(AudioTagMap::ALBUM())),
		std::make_pair("ALBUM ARTIST"s, std::make_shared<StringProcessor>(AudioTagMap::ALBUMARTIST())),
		std::make_pair("ALBUMSORT"s, std::make_shared<StringProcessor>(AudioTagMap::ALBUMSORT())),
		std::make_pair("ARTIST"s, std::make_shared<MultiStringProcessor>(AudioTagMap::ARTIST())),
		std::make_pair("ARTISTSORT"s, std::make_shared<MultiStringProcessor>(AudioTagMap::ARTISTSORT())),
		std::make_pair("COMPOSER"s, std::make_shared<MultiStringProcessor>(AudioTagMap::COMPOSER())),
		std::make_pair("CONDUCTOR"s, std::make_shared<StringProcessor>(AudioTagMap::COMPOSER())),
		std::make_pair("DISCSUBTITLE"s, std::make_shared<StringProcessor>(AudioTagMap::SETSUBTITLE())),
		std::make_pair("SUBTITLE"s, std::make_shared<StringProcessor>(AudioTagMap::SUBTITLE())),
		std::make_pair("TITLE"s, std::make_shared<StringProcessor>(AudioTagMap::TITLE())),
		std::make_pair("TITLESORT"s, std::make_shared<StringProcessor>(AudioTagMap::TITLESORT())),
		std::make_pair("WRITER"s, std::make_shared<MultiStringProcessor>(AudioTagMap::LYRICIST())),
	};

}