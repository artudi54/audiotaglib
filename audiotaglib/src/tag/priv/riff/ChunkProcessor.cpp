#include "ChunkProcessor.hpp"
#include <tag/priv/read_util.hpp>

namespace tag::priv::riff {
	ChunkProcessor::ChunkProcessor(const std::string & name)
		: name(name) {
	}



	StringChunkProcessor::StringChunkProcessor(const std::string & name)
		: ChunkProcessor(name) {}

	void StringChunkProcessor::process(std::istream & readStream, std::uint32_t chunkSize, AudioTagMap & map) const {
		std::string text = readUtf8(readStream, chunkSize);
		if (!text.empty())
			map.setStringTag(name, text);
	}



	MultiStringChunkProcessor::MultiStringChunkProcessor(const std::string & name)
		: ChunkProcessor(name) {}

	void MultiStringChunkProcessor::process(std::istream & readStream, std::uint32_t chunkSize, AudioTagMap & map) const {
		std::string text = processMultiString(readUtf8(readStream, chunkSize));
		if (!text.empty())
			map.setStringTag(name, text);
	}



	NumberChunkProcessor::NumberChunkProcessor(const std::string & name)
		: ChunkProcessor(name) {}

	void NumberChunkProcessor::process(std::istream & readStream, std::uint32_t chunkSize, AudioTagMap & map) const {
		std::string text = readUtf8(readStream, chunkSize);
		try {
			std::uint32_t number = static_cast<std::uint32_t>(std::stoul(text));
			map.setNumberTag(name, number);
		}
		catch (std::logic_error &) {}
	}



	DateChunkProcessor::DateChunkProcessor(const std::string & name)
		: ChunkProcessor(name) {}

	void DateChunkProcessor::process(std::istream & readStream, std::uint32_t chunkSize, AudioTagMap & map) const {
		std::string text = readUtf8(readStream, chunkSize);
		types::Date date = types::Date::parseString(text);

		if (!date.isEmpty())
			map.setDateTag(name, date);
	}



	const std::unordered_map<std::string, SharedChunkProcessor> CHUNK_PROCESSORS = {
		{"IPRD"s, std::make_shared<StringChunkProcessor>(AudioTagMap::ALBUM())},
		{"INAM"s, std::make_shared<StringChunkProcessor>(AudioTagMap::TITLE())},
		{"ICMT"s, std::make_shared<StringChunkProcessor>(AudioTagMap::COMMENT())},
		{"CMNT"s, std::make_shared<StringChunkProcessor>(AudioTagMap::COMMENT())},
		{"COMM"s, std::make_shared<StringChunkProcessor>(AudioTagMap::COMMENT())},
		{"ICOP"s, std::make_shared<StringChunkProcessor>(AudioTagMap::COPYRIGHT())},
		{"CODE"s, std::make_shared<StringChunkProcessor>(AudioTagMap::ENCODEDBY())},
		{"ITCH"s, std::make_shared<StringChunkProcessor>(AudioTagMap::ENCODEDBY())},

		{"IART"s, std::make_shared<MultiStringChunkProcessor>(AudioTagMap::ARTIST())},
		{"IWRI"s, std::make_shared<MultiStringChunkProcessor>(AudioTagMap::LYRICIST())},
		{"IMUS"s, std::make_shared<MultiStringChunkProcessor>(AudioTagMap::COMPOSER())},
		{"IPRO"s, std::make_shared<MultiStringChunkProcessor>(AudioTagMap::PRODUCER())},
		{"IGNR"s, std::make_shared<MultiStringChunkProcessor>(AudioTagMap::GENRE())},
		{"GENR"s, std::make_shared<MultiStringChunkProcessor>(AudioTagMap::GENRE())},

		{"IPRT"s, std::make_shared<NumberChunkProcessor>(AudioTagMap::TRACKNUMBER())},
		{"ITRK"s, std::make_shared<NumberChunkProcessor>(AudioTagMap::TRACKNUMBER())},
		{"IFRM"s, std::make_shared<NumberChunkProcessor>(AudioTagMap::TOTALTRACKNUMBER())},

		{"ICRD"s, std::make_shared<DateChunkProcessor>(AudioTagMap::DATE())}
	};


    SharedChunkProcessor getProcessor(const std::string & chunkName) {
		auto it = CHUNK_PROCESSORS.find(chunkName);
		if (it != CHUNK_PROCESSORS.end())
			return it->second;
		return nullptr;
	}
}