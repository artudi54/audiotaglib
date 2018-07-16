#include <tag/reader/AudioTagReader.hpp>
#include <tag/except/FileParseException.hpp>

namespace tag::reader {
	class AiffChunksReader : public AudioTagReader {
		virtual AudioTagMap readTag(std::istream &readStream) const;
	};
}