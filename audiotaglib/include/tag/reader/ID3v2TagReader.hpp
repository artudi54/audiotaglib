#pragma once
#include <tag/reader/AudioTagReader.hpp>

//todo: add mapping for custom strings
namespace tag::reader {
	class ID3v2AudioTagReader : public AudioTagReader {
	public:
		virtual AudioTagMap readTag(std::istream &readStream) const override;
	private:
		};
}