#include "TagScannerProvider.hpp"
#include <unordered_map>
using namespace std::literals;


namespace tag::scanner {
    template <class... Args>
    static SharedTagScannerVector makeVector(Args&&... args) {
        SharedTagScannerVector result;
        result.reserve(sizeof...(Args));
        (result.push_back(std::forward<Args>(args)), ...);
        return result;
    }

    static const SharedTagScannerVector SCANNERS_NONE;
    static const SharedTagScannerVector SCANNERS_ALL = makeVector(
            std::make_unique<RiffInfoScanner>(),
            std::make_unique<AiffChunksScanner>(),
            std::make_unique<ASFMetadataScanner>(),
            std::make_unique<FLACScanner>(),
            std::make_unique<ID3TagScanner>(),
            std::make_unique<APETagScanner>(),
            std::make_unique<OggScanner>()
    );
    static const SharedTagScannerVector AIFF = makeVector(
            std::make_unique<AiffChunksScanner>()
    );
    static const SharedTagScannerVector AIFF_ALL = makeVector(
            std::make_unique<AiffChunksScanner>(),
            std::make_unique<RiffInfoScanner>(),
            std::make_unique<ASFMetadataScanner>(),
            std::make_unique<FLACScanner>(),
            std::make_unique<ID3TagScanner>(),
            std::make_unique<APETagScanner>(),
            std::make_unique<OggScanner>()
    );
    static const SharedTagScannerVector APE = makeVector(
            std::make_unique<APETagScanner>(),
            std::make_unique<ID3TagScanner>()
    );
    static const SharedTagScannerVector APE_ALL = makeVector(
            std::make_unique<APETagScanner>(),
            std::make_unique<ID3TagScanner>(),
            std::make_unique<ASFMetadataScanner>(),
            std::make_unique<FLACScanner>(),
            std::make_unique<RiffInfoScanner>(),
            std::make_unique<AiffChunksScanner>(),
            std::make_unique<OggScanner>()
    );
    static const SharedTagScannerVector FLAC = makeVector(
            std::make_unique<FLACScanner>()
    );
    static const SharedTagScannerVector FLAC_ALL = makeVector(
            std::make_unique<FLACScanner>(),
            std::make_unique<ASFMetadataScanner>(),
            std::make_unique<RiffInfoScanner>(),
            std::make_unique<AiffChunksScanner>(),
            std::make_unique<ID3TagScanner>(),
            std::make_unique<APETagScanner>(),
            std::make_unique<OggScanner>()
    );
    static const SharedTagScannerVector ID3APE = makeVector(
            std::make_unique<ID3TagScanner>(),
            std::make_unique<APETagScanner>()
    );
    static const SharedTagScannerVector ID3APE_ALL = makeVector(
            std::make_unique<ID3TagScanner>(),
            std::make_unique<APETagScanner>(),
            std::make_unique<ASFMetadataScanner>(),
            std::make_unique<RiffInfoScanner>(),
            std::make_unique<AiffChunksScanner>(),
            std::make_unique<FLACScanner>(),
            std::make_unique<OggScanner>()
    );
    static const SharedTagScannerVector OGG = makeVector(
            std::make_unique<OggScanner>()
    );
    static const SharedTagScannerVector OGG_ALL = makeVector(
            std::make_unique<OggScanner>(),
            std::make_unique<ASFMetadataScanner>(),
            std::make_unique<FLACScanner>(),
            std::make_unique<RiffInfoScanner>(),
            std::make_unique<AiffChunksScanner>(),
            std::make_unique<ID3TagScanner>(),
            std::make_unique<APETagScanner>(),
            std::make_unique<OggScanner>()
    );
    static const SharedTagScannerVector WAVE = makeVector(
            std::make_unique<RiffInfoScanner>()
    );
    static const SharedTagScannerVector WAVE_ALL = makeVector(
            std::make_unique<RiffInfoScanner>(),
            std::make_unique<AiffChunksScanner>(),
            std::make_unique<ASFMetadataScanner>(),
            std::make_unique<FLACScanner>(),
            std::make_unique<ID3TagScanner>(),
            std::make_unique<APETagScanner>(),
            std::make_unique<OggScanner>()
    );
    static const SharedTagScannerVector WMA = makeVector(
            std::make_unique<ASFMetadataScanner>()
    );
    static const SharedTagScannerVector WMA_ALL = makeVector(
            std::make_unique<ASFMetadataScanner>(),
            std::make_unique<RiffInfoScanner>(),
            std::make_unique<AiffChunksScanner>(),
            std::make_unique<FLACScanner>(),
            std::make_unique<ID3TagScanner>(),
            std::make_unique<APETagScanner>(),
            std::make_unique<OggScanner>()
    );



    static const std::unordered_map<AudioContainerFormat, const SharedTagScannerVector*> SCANNERS_MAP = {
            std::make_pair(AudioContainerFormat::Unspecified,					    &SCANNERS_NONE),
            std::make_pair(AudioContainerFormat::Invalid,						    &SCANNERS_NONE),
            std::make_pair(AudioContainerFormat::ACT,							    &SCANNERS_NONE),
            std::make_pair(AudioContainerFormat::AdaptiveMultiRate,				&SCANNERS_NONE),
            std::make_pair(AudioContainerFormat::AdaptiveMultiRateWideband,		&SCANNERS_NONE),
            std::make_pair(AudioContainerFormat::AdvancedAudioCodec,			    &APE),
            std::make_pair(AudioContainerFormat::Au,							    &SCANNERS_NONE),
            std::make_pair(AudioContainerFormat::AudibleAudiobook,				&SCANNERS_NONE),
            std::make_pair(AudioContainerFormat::AudibleAudiobookEnhanced,		&SCANNERS_NONE),
            std::make_pair(AudioContainerFormat::AudioInterchangeFileFormat,    &AIFF),
            std::make_pair(AudioContainerFormat::Dct,							    &SCANNERS_NONE),
            std::make_pair(AudioContainerFormat::DigitalSpeechStandard,			&SCANNERS_NONE),
            std::make_pair(AudioContainerFormat::FreeLosslessAudioCodec,		&FLAC),
            std::make_pair(AudioContainerFormat::GSM,							    &SCANNERS_NONE),
            std::make_pair(AudioContainerFormat::IKlaxMedia,					    &SCANNERS_NONE),
            std::make_pair(AudioContainerFormat::Matroska,							    &SCANNERS_NONE),
            std::make_pair(AudioContainerFormat::MonkeysAudio,					&APE),
            std::make_pair(AudioContainerFormat::Mousepack,					    &APE),
            std::make_pair(AudioContainerFormat::Mpeg4,							    &SCANNERS_NONE),
            std::make_pair(AudioContainerFormat::MpegLayer1,					    &ID3APE),
            std::make_pair(AudioContainerFormat::MpegLayer2,					    &ID3APE),
            std::make_pair(AudioContainerFormat::MpegLayer3,					    &ID3APE),
            std::make_pair(AudioContainerFormat::NESSoundFormat,				    &SCANNERS_NONE),
            std::make_pair(AudioContainerFormat::Ogg,								&OGG),
            std::make_pair(AudioContainerFormat::OptimFROG,						&ID3APE),
            std::make_pair(AudioContainerFormat::Opus,								&OGG),
            std::make_pair(AudioContainerFormat::RealAudio,						&SCANNERS_NONE),
            std::make_pair(AudioContainerFormat::SonyVoiceFormat,				&SCANNERS_NONE),
            std::make_pair(AudioContainerFormat::Speex,							&OGG),
            std::make_pair(AudioContainerFormat::ThirdGenerationPartnership,	&SCANNERS_NONE),
            std::make_pair(AudioContainerFormat::TomsAudioKompressor,		    &APE),
            std::make_pair(AudioContainerFormat::TTA,							    &ID3APE),
            std::make_pair(AudioContainerFormat::WaveAudio,					    &WAVE),
            std::make_pair(AudioContainerFormat::WavPack,						    &APE),
            std::make_pair(AudioContainerFormat::WindowsMediaAudio,			    &WMA)
    };


    static const std::unordered_map<AudioContainerFormat, const SharedTagScannerVector*> SCANNERS_ALL_MAP = {
            std::make_pair(AudioContainerFormat::Unspecified,					    &SCANNERS_ALL),
            std::make_pair(AudioContainerFormat::Invalid,						    &SCANNERS_ALL),
            std::make_pair(AudioContainerFormat::ACT,							    &SCANNERS_ALL),
            std::make_pair(AudioContainerFormat::AdaptiveMultiRate,				&SCANNERS_ALL),
            std::make_pair(AudioContainerFormat::AdaptiveMultiRateWideband,		&SCANNERS_ALL),
            std::make_pair(AudioContainerFormat::AdvancedAudioCodec,			    &APE_ALL),
            std::make_pair(AudioContainerFormat::Au,							    &SCANNERS_ALL),
            std::make_pair(AudioContainerFormat::AudibleAudiobook,			 	&SCANNERS_ALL),
            std::make_pair(AudioContainerFormat::AudibleAudiobookEnhanced,		&SCANNERS_ALL),
            std::make_pair(AudioContainerFormat::AudioInterchangeFileFormat,	&AIFF_ALL),
            std::make_pair(AudioContainerFormat::Dct,							    &SCANNERS_ALL),
            std::make_pair(AudioContainerFormat::DigitalSpeechStandard,			&SCANNERS_ALL),
            std::make_pair(AudioContainerFormat::FreeLosslessAudioCodec,		&FLAC_ALL),
            std::make_pair(AudioContainerFormat::GSM,							    &SCANNERS_ALL),
            std::make_pair(AudioContainerFormat::IKlaxMedia,					    &SCANNERS_ALL),
            std::make_pair(AudioContainerFormat::Matroska,							    &SCANNERS_ALL),
            std::make_pair(AudioContainerFormat::MonkeysAudio,					&APE_ALL),
            std::make_pair(AudioContainerFormat::Mousepack,						&APE_ALL),
            std::make_pair(AudioContainerFormat::Mpeg4,								&SCANNERS_ALL),
            std::make_pair(AudioContainerFormat::MpegLayer1,					    &ID3APE_ALL),
            std::make_pair(AudioContainerFormat::MpegLayer2,					    &ID3APE_ALL),
            std::make_pair(AudioContainerFormat::MpegLayer3,					    &ID3APE_ALL),
            std::make_pair(AudioContainerFormat::NESSoundFormat,				    &SCANNERS_ALL),
            std::make_pair(AudioContainerFormat::Ogg,								&OGG_ALL),
            std::make_pair(AudioContainerFormat::OptimFROG,						&ID3APE_ALL),
            std::make_pair(AudioContainerFormat::Opus,								&OGG_ALL),
            std::make_pair(AudioContainerFormat::RealAudio,						&SCANNERS_ALL),
            std::make_pair(AudioContainerFormat::SonyVoiceFormat,				&SCANNERS_ALL),
            std::make_pair(AudioContainerFormat::Speex,							&OGG_ALL),
            std::make_pair(AudioContainerFormat::ThirdGenerationPartnership,	&SCANNERS_ALL),
            std::make_pair(AudioContainerFormat::TomsAudioKompressor,			&APE),
            std::make_pair(AudioContainerFormat::TTA,							    &ID3APE_ALL),
            std::make_pair(AudioContainerFormat::WaveAudio,						&WAVE_ALL),
            std::make_pair(AudioContainerFormat::WavPack,						    &APE_ALL),
            std::make_pair(AudioContainerFormat::WindowsMediaAudio,				&WMA_ALL)
    };
    
	const SharedTagScannerVector & TagScannerProvider::getScanners(AudioContainerFormat format, const config::ScanConfiguration &scanConfiguration) {
		if (scanConfiguration.searchForAllPossibleTags) {
			auto it = SCANNERS_ALL_MAP.find(format);
			if (it != SCANNERS_ALL_MAP.end())
				return *it->second;
			return SCANNERS_ALL;
		}
		if (format == AudioContainerFormat::Unspecified && scanConfiguration.processFilesWithoutExtension)
		    return SCANNERS_ALL;
		if (format == AudioContainerFormat::Invalid && scanConfiguration.processNonAudioFiles)
		    return SCANNERS_ALL;
        auto it = SCANNERS_MAP.find(format);
        if (it != SCANNERS_MAP.end())
            return *it->second;
        return SCANNERS_NONE;
	}

	const SharedTagScannerVector& TagScannerProvider::getAllScanners() {
		return SCANNERS_ALL;
	}
}
