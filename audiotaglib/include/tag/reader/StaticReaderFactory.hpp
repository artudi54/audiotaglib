#pragma once
#include <tag/AudioTagFormat.hpp>
#include <tag/reader/AiffChunksReader.hpp>
#include <tag/reader/APETagReader.hpp>
#include <tag/reader/ID3v1TagReader.hpp>
#include <tag/reader/ID3v2TagReader.hpp>
#include <tag/reader/RiffInfoReader.hpp>
#include <tag/reader/ASFMetadataReader.hpp>
#include <tag/reader/VorbisCommentsReader.hpp>
#include <tag/reader/FLACPicturesReader.hpp>

namespace tag::reader {
	//todo: change the order / hide impl
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
		static const SharedAudioTagReader VORBIS_COMMENTS;
		static const SharedAudioTagReader FLAC_PICTURES;
	};
}