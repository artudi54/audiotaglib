#include <tag/reader/AudioTagReader.hpp>

namespace tag::reader {
	class AiffChunksReader : public AudioTagReader {
		virtual AudioTagMap readTag(std::istream &readStream) const;
	};
}