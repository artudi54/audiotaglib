#pragma once
#include "AudioTagReader.hpp"

namespace tag::reader {

	class ID3v1AudioTagReader : public AudioTagReader {
	public:
		virtual AudioTagMap readTag(std::istream &readStream) const override;
	};

}

