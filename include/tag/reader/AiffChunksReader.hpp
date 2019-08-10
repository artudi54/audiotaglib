#include <tag/reader/AudioTagReader.hpp>
#include <tag/except/StreamParseException.hpp>

namespace tag::reader {
	class AiffChunksReader : public AudioTagReader {
		virtual TagMap readTag(std::istream &readStream) const;
	};
}