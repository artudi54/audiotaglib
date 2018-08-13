#include "StaticScannerFactory.hpp"
namespace fs = std::filesystem;
using namespace std::literals;

namespace tag::scanner::priv {
	static const SharedTagScannerVector SCANNERS_NONE;
	static const SharedTagScannerVector SCANNERS_ALL = {
		std::make_shared<RiffInfoScanner>(),
		std::make_shared<AiffChunksScanner>(),
		std::make_shared<ASFMetadataScanner>(),
		std::make_shared<FLACScanner>(),
		std::make_shared<ID3TagScanner>(),
		std::make_shared<APETagScanner>()
	};
	static const SharedTagScannerVector AIFF = {
		std::make_shared<AiffChunksScanner>()
	};
	static const SharedTagScannerVector AIFF_ALL = {
		std::make_shared<AiffChunksScanner>(),
		std::make_shared<RiffInfoScanner>(),
		std::make_shared<ASFMetadataScanner>(),
		std::make_shared<FLACScanner>(),
		std::make_shared<ID3TagScanner>(),
		std::make_shared<APETagScanner>()
	};
	static const SharedTagScannerVector APE = {
		std::make_shared<APETagScanner>(),
		std::make_shared<ID3TagScanner>()
	};
	static const SharedTagScannerVector APE_ALL = {
		std::make_shared<APETagScanner>(),
		std::make_shared<ID3TagScanner>(),
		std::make_shared<ASFMetadataScanner>(),
		std::make_shared<FLACScanner>(),
		std::make_shared<RiffInfoScanner>(),
		std::make_shared<AiffChunksScanner>()

	};
	static const SharedTagScannerVector FLAC = {
		std::make_shared<FLACScanner>()
	};
	static const SharedTagScannerVector FLAC_ALL = {
		std::make_shared<FLACScanner>(),
		std::make_shared<ASFMetadataScanner>(),
		std::make_shared<RiffInfoScanner>(),
		std::make_shared<AiffChunksScanner>(),
		std::make_shared<ID3TagScanner>(),
		std::make_shared<APETagScanner>()
	};
	static const SharedTagScannerVector ID3APE = {
		std::make_shared<ID3TagScanner>(),
		std::make_shared<APETagScanner>(),

	};
	static const SharedTagScannerVector ID3APE_ALL = {
		std::make_shared<ID3TagScanner>(),
		std::make_shared<APETagScanner>(),
		std::make_shared<ASFMetadataScanner>(),
		std::make_shared<RiffInfoScanner>(),
		std::make_shared<AiffChunksScanner>(),
		std::make_shared<FLACScanner>(),

	};
	static const SharedTagScannerVector WAVE = {
		std::make_shared<RiffInfoScanner>()
	};
	static const SharedTagScannerVector WAVE_ALL = {
		std::make_shared<RiffInfoScanner>(),
		std::make_shared<AiffChunksScanner>(),
		std::make_shared<ASFMetadataScanner>(),
		std::make_shared<FLACScanner>(),
		std::make_shared<ID3TagScanner>(),
		std::make_shared<APETagScanner>()
	};
	static const SharedTagScannerVector WMA = {
		std::make_shared<ASFMetadataScanner>()
	};
	static const SharedTagScannerVector WMA_ALL = {
		std::make_shared<ASFMetadataScanner>(),
		std::make_shared<RiffInfoScanner>(),
		std::make_shared<AiffChunksScanner>(),
		std::make_shared<FLACScanner>(),
		std::make_shared<ID3TagScanner>(),
		std::make_shared<APETagScanner>()
	};
}


namespace tag::scanner {
	const SharedTagScannerVector & StaticScannerFactory::getScanners(AudioContainerFormat format, bool allPossible) {
		if (allPossible) {
			auto it = SCANNERS_ALL_MAP.find(format);
			if (it != SCANNERS_ALL_MAP.end())
				return *it->second;
			return priv::SCANNERS_ALL;
		} else {
			auto it = SCANNERS_MAP.find(format);
			if (it != SCANNERS_MAP.end())
				return *it->second;
			return priv::SCANNERS_NONE;
		}
	}

	const SharedTagScannerVector& StaticScannerFactory::getAllScanners() {
		return priv::SCANNERS_ALL;
	}


	const std::unordered_map<AudioContainerFormat, const SharedTagScannerVector*> StaticScannerFactory::SCANNERS_MAP = {
		std::make_pair(AudioContainerFormat::Unspecified,					&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::Invalid,						&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::ACT,							&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::AdaptiveMultiRate,				&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::AdaptiveMultiRateWideband,		&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::AdvancedAudioCodec,			&priv::APE),
		std::make_pair(AudioContainerFormat::Au,							&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::AudibleAudiobook,				&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::AudibleAudiobookEnhanced,		&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::AudioInterchangeFileFormat,	&priv::AIFF),
		std::make_pair(AudioContainerFormat::Dct,							&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::DigitalSpeechStandard,			&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::FreeLosslessAudioCodec,		&priv::FLAC),
		std::make_pair(AudioContainerFormat::GSM,							&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::IKlaxMedia,					&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::Matroska,							&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::MonkeysAudio,						&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::Mousepack,						&priv::APE),
		std::make_pair(AudioContainerFormat::Mpeg4,								&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::MpegLayer1,					&priv::ID3APE),
		std::make_pair(AudioContainerFormat::MpegLayer2,					&priv::ID3APE),
		std::make_pair(AudioContainerFormat::MpegLayer3,					&priv::ID3APE),
		std::make_pair(AudioContainerFormat::NESSoundFormat,				&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::Ogg,								&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::OptimFROG,							&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::Opus,								&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::RealAudio,						&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::SonyVoiceFormat,				&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::Speex,								&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::ThirdGenerationPartnership,	&priv::SCANNERS_NONE),
		std::make_pair(AudioContainerFormat::TomsAudioKompressor,			&priv::APE),
		std::make_pair(AudioContainerFormat::TTA,							&priv::ID3APE),
		std::make_pair(AudioContainerFormat::WaveAudio,						&priv::WAVE),
		std::make_pair(AudioContainerFormat::WavPack,						&priv::APE),
		std::make_pair(AudioContainerFormat::WindowsMediaAudio,				&priv::WMA)
	};
	
	
	const std::unordered_map<AudioContainerFormat, const SharedTagScannerVector*> StaticScannerFactory::SCANNERS_ALL_MAP = {
		std::make_pair(AudioContainerFormat::Unspecified,					&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::Invalid,						&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::ACT,							&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::AdaptiveMultiRate,				&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::AdaptiveMultiRateWideband,		&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::AdvancedAudioCodec,			&priv::APE_ALL),
		std::make_pair(AudioContainerFormat::Au,							&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::AudibleAudiobook,				&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::AudibleAudiobookEnhanced,		&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::AudioInterchangeFileFormat,	&priv::AIFF_ALL),
		std::make_pair(AudioContainerFormat::Dct,							&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::DigitalSpeechStandard,			&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::FreeLosslessAudioCodec,		&priv::FLAC_ALL),
		std::make_pair(AudioContainerFormat::GSM,							&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::IKlaxMedia,					&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::Matroska,							&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::MonkeysAudio,						&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::Mousepack,						&priv::APE_ALL),
		std::make_pair(AudioContainerFormat::Mpeg4,								&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::MpegLayer1,					&priv::ID3APE_ALL),
		std::make_pair(AudioContainerFormat::MpegLayer2,					&priv::ID3APE_ALL),
		std::make_pair(AudioContainerFormat::MpegLayer3,					&priv::ID3APE_ALL),
		std::make_pair(AudioContainerFormat::NESSoundFormat,				&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::Ogg,								&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::OptimFROG,							&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::Opus,								&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::RealAudio,						&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::SonyVoiceFormat,				&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::Speex,								&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::ThirdGenerationPartnership,	&priv::SCANNERS_ALL),
		std::make_pair(AudioContainerFormat::TomsAudioKompressor,			&priv::APE),
		std::make_pair(AudioContainerFormat::TTA,							&priv::ID3APE_ALL),
		std::make_pair(AudioContainerFormat::WaveAudio,						&priv::WAVE_ALL),
		std::make_pair(AudioContainerFormat::WavPack,						&priv::APE_ALL),
		std::make_pair(AudioContainerFormat::WindowsMediaAudio,				&priv::WMA_ALL)
	};
}
