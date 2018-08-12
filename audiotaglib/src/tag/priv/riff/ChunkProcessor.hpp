#pragma once
#include <string>
#include <string_view>
#include <istream>
#include <tag/AudioTagMap.hpp>

namespace tag::priv::riff {
	struct ChunkProcessor {
        /* @brief constructs object
         *
         * */
		explicit ChunkProcessor(const std::string &name);
		virtual void process(std::istream &readStream, unsigned chunkSize, AudioTagMap &map) const = 0;
	protected:
		std::string name;
	};
	using SharedChunkProcessor = std::shared_ptr<ChunkProcessor>;

	struct StringChunkProcessor : public ChunkProcessor {
        explicit StringChunkProcessor(const std::string &name);
		virtual void process(std::istream &readStream, unsigned chunkSize, AudioTagMap &map) const override;
	};

	struct MultiStringChunkProcessor : public ChunkProcessor {
        explicit MultiStringChunkProcessor(const std::string &name);
		virtual void process(std::istream &readStream, unsigned chunkSize, AudioTagMap &map) const override;
	};

	struct NumberChunkProcessor : public ChunkProcessor {
        explicit NumberChunkProcessor(const std::string &name);
		virtual void process(std::istream &readStream, unsigned chunkSize, AudioTagMap &map) const override;
	};

	struct DateChunkProcessor : public ChunkProcessor {
        explicit DateChunkProcessor(const std::string &name);
		virtual void process(std::istream &readStream, unsigned chunkSize, AudioTagMap &map) const override;
	};

	SharedChunkProcessor getProcessor(const std::string &chunkName);
}