#include "RiffInfoReader.hpp"
namespace tag::reader{

	AudioTagMap RiffInfoReader::readTag(std::istream & readStream) const {
		AudioTagMap map;

		if (!readAndEquals(readStream, Headers::LIST_CHUNK))
			return map;

		unsigned size = readLittleEndianSize(readStream);
		if (size <= 4)
			return map;

		if (!readAndEquals(readStream, Headers::INFO_SUBCHUNK))
			return map;

		size -= 4;

		while (size > 8) {
			std::string header = readUtf8(readStream, 4);
			unsigned chunkSize = readLittleEndianSize(readStream);

			auto it = CHUNK_PROCESSORS.find(header);
			if (it != CHUNK_PROCESSORS.end())
				it->second->process(readStream, chunkSize, map);
			else
				readStream.seekg(chunkSize, std::ios::cur);

			size -= chunkSize + 8;
			if (chunkSize % 2 == 1) {
				char next = readStream.get();
				if (readStream.get() == '\0')
					--size;
				else
					readStream.unget();
			}
		}
		return map;
	}








	RiffInfoReader::ChunkProcessor::ChunkProcessor(const std::string & name)
		: name(name) {}




	RiffInfoReader::StringChunkProcessor::StringChunkProcessor(const std::string & name)
		: ChunkProcessor(name) {}

	void RiffInfoReader::StringChunkProcessor::process(std::istream & readStream, unsigned chunkSize, AudioTagMap & map) const {
		std::string text = readUtf8(readStream, chunkSize);
		if (!text.empty())
			map.setStringTag(name, text);
	}






	RiffInfoReader::MultiStringChunkProcessor::MultiStringChunkProcessor(const std::string & name)
		: ChunkProcessor(name) {}

	void RiffInfoReader::MultiStringChunkProcessor::process(std::istream & readStream, unsigned chunkSize, AudioTagMap & map) const {
		static const std::regex PATTERN(R"(\s*[;,/\\0\\]\s*)"s);

		std::string text = readUtf8(readStream, chunkSize);
		if (!text.empty()) {
			std::string newText;
			newText.reserve(text.size());
			std::regex_replace(std::back_inserter(newText), text.begin(), text.end(), PATTERN, "; "s);
			map.setStringTag(name, newText);
		}
	}

	RiffInfoReader::NumberChunkProcessor::NumberChunkProcessor(const std::string & name)
		: ChunkProcessor(name) {}

	void RiffInfoReader::NumberChunkProcessor::process(std::istream & readStream, unsigned chunkSize, AudioTagMap & map) const {
		std::string text = readUtf8(readStream, chunkSize);
		try {
			unsigned number = static_cast<unsigned>(std::stoul(text));
			map.setNumberTag(name, number);
		}
		catch (std::logic_error &) {}
	}






	RiffInfoReader::DateChunkProcessor::DateChunkProcessor(const std::string & name)
		: ChunkProcessor(name) {}

	void RiffInfoReader::DateChunkProcessor::process(std::istream & readStream, unsigned chunkSize, AudioTagMap & map) const {
		std::string text = readUtf8(readStream, chunkSize);
		type::Date date = type::Date::parseString(text);

		if (!date.isNull())
			map.setDateTag(name, date);
	}








	const std::unordered_map<std::string, RiffInfoReader::SharedChunkProcessor> RiffInfoReader::CHUNK_PROCESSORS = {
		std::make_pair("IPRD"s, std::make_shared<StringChunkProcessor>(AudioTagMap::ALBUM)),
		std::make_pair("INAM"s, std::make_shared<StringChunkProcessor>(AudioTagMap::TITLE)),
		std::make_pair("ICMT"s, std::make_shared<StringChunkProcessor>(AudioTagMap::COMMENT)),
		std::make_pair("CMNT"s, std::make_shared<StringChunkProcessor>(AudioTagMap::COMMENT)),
		std::make_pair("COMM"s, std::make_shared<StringChunkProcessor>(AudioTagMap::COMMENT)),

		std::make_pair("IART"s, std::make_shared<MultiStringChunkProcessor>(AudioTagMap::ARTIST)),
		std::make_pair("IWRI"s, std::make_shared<MultiStringChunkProcessor>(AudioTagMap::LYRICIST)),
		std::make_pair("IMUS"s, std::make_shared<MultiStringChunkProcessor>(AudioTagMap::COMPOSER)),
		std::make_pair("IPRO"s, std::make_shared<MultiStringChunkProcessor>(AudioTagMap::PRODUCER)),
		std::make_pair("IGNR"s, std::make_shared<MultiStringChunkProcessor>(AudioTagMap::GENRE)),
		std::make_pair("GENR"s, std::make_shared<MultiStringChunkProcessor>(AudioTagMap::GENRE)),

		std::make_pair("IPRT"s, std::make_shared<NumberChunkProcessor>(AudioTagMap::TRACKNUMBER)),
		std::make_pair("ITRK"s, std::make_shared<NumberChunkProcessor>(AudioTagMap::TRACKNUMBER)),
		std::make_pair("IFRM"s, std::make_shared<NumberChunkProcessor>(AudioTagMap::TOTALTRACKNUMBER)),

		std::make_pair("ICRD"s, std::make_shared<DateChunkProcessor>(AudioTagMap::DATE))
	};

}