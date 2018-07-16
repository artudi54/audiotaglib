#pragma once

#include "AudioTagReader.hpp"
#include <memory>
#include <unordered_map>
#include <regex>

namespace tag::reader {
	class RiffInfoReader : public AudioTagReader {
		virtual AudioTagMap readTag(std::istream &readStream) const;
	private:
		struct ChunkProcessor {
			ChunkProcessor(const std::string &name);
			virtual void process(std::istream &readStream, unsigned chunkSize, AudioTagMap &map) const = 0;
		protected:
			std::string name;
		};
		using SharedChunkProcessor = std::shared_ptr<ChunkProcessor>;

		struct StringChunkProcessor : public ChunkProcessor {
			StringChunkProcessor(const std::string &name);
			virtual void process(std::istream &readStream, unsigned chunkSize, AudioTagMap &map) const override;
		};

		struct MultiStringChunkProcessor : public ChunkProcessor {
			MultiStringChunkProcessor(const std::string &name);
			virtual void process(std::istream &readStream, unsigned chunkSize, AudioTagMap &map) const override;
		};

		struct NumberChunkProcessor : public ChunkProcessor {
			NumberChunkProcessor(const std::string &name);
			virtual void process(std::istream &readStream, unsigned chunkSize, AudioTagMap &map) const override;
		};

		struct DateChunkProcessor : public ChunkProcessor {
			DateChunkProcessor(const std::string &name);
			virtual void process(std::istream &readStream, unsigned chunkSize, AudioTagMap &map) const override;
		};


		static const std::unordered_map<std::string, SharedChunkProcessor> CHUNK_PROCESSORS;
	};
}