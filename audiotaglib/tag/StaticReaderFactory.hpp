#pragma once

#include "AudioTagFormat.hpp"
#include "APETagReader.hpp"
#include "ID3v1AudioTagReader.hpp"
#include "ID3v2AudioTagReader.hpp"
#include "RiffInfoReader.hpp"
#include "ASFMetadataReader.hpp"

namespace tag::reader {
	//todo: change the order
	class StaticReaderFactory {
	public:
		static SharedAudioTagReader getReader(AudioTagFormat tagFormat);
	private:
		static const SharedAudioTagReader APE;
		static const SharedAudioTagReader ID3_V1;
		static const SharedAudioTagReader ID3_V2;
		static const SharedAudioTagReader RIFF_INFO;
		static const SharedAudioTagReader ASF_METADATA;
	};
}