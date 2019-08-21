#pragma once
#include <audiotaglib/reader/AudioTagReader.hpp>

//todo: add mapping for custom strings
namespace audiotaglib::reader {
	class ID3v2AudioTagReader : public AudioTagReader {
	public:
		virtual TagMap readTag(std::istream &readStream) const override;
	private:
	};
}