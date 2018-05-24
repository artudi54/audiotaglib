#pragma once

#include "AudioTagFormat.hpp"
#include "ID3v1AudioTagReader.hpp"
#include "ID3v2AudioTagReader.hpp"
#include "RiffInfoReader.hpp"

namespace tag::reader {

	class StaticReaderFactory {
	public:
		static SharedAudioTagReader getReader(AudioTagFormat tagFormat);
	private:
		static const SharedAudioTagReader ID3_V1;
		static const SharedAudioTagReader ID3_V2;
		static const SharedAudioTagReader RIFF_INFO;
	};
}