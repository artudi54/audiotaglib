#include <tag/reader/StaticReaderFactory.hpp>

namespace tag::reader {
	SharedAudioTagReader StaticReaderFactory::getReader(AudioTagFormat tagFormat) {
		switch (tagFormat) {
		case AudioTagFormat::None:
			return nullptr;
		case AudioTagFormat::ID3v1:
			return ID3_V1;
		case AudioTagFormat::ID3v22:
			return ID3_V2;
		case AudioTagFormat::ID3v23:
			return ID3_V2;
		case AudioTagFormat::ID3v24:
			return ID3_V2;
		case AudioTagFormat::APEv1:
			return APE;
		case AudioTagFormat::APEv2:
			return APE;
		case AudioTagFormat::ASFMetadata:
			return ASF_METADATA;
		case AudioTagFormat::RiffInfo:
			return RIFF_INFO;
		case AudioTagFormat::AiffChunks:
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
}