#include "StaticReaderFactory.hpp"

namespace tag::reader {
	SharedAudioTagReader StaticReaderFactory::getReader(AudioTagFormat tagFormat) {
		switch (tagFormat) {
		case tag::AudioTagFormat::None:
			return nullptr;
		case tag::AudioTagFormat::ID3v1:
			return ID3_V1;
		case tag::AudioTagFormat::ID3v22:
			return ID3_V2;
		case tag::AudioTagFormat::ID3v23:
			return ID3_V2;
		case tag::AudioTagFormat::ID3v24:
			return ID3_V2;
		case tag::AudioTagFormat::WaveInfo:
			return nullptr;
		case tag::AudioTagFormat::APEv1:
			return nullptr;
		case tag::AudioTagFormat::APEv2:
			return nullptr;
		default:
			return nullptr;
		}
	}

	const SharedAudioTagReader StaticReaderFactory::ID3_V1 = std::make_shared<ID3v1AudioTagReader>();
	const SharedAudioTagReader StaticReaderFactory::ID3_V2 = std::make_shared<ID3v2AudioTagReader>();
}