#pragma once

#include "AudioTagFormat.hpp"
#include "ID3v1AudioTagReader.hpp"
#include "ID3v2AudioTagReader.hpp"

namespace tag::reader {

	class StaticReaderFactory {
	public:
		static SharedAudioTagReader getReader(AudioTagFormat tagFormat);
	private:
		static const SharedAudioTagReader ID3_V1;
		static const SharedAudioTagReader ID3_V2;
	};
}