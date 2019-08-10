#pragma once
#include <tag/reader/AudioTagReader.hpp>
#include <tag/except/StreamParseException.hpp>

namespace tag::reader {
	class ID3v1AudioTagReader : public AudioTagReader {
	public:
		virtual TagMap readTag(std::istream &readStream) const override;
	};
}

