#include <audiotaglib/reader/AudioTagReader.hpp>
#include <audiotaglib/except/StreamParseException.hpp>

namespace audiotaglib::reader {
	class AiffChunksReader : public AudioTagReader {
		virtual TagMap readTag(std::istream &readStream) const;
	};
}