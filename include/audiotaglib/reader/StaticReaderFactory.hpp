#pragma once
#include <audiotaglib/TagContainerFormat.hpp>
#include <audiotaglib/reader/AiffChunksReader.hpp>
#include <audiotaglib/reader/APETagReader.hpp>
#include <audiotaglib/reader/ID3v1TagReader.hpp>
#include <audiotaglib/reader/ID3v2TagReader.hpp>
#include <audiotaglib/reader/RiffInfoReader.hpp>
#include <audiotaglib/reader/ASFMetadataReader.hpp>
#include <audiotaglib/reader/VorbisCommentsReader.hpp>
#include <audiotaglib/reader/FlacPicturesReader.hpp>
//todo: optimize includes
namespace audiotaglib::reader {
	//todo: change the order / hide impl
	class StaticReaderFactory {
	public:
		static SharedAudioTagReader getReader(TagContainerFormat tagFormat);
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