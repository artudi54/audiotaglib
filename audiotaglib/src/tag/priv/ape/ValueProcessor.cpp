#include "ValueProcessor.hpp"
#include <tag/priv/read_util.hpp>
#include <tag/priv/ape/icomp.hpp>
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
			map.setStringTag(name, processMultistring(text));
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









	const std::unordered_map<std::string, SharedValueProcessor, IHash, IEquals> MAPPED_PROCESSORS = {
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




	SharedValueProcessor getValueProcessor(const std::string & name) {
		auto it = MAPPED_PROCESSORS.find(name);
		if (it != MAPPED_PROCESSORS.end())
			return it->second;
		return nullptr;
	}

}