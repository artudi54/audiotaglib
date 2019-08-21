#include "TagScannerProvider.hpp"
#include <audiotaglib/tag_scanner/AiffChunksScanner.hpp>
#include <audiotaglib/tag_scanner/APETagScanner.hpp>
#include <audiotaglib/tag_scanner/ASFMetadataScanner.hpp>
#include <audiotaglib/tag_scanner/ID3TagScanner.hpp>
#include <audiotaglib/tag_scanner/RiffInfoScanner.hpp>
#include <audiotaglib/tag_scanner/FLACScanner.hpp>
#include <audiotaglib/tag_scanner/OggScanner.hpp>
#include <unordered_map>
using namespace std::literals;


namespace audiotaglib::tag_scanner {
    template <class... Args>
    static std::vector<std::unique_ptr<TagScanner>> makeVector(Args&&... args) {
        std::vector<std::unique_ptr<TagScanner>> result;
        result.reserve(sizeof...(Args));
        (result.push_back(std::forward<Args>(args)), ...);
        return result;
    }

    static const std::vector<std::unique_ptr<TagScanner>> SCANNERS_NONE;
    static const std::vector<std::unique_ptr<TagScanner>> SCANNERS_ALL = makeVector(
            std::make_unique<RiffInfoScanner>(),
            std::make_unique<AiffChunksScanner>(),
            std::make_unique<ASFMetadataScanner>(),
            std::make_unique<FLACScanner>(),
            std::make_unique<ID3TagScanner>(),
            std::make_unique<APETagScanner>(),
            std::make_unique<OggScanner>()
    );
    static const std::vector<std::unique_ptr<TagScanner>> AIFF = makeVector(
            std::make_unique<AiffChunksScanner>()
    );
    static const std::vector<std::unique_ptr<TagScanner>> AIFF_ALL = makeVector(
            std::make_unique<AiffChunksScanner>(),
            std::make_unique<RiffInfoScanner>(),
            std::make_unique<ASFMetadataScanner>(),
            std::make_unique<FLACScanner>(),
            std::make_unique<ID3TagScanner>(),
            std::make_unique<APETagScanner>(),
            std::make_unique<OggScanner>()
    );
    static const std::vector<std::unique_ptr<TagScanner>> APE = makeVector(
            std::make_unique<APETagScanner>(),
            std::make_unique<ID3TagScanner>()
    );
    static const std::vector<std::unique_ptr<TagScanner>> APE_ALL = makeVector(
            std::make_unique<APETagScanner>(),
            std::make_unique<ID3TagScanner>(),
            std::make_unique<ASFMetadataScanner>(),
            std::make_unique<FLACScanner>(),
            std::make_unique<RiffInfoScanner>(),
            std::make_unique<AiffChunksScanner>(),
            std::make_unique<OggScanner>()
    );
    static const std::vector<std::unique_ptr<TagScanner>> FLAC = makeVector(
            std::make_unique<FLACScanner>()
    );
    static const std::vector<std::unique_ptr<TagScanner>> FLAC_ALL = makeVector(
            std::make_unique<FLACScanner>(),
            std::make_unique<ASFMetadataScanner>(),
            std::make_unique<RiffInfoScanner>(),
            std::make_unique<AiffChunksScanner>(),
            std::make_unique<ID3TagScanner>(),
            std::make_unique<APETagScanner>(),
            std::make_unique<OggScanner>()
    );
    static const std::vector<std::unique_ptr<TagScanner>> ID3APE = makeVector(
            std::make_unique<ID3TagScanner>(),
            std::make_unique<APETagScanner>()
    );
    static const std::vector<std::unique_ptr<TagScanner>> ID3APE_ALL = makeVector(
            std::make_unique<ID3TagScanner>(),
            std::make_unique<APETagScanner>(),
            std::make_unique<ASFMetadataScanner>(),
            std::make_unique<RiffInfoScanner>(),
            std::make_unique<AiffChunksScanner>(),
            std::make_unique<FLACScanner>(),
            std::make_unique<OggScanner>()
    );
    static const std::vector<std::unique_ptr<TagScanner>> OGG = makeVector(
            std::make_unique<OggScanner>()
    );
    static const std::vector<std::unique_ptr<TagScanner>> OGG_ALL = makeVector(
            std::make_unique<OggScanner>(),
            std::make_unique<ASFMetadataScanner>(),
            std::make_unique<FLACScanner>(),
            std::make_unique<RiffInfoScanner>(),
            std::make_unique<AiffChunksScanner>(),
            std::make_unique<ID3TagScanner>(),
            std::make_unique<APETagScanner>(),
            std::make_unique<OggScanner>()
    );
    static const std::vector<std::unique_ptr<TagScanner>> WAVE = makeVector(
            std::make_unique<RiffInfoScanner>()
    );
    static const std::vector<std::unique_ptr<TagScanner>> WAVE_ALL = makeVector(
            std::make_unique<RiffInfoScanner>(),
            std::make_unique<AiffChunksScanner>(),
            std::make_unique<ASFMetadataScanner>(),
            std::make_unique<FLACScanner>(),
            std::make_unique<ID3TagScanner>(),
            std::make_unique<APETagScanner>(),
            std::make_unique<OggScanner>()
    );
    static const std::vector<std::unique_ptr<TagScanner>> WMA = makeVector(
            std::make_unique<ASFMetadataScanner>()
    );
    static const std::vector<std::unique_ptr<TagScanner>> WMA_ALL = makeVector(
            std::make_unique<ASFMetadataScanner>(),
            std::make_unique<RiffInfoScanner>(),
            std::make_unique<AiffChunksScanner>(),
            std::make_unique<FLACScanner>(),
            std::make_unique<ID3TagScanner>(),
            std::make_unique<APETagScanner>(),
            std::make_unique<OggScanner>()
    );



    static const std::unordered_map<ContainerFormat, const std::vector<std::unique_ptr<TagScanner>>*> SCANNERS_MAP = {
            {ContainerFormat::Unknown,					    &SCANNERS_NONE},
            {ContainerFormat::ACT,							    &SCANNERS_NONE},
            {ContainerFormat::AdaptiveMultiRate,				&SCANNERS_NONE},
            {ContainerFormat::AdaptiveMultiRateWideband,		&SCANNERS_NONE},
            {ContainerFormat::AdvancedAudioCodec,			    &APE},
            {ContainerFormat::Au,							    &SCANNERS_NONE},
            {ContainerFormat::AudibleAudiobook,				&SCANNERS_NONE},
            {ContainerFormat::AudibleAudiobookEnhanced,		&SCANNERS_NONE},
            {ContainerFormat::AudioInterchangeFileFormat,    &AIFF},
            {ContainerFormat::Dct,							    &SCANNERS_NONE},
            {ContainerFormat::DigitalSpeechStandard,			&SCANNERS_NONE},
            {ContainerFormat::FreeLosslessAudioCodec,		&FLAC},
            {ContainerFormat::GSM,							    &SCANNERS_NONE},
            {ContainerFormat::IKlaxMedia,					    &SCANNERS_NONE},
            {ContainerFormat::Matroska,							    &SCANNERS_NONE},
            {ContainerFormat::MonkeysAudio,					&APE},
            {ContainerFormat::Mousepack,					    &APE},
            {ContainerFormat::Mpeg4,							    &SCANNERS_NONE},
            {ContainerFormat::MpegLayer1,					    &ID3APE},
            {ContainerFormat::MpegLayer2,					    &ID3APE},
            {ContainerFormat::MpegLayer3,					    &ID3APE},
            {ContainerFormat::NESSoundFormat,				    &SCANNERS_NONE},
            {ContainerFormat::Ogg,								&OGG},
            {ContainerFormat::OptimFROG,						&ID3APE},
            {ContainerFormat::Opus,								&OGG},
            {ContainerFormat::RealAudio,						&SCANNERS_NONE},
            {ContainerFormat::SonyVoiceFormat,				&SCANNERS_NONE},
            {ContainerFormat::Speex,							&OGG},
            {ContainerFormat::ThirdGenerationPartnership,	&SCANNERS_NONE},
            {ContainerFormat::TomsAudioKompressor,		    &APE},
            {ContainerFormat::TTA,							    &ID3APE},
            {ContainerFormat::WaveAudio,					    &WAVE},
            {ContainerFormat::WavPack,						    &APE},
            {ContainerFormat::WindowsMediaAudio,			    &WMA}
    };


    static const std::unordered_map<ContainerFormat, const std::vector<std::unique_ptr<TagScanner>>*> SCANNERS_ALL_MAP = {
            {ContainerFormat::Unknown,					    &SCANNERS_ALL},
            {ContainerFormat::ACT,							    &SCANNERS_ALL},
            {ContainerFormat::AdaptiveMultiRate,				&SCANNERS_ALL},
            {ContainerFormat::AdaptiveMultiRateWideband,		&SCANNERS_ALL},
            {ContainerFormat::AdvancedAudioCodec,			    &APE_ALL},
            {ContainerFormat::Au,							    &SCANNERS_ALL},
            {ContainerFormat::AudibleAudiobook,			 	&SCANNERS_ALL},
            {ContainerFormat::AudibleAudiobookEnhanced,		&SCANNERS_ALL},
            {ContainerFormat::AudioInterchangeFileFormat,	&AIFF_ALL},
            {ContainerFormat::Dct,							    &SCANNERS_ALL},
            {ContainerFormat::DigitalSpeechStandard,			&SCANNERS_ALL},
            {ContainerFormat::FreeLosslessAudioCodec,		&FLAC_ALL},
            {ContainerFormat::GSM,							    &SCANNERS_ALL},
            {ContainerFormat::IKlaxMedia,					    &SCANNERS_ALL},
            {ContainerFormat::Matroska,							    &SCANNERS_ALL},
            {ContainerFormat::MonkeysAudio,					&APE_ALL},
            {ContainerFormat::Mousepack,						&APE_ALL},
            {ContainerFormat::Mpeg4,								&SCANNERS_ALL},
            {ContainerFormat::MpegLayer1,					    &ID3APE_ALL},
            {ContainerFormat::MpegLayer2,					    &ID3APE_ALL},
            {ContainerFormat::MpegLayer3,					    &ID3APE_ALL},
            {ContainerFormat::NESSoundFormat,				    &SCANNERS_ALL},
            {ContainerFormat::Ogg,								&OGG_ALL},
            {ContainerFormat::OptimFROG,						&ID3APE_ALL},
            {ContainerFormat::Opus,								&OGG_ALL},
            {ContainerFormat::RealAudio,						&SCANNERS_ALL},
            {ContainerFormat::SonyVoiceFormat,				&SCANNERS_ALL},
            {ContainerFormat::Speex,							&OGG_ALL},
            {ContainerFormat::ThirdGenerationPartnership,	&SCANNERS_ALL},
            {ContainerFormat::TomsAudioKompressor,			&APE},
            {ContainerFormat::TTA,							    &ID3APE_ALL},
            {ContainerFormat::WaveAudio,						&WAVE_ALL},
            {ContainerFormat::WavPack,						    &APE_ALL},
            {ContainerFormat::WindowsMediaAudio,				&WMA_ALL}
    };
    
	const std::vector<std::unique_ptr<TagScanner>>& TagScannerProvider::getScanners(ContainerFormat format, const config::ScanConfiguration &scanConfiguration) {
	    if (scanConfiguration.searchForAllPossibleTags) {
			auto it = SCANNERS_ALL_MAP.find(format);
			if (it != SCANNERS_ALL_MAP.end())
				return *it->second;
			return SCANNERS_ALL;
		}

		if (format == ContainerFormat::Unknown && scanConfiguration.processUnknownContainerFormats)
		    return SCANNERS_ALL;

        auto it = SCANNERS_MAP.find(format);
        if (it != SCANNERS_MAP.end())
            return *it->second;
        return SCANNERS_NONE;
	}
}
