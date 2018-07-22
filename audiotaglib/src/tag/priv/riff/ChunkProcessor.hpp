#pragma once
#include <string>
#include <string_view>
#include <istream>
#include <tag/AudioTagMap.hpp>

namespace tag::priv::riff {
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

	SharedChunkProcessor getProcessor(const std::string &chunkName);
}