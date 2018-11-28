#include "ChunkProcessor.hpp"
#include <tag/priv/read_util.hpp>

namespace tag::priv::riff {
	ChunkProcessor::ChunkProcessor(const std::string & name)
		: name(name) {
	}



	StringChunkProcessor::StringChunkProcessor(const std::string & name)
		: ChunkProcessor(name) {}

	void StringChunkProcessor::process(std::istream & readStream, unsigned chunkSize, AudioTagMap & map) const {
		std::string text = readUtf8(readStream, chunkSize);
		if (!text.empty())
			map.setStringTag(name, text);
	}



	MultiStringChunkProcessor::MultiStringChunkProcessor(const std::string & name)
		: ChunkProcessor(name) {}

	void MultiStringChunkProcessor::process(std::istream & readStream, unsigned chunkSize, AudioTagMap & map) const {
		std::string text = processMultiString(readUtf8(readStream, chunkSize));
		if (!text.empty())
			map.setStringTag(name, text);
	}



	NumberChunkProcessor::NumberChunkProcessor(const std::string & name)
		: ChunkProcessor(name) {}

	void NumberChunkProcessor::process(std::istream & readStream, unsigned chunkSize, AudioTagMap & map) const {
		std::string text = readUtf8(readStream, chunkSize);
		try {
			unsigned number = static_cast<unsigned>(std::stoul(text));
			map.setNumberTag(name, number);
		}
		catch (std::logic_error &) {}
	}



	DateChunkProcessor::DateChunkProcessor(const std::string & name)
		: ChunkProcessor(name) {}

	void DateChunkProcessor::process(std::istream & readStream, unsigned chunkSize, AudioTagMap & map) const {
		std::string text = readUtf8(readStream, chunkSize);
		types::Date date = types::Date::parseString(text);

		if (!date.isEmpty())
			map.setDateTag(name, date);
	}



    const std::unordered_map<std::string, SharedChunkProcessor> CHUNK_PROCESSORS = {
            std::make_pair("IPRD"s, std::make_shared<StringChunkProcessor>(AudioTagMap::ALBUM())),
            std::make_pair("INAM"s, std::make_shared<StringChunkProcessor>(AudioTagMap::TITLE())),
            std::make_pair("ICMT"s, std::make_shared<StringChunkProcessor>(AudioTagMap::COMMENT())),
            std::make_pair("CMNT"s, std::make_shared<StringChunkProcessor>(AudioTagMap::COMMENT())),
            std::make_pair("COMM"s, std::make_shared<StringChunkProcessor>(AudioTagMap::COMMENT())),
            std::make_pair("ICOP"s, std::make_shared<StringChunkProcessor>(AudioTagMap::COPYRIGHT())),
            std::make_pair("CODE"s, std::make_shared<StringChunkProcessor>(AudioTagMap::ENCODEDBY())),
            std::make_pair("ITCH"s, std::make_shared<StringChunkProcessor>(AudioTagMap::ENCODEDBY())),

            std::make_pair("IART"s, std::make_shared<MultiStringChunkProcessor>(AudioTagMap::ARTIST())),
            std::make_pair("IWRI"s, std::make_shared<MultiStringChunkProcessor>(AudioTagMap::LYRICIST())),
            std::make_pair("IMUS"s, std::make_shared<MultiStringChunkProcessor>(AudioTagMap::COMPOSER())),
            std::make_pair("IPRO"s, std::make_shared<MultiStringChunkProcessor>(AudioTagMap::PRODUCER())),
            std::make_pair("IGNR"s, std::make_shared<MultiStringChunkProcessor>(AudioTagMap::GENRE())),
            std::make_pair("GENR"s, std::make_shared<MultiStringChunkProcessor>(AudioTagMap::GENRE())),

            std::make_pair("IPRT"s, std::make_shared<NumberChunkProcessor>(AudioTagMap::TRACKNUMBER())),
            std::make_pair("ITRK"s, std::make_shared<NumberChunkProcessor>(AudioTagMap::TRACKNUMBER())),
            std::make_pair("IFRM"s, std::make_shared<NumberChunkProcessor>(AudioTagMap::TOTALTRACKNUMBER())),

            std::make_pair("ICRD"s, std::make_shared<DateChunkProcessor>(AudioTagMap::DATE()))
    };


    SharedChunkProcessor getProcessor(const std::string & chunkName) {
		auto it = CHUNK_PROCESSORS.find(chunkName);
		if (it != CHUNK_PROCESSORS.end())
			return it->second;
		return nullptr;
	}
}