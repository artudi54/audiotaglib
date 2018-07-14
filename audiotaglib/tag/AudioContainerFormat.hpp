#pragma once
#include <cstdint>
#include <filesystem>


namespace tag {
	enum class AudioContainerFormat : std::uint16_t {
		Unspecified = static_cast<std::uint16_t>(-1),
		Invalid = 0,
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

namespace tag::string {
	const std::string& toString(AudioContainerFormat audioContainerFormat);
}

namespace tag::util {
	AudioContainerFormat fileContainerFormat(const std::filesystem::path &filePath);
	const std::vector<std::string>& containerFormatExtensions(AudioContainerFormat audioContainerFormat);
	bool canContainTags(AudioContainerFormat audioContainerFormat);
	bool canContainTags(const std::filesystem::path &filePath);
}
