#include "TagScannerProvider.hpp"
#include <tag/scanner/AiffChunksScanner.hpp>
#include <tag/scanner/APETagScanner.hpp>
#include <tag/scanner/ASFMetadataScanner.hpp>
#include <tag/scanner/ID3TagScanner.hpp>
#include <tag/scanner/RiffInfoScanner.hpp>
#include <tag/scanner/FLACScanner.hpp>
#include <tag/scanner/OggScanner.hpp>
#include <unordered_map>
using namespace std::literals;


namespace tag::scanner {
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
            std::make_pair(ContainerFormat::Unspecified,					    &SCANNERS_NONE),
            std::make_pair(ContainerFormat::Invalid,						    &SCANNERS_NONE),
            std::make_pair(ContainerFormat::ACT,							    &SCANNERS_NONE),
            std::make_pair(ContainerFormat::AdaptiveMultiRate,				&SCANNERS_NONE),
            std::make_pair(ContainerFormat::AdaptiveMultiRateWideband,		&SCANNERS_NONE),
            std::make_pair(ContainerFormat::AdvancedAudioCodec,			    &APE),
            std::make_pair(ContainerFormat::Au,							    &SCANNERS_NONE),
            std::make_pair(ContainerFormat::AudibleAudiobook,				&SCANNERS_NONE),
            std::make_pair(ContainerFormat::AudibleAudiobookEnhanced,		&SCANNERS_NONE),
            std::make_pair(ContainerFormat::AudioInterchangeFileFormat,    &AIFF),
            std::make_pair(ContainerFormat::Dct,							    &SCANNERS_NONE),
            std::make_pair(ContainerFormat::DigitalSpeechStandard,			&SCANNERS_NONE),
            std::make_pair(ContainerFormat::FreeLosslessAudioCodec,		&FLAC),
            std::make_pair(ContainerFormat::GSM,							    &SCANNERS_NONE),
            std::make_pair(ContainerFormat::IKlaxMedia,					    &SCANNERS_NONE),
            std::make_pair(ContainerFormat::Matroska,							    &SCANNERS_NONE),
            std::make_pair(ContainerFormat::MonkeysAudio,					&APE),
            std::make_pair(ContainerFormat::Mousepack,					    &APE),
            std::make_pair(ContainerFormat::Mpeg4,							    &SCANNERS_NONE),
            std::make_pair(ContainerFormat::MpegLayer1,					    &ID3APE),
            std::make_pair(ContainerFormat::MpegLayer2,					    &ID3APE),
            std::make_pair(ContainerFormat::MpegLayer3,					    &ID3APE),
            std::make_pair(ContainerFormat::NESSoundFormat,				    &SCANNERS_NONE),
            std::make_pair(ContainerFormat::Ogg,								&OGG),
            std::make_pair(ContainerFormat::OptimFROG,						&ID3APE),
            std::make_pair(ContainerFormat::Opus,								&OGG),
            std::make_pair(ContainerFormat::RealAudio,						&SCANNERS_NONE),
            std::make_pair(ContainerFormat::SonyVoiceFormat,				&SCANNERS_NONE),
            std::make_pair(ContainerFormat::Speex,							&OGG),
            std::make_pair(ContainerFormat::ThirdGenerationPartnership,	&SCANNERS_NONE),
            std::make_pair(ContainerFormat::TomsAudioKompressor,		    &APE),
            std::make_pair(ContainerFormat::TTA,							    &ID3APE),
            std::make_pair(ContainerFormat::WaveAudio,					    &WAVE),
            std::make_pair(ContainerFormat::WavPack,						    &APE),
            std::make_pair(ContainerFormat::WindowsMediaAudio,			    &WMA)
    };


    static const std::unordered_map<ContainerFormat, const std::vector<std::unique_ptr<TagScanner>>*> SCANNERS_ALL_MAP = {
            std::make_pair(ContainerFormat::Unspecified,					    &SCANNERS_ALL),
            std::make_pair(ContainerFormat::Invalid,						    &SCANNERS_ALL),
            std::make_pair(ContainerFormat::ACT,							    &SCANNERS_ALL),
            std::make_pair(ContainerFormat::AdaptiveMultiRate,				&SCANNERS_ALL),
            std::make_pair(ContainerFormat::AdaptiveMultiRateWideband,		&SCANNERS_ALL),
            std::make_pair(ContainerFormat::AdvancedAudioCodec,			    &APE_ALL),
            std::make_pair(ContainerFormat::Au,							    &SCANNERS_ALL),
            std::make_pair(ContainerFormat::AudibleAudiobook,			 	&SCANNERS_ALL),
            std::make_pair(ContainerFormat::AudibleAudiobookEnhanced,		&SCANNERS_ALL),
            std::make_pair(ContainerFormat::AudioInterchangeFileFormat,	&AIFF_ALL),
            std::make_pair(ContainerFormat::Dct,							    &SCANNERS_ALL),
            std::make_pair(ContainerFormat::DigitalSpeechStandard,			&SCANNERS_ALL),
            std::make_pair(ContainerFormat::FreeLosslessAudioCodec,		&FLAC_ALL),
            std::make_pair(ContainerFormat::GSM,							    &SCANNERS_ALL),
            std::make_pair(ContainerFormat::IKlaxMedia,					    &SCANNERS_ALL),
            std::make_pair(ContainerFormat::Matroska,							    &SCANNERS_ALL),
            std::make_pair(ContainerFormat::MonkeysAudio,					&APE_ALL),
            std::make_pair(ContainerFormat::Mousepack,						&APE_ALL),
            std::make_pair(ContainerFormat::Mpeg4,								&SCANNERS_ALL),
            std::make_pair(ContainerFormat::MpegLayer1,					    &ID3APE_ALL),
            std::make_pair(ContainerFormat::MpegLayer2,					    &ID3APE_ALL),
            std::make_pair(ContainerFormat::MpegLayer3,					    &ID3APE_ALL),
            std::make_pair(ContainerFormat::NESSoundFormat,				    &SCANNERS_ALL),
            std::make_pair(ContainerFormat::Ogg,								&OGG_ALL),
            std::make_pair(ContainerFormat::OptimFROG,						&ID3APE_ALL),
            std::make_pair(ContainerFormat::Opus,								&OGG_ALL),
            std::make_pair(ContainerFormat::RealAudio,						&SCANNERS_ALL),
            std::make_pair(ContainerFormat::SonyVoiceFormat,				&SCANNERS_ALL),
            std::make_pair(ContainerFormat::Speex,							&OGG_ALL),
            std::make_pair(ContainerFormat::ThirdGenerationPartnership,	&SCANNERS_ALL),
            std::make_pair(ContainerFormat::TomsAudioKompressor,			&APE),
            std::make_pair(ContainerFormat::TTA,							    &ID3APE_ALL),
            std::make_pair(ContainerFormat::WaveAudio,						&WAVE_ALL),
            std::make_pair(ContainerFormat::WavPack,						    &APE_ALL),
            std::make_pair(ContainerFormat::WindowsMediaAudio,				&WMA_ALL)
    };
    
	const std::vector<std::unique_ptr<TagScanner>>& TagScannerProvider::getScanners(ContainerFormat format, const config::ScanConfiguration &scanConfiguration) {
		if (scanConfiguration.searchForAllPossibleTags) {
			auto it = SCANNERS_ALL_MAP.find(format);
			if (it != SCANNERS_ALL_MAP.end())
				return *it->second;
			return SCANNERS_ALL;
		}
		if (format == ContainerFormat::Unspecified && scanConfiguration.processFilesWithoutExtension)
		    return SCANNERS_ALL;
		if (format == ContainerFormat::Invalid && scanConfiguration.processNonAudioFiles)
		    return SCANNERS_ALL;
        auto it = SCANNERS_MAP.find(format);
        if (it != SCANNERS_MAP.end())
            return *it->second;
        return SCANNERS_NONE;
	}

	const std::vector<std::unique_ptr<TagScanner>>& TagScannerProvider::getAllScanners() {
		return SCANNERS_ALL;
	}
}
