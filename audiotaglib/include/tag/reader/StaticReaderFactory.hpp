#pragma once

#include <tag/AudioTagFormat.hpp>
#include <tag/reader/AiffChunksReader.hpp>
#include <tag/reader/APETagReader.hpp>
#include <tag/reader/ID3v1AudioTagReader.hpp>
#include <tag/reader/ID3v2AudioTagReader.hpp>
#include <tag/reader/RiffInfoReader.hpp>
#include <tag/reader/ASFMetadataReader.hpp>

namespace tag::reader {
	//todo: change the order
	class StaticReaderFactory {
	public:
		static SharedAudioTagReader getReader(AudioTagFormat tagFormat);
	private:
		static const SharedAudioTagReader AIFF;
		static const SharedAudioTagReader APE;
		static const SharedAudioTagReader ID3_V1;
		static const SharedAudioTagReader ID3_V2;
		static const SharedAudioTagReader RIFF_INFO;
		static const SharedAudioTagReader ASF_METADATA;
	};
}