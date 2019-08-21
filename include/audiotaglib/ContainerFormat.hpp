#pragma once
#include <cstdint>
#include <string>
#include <filesystem>


namespace audiotaglib {
	enum class ContainerFormat : std::uint16_t {
		Unknown,
		AC3,
		ACT,
		AdaptiveMultiRate,
		AdaptiveMultiRateWideband,
		AdvancedAudioCodec,
		Au,
		AudibleAudiobook,
		AudibleAudiobookEnhanced,
		AudioInterchangeFileFormat,
		Dct,
		DigitalSpeechStandard,
		FreeLosslessAudioCodec,
		GSM,
		IKlaxMedia,
		Matroska,
		MonkeysAudio,
		Mousepack,
		Mpeg4,
		MpegLayer1,
		MpegLayer2,
		MpegLayer3,
		NESSoundFormat,
		Ogg,
		OptimFROG,
		Opus,
		RealAudio,
		SonyVoiceFormat,
		Speex,
		ThirdGenerationPartnership,
		TomsAudioKompressor,
		TTA,
		WaveAudio,
		WavPack,
		WindowsMediaAudio
	};
}

namespace audiotaglib::string {
	const std::string& toString(ContainerFormat containerFormat);
}

namespace audiotaglib::util {
	ContainerFormat containerFormatByExtension(const std::filesystem::path &filePath);
	const std::vector<std::string>& containerFormatExtensions(ContainerFormat containerFormat);
	bool canContainTags(ContainerFormat containerFormat);
	bool canContainTags(const std::filesystem::path &filePath);
    bool isValidContainer(ContainerFormat containerFormat);
}
