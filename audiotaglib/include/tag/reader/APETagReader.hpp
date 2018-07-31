#pragma once
#include <tag/reader/AudioTagReader.hpp>
#include <tag/except/StreamParseException.hpp>

namespace tag::reader {
	class APETagReader : public AudioTagReader {
	public:
		virtual AudioTagMap readTag(std::istream &readStream) const override;
	private:
	};
}