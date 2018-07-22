#include <tag/reader/AudioTagReader.hpp>
#include <tag/except/StreamParseException.hpp>

namespace tag::reader {
	class AiffChunksReader : public AudioTagReader {
		virtual AudioTagMap readTag(std::istream &readStream) const;
	};
}