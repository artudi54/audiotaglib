#pragma once
#include <audiotaglib/reader/AudioTagReader.hpp>
#include <audiotaglib/except/StreamParseException.hpp>

namespace audiotaglib::reader {
	class FLACPicturesReader : public AudioTagReader {
	public:
		virtual TagMap readTag(std::istream &readStream) const override;
	};
}