#include "StaticReaderFactory.hpp"

namespace audiotaglib::reader {
	SharedAudioTagReader StaticReaderFactory::getReader(TagContainerFormat tagFormat) {
		switch (tagFormat) {
		case TagContainerFormat::None:
			return nullptr;
		case TagContainerFormat::ID3v1:
			return ID3_V1;
		case TagContainerFormat::ID3v22:
			return ID3_V2;
		case TagContainerFormat::ID3v23:
			return ID3_V2;
		case TagContainerFormat::ID3v24:
			return ID3_V2;
		case TagContainerFormat::APEv1:
			return APE;
		case TagContainerFormat::APEv2:
			return APE;
        case TagContainerFormat::VorbisComments:
            return VORBIS_COMMENTS;
		case TagContainerFormat::FLACPictures:
			return FLAC_PICTURES;
		case TagContainerFormat::ASFMetadata:
			return ASF_METADATA;
		case TagContainerFormat::RiffInfo:
			return RIFF_INFO;
		case TagContainerFormat::AiffChunks:
			return AIFF;
		default:
			return nullptr;
		}
	}

    const SharedAudioTagReader StaticReaderFactory::AIFF = std::make_shared<AiffChunksReader>();
	const SharedAudioTagReader StaticReaderFactory::APE = std::make_shared<APETagReader>();
	const SharedAudioTagReader StaticReaderFactory::ID3_V1 = std::make_shared<ID3v1AudioTagReader>();
	const SharedAudioTagReader StaticReaderFactory::ID3_V2 = std::make_shared<ID3v2AudioTagReader>();
	const SharedAudioTagReader StaticReaderFactory::RIFF_INFO = std::make_shared<RiffInfoReader>();
	const SharedAudioTagReader StaticReaderFactory::ASF_METADATA = std::make_shared<ASFMetadataReader>();
	const SharedAudioTagReader StaticReaderFactory::VORBIS_COMMENTS = std::make_shared<VorbisCommentsReader>();
	const SharedAudioTagReader StaticReaderFactory::FLAC_PICTURES = std::make_shared<FLACPicturesReader>();
}