#include "AudioContainerFormat.hpp"

#include <vector>
#include <unordered_map>
using namespace std::literals;

namespace tag::priv {
	struct AudioContainerFormatInfo {
		std::vector<std::string> extensions;
		std::string descriptableName;
		bool canContainTags;

		AudioContainerFormatInfo(const std::vector<std::string> &extensions,
								 const std::string &descriptableName,
								 bool canContainTags) 
			: extensions(extensions), descriptableName(descriptableName)
			, canContainTags(canContainTags) {}
	};

	static const std::vector<AudioContainerFormatInfo> CONTAINER_INFO = {
		AudioContainerFormatInfo({}, "Invalid"s, false),
		AudioContainerFormatInfo({ ".ac3"s }, "AC-3"s, false),
		AudioContainerFormatInfo({ ".act"s }, "ACT"s, false),
		AudioContainerFormatInfo({ ".amr"s, ".3ga"s }, "Adaptive Multi-Rate"s, false),
		AudioContainerFormatInfo({ ".awb"s}, "Adaptive Multi-Rate Wideband"s, false),
		AudioContainerFormatInfo({ ".aac"s }, "Advanced Audio Codec", true),
		AudioContainerFormatInfo({ ".au"s }, "Au"s, false),
		AudioContainerFormatInfo({ ".aa"s }, "Audible Audiobook", false),
		AudioContainerFormatInfo({ ".aax"s }, "Audible Audiobook Enhanced", false),
		AudioContainerFormatInfo({ ".aiff"s, ".aif"s }, "Audio Interchange File Format"s, true),
		AudioContainerFormatInfo({ ".dct"s }, "dct"s, false),
		AudioContainerFormatInfo({ ".dss"s }, "Digital Speech Standard"s, false),
		AudioContainerFormatInfo({ ".flac"s }, "Free Lossless Audio Codec"s, true),
		AudioContainerFormatInfo({ ".gsm"s }, "GSM"s, false),
		AudioContainerFormatInfo({ ".iklax"s }, "iKlax Media"s, false),
		AudioContainerFormatInfo({ ".mkv"s, ".mka"s }, "Matroska"s, true),
		AudioContainerFormatInfo({ ".ape"s }, "Monkey's Audio"s, true),
		AudioContainerFormatInfo({ ".mpc"s, ".mp+"s, ".mpp"s }, "Mousepack"s, true),
		AudioContainerFormatInfo({ ".mp4"s, ".m4a"s, ".m4b"s, ".m4p"s, ".m4v"s }, "MPEG-4"s, true),
		AudioContainerFormatInfo({ ".mp1"s }, "MPEG Layer I Audio"s, true),
		AudioContainerFormatInfo({ ".mp2"s }, "MPEG Layer II Audio"s, true),
		AudioContainerFormatInfo({ ".mp3"s }, "MPEG Layer III Audio"s, true),
		AudioContainerFormatInfo({ ".nsf"s }, "NES Sound Format"s, false),
		AudioContainerFormatInfo({ ".ogg"s, ".oga"s, ".ogv"s, ".ogx"s, ".ogm"s, ".spx"s }, "Ogg"s, true),
		AudioContainerFormatInfo({ ".ofr"s }, "OptimFROG"s, true),
		AudioContainerFormatInfo({ ".opus"s }, "Opus"s, true),
		AudioContainerFormatInfo({ ".ra"s, ".rm"s, ".ram"s, ".rmvb"s }, "RealAudio"s, false),
		AudioContainerFormatInfo({ ".dvf"s }, "Sony Voice Format"s, false),
		AudioContainerFormatInfo({ ".spx"s }, "Speex"s, true),
		AudioContainerFormatInfo({ ".3gp"s }, "Third Generation Partnership", false),
		AudioContainerFormatInfo({ ".tak"s }, "Tom's Audio Kompressor"s, true),
		AudioContainerFormatInfo({ ".tta"s }, "TTA"s, true),
		AudioContainerFormatInfo({ ".wav"s, ".wave"s }, "Wave Audio File Format"s, true),
		AudioContainerFormatInfo({ ".wv"s }, "WavPack"s, true),
		AudioContainerFormatInfo({ ".wma"s }, "Windows Media Audio"s, true)
	};

	static const AudioContainerFormatInfo UNSPECIFIED({}, "Unspecified", false);

	static const std::unordered_map<std::string, AudioContainerFormat> EXTENSION_MAP = {
		std::make_pair(""s,			AudioContainerFormat::Unspecified),
		std::make_pair(".ac3"s,		AudioContainerFormat::AC3),
		std::make_pair(".act"s,		AudioContainerFormat::ACT),
		std::make_pair(".amr"s,		AudioContainerFormat::AdaptiveMultiRate),
		std::make_pair(".3ga"s,		AudioContainerFormat::AdaptiveMultiRate),
		std::make_pair(".awb"s,		AudioContainerFormat::AdaptiveMultiRateWideband),
		std::make_pair(".aac"s,		AudioContainerFormat::AdvancedAudioCodec),
		std::make_pair(".au"s,		AudioContainerFormat::Au),
		std::make_pair(".aa"s,		AudioContainerFormat::AudibleAudiobook),
		std::make_pair(".aax"s,		AudioContainerFormat::AudibleAudiobookEnhanced),
        std::make_pair(".aif"s,		AudioContainerFormat::AudioInterchangeFileFormat),
		std::make_pair(".aiff"s,	AudioContainerFormat::AudioInterchangeFileFormat),
		std::make_pair(".dct"s,		AudioContainerFormat::Dct),
		std::make_pair(".dss"s,		AudioContainerFormat::DigitalSpeechStandard),
		std::make_pair(".flac"s,	AudioContainerFormat::FreeLosslessAudioCodec),
		std::make_pair(".gsm"s,		AudioContainerFormat::GSM),
		std::make_pair(".iklax"s,	AudioContainerFormat::IKlaxMedia),
		std::make_pair(".mkv"s,		AudioContainerFormat::Matroska),
		std::make_pair(".mka"s,		AudioContainerFormat::Matroska),
		std::make_pair(".ape"s,		AudioContainerFormat::MonkeysAudio),
		std::make_pair(".mpc"s,		AudioContainerFormat::Mousepack),
		std::make_pair(".mp+"s,		AudioContainerFormat::Mousepack),
		std::make_pair(".mpp"s,		AudioContainerFormat::Mousepack),
		std::make_pair(".mp4"s,		AudioContainerFormat::Mpeg4),
		std::make_pair(".m4a"s,		AudioContainerFormat::Mpeg4),
		std::make_pair(".m4b"s,		AudioContainerFormat::Mpeg4),
		std::make_pair(".m4p"s,		AudioContainerFormat::Mpeg4),
		std::make_pair(".m4v"s,		AudioContainerFormat::Mpeg4),
		std::make_pair(".mp1"s,		AudioContainerFormat::MpegLayer1),
		std::make_pair(".mp2"s,		AudioContainerFormat::MpegLayer2),
		std::make_pair(".mp3"s,		AudioContainerFormat::MpegLayer3),
		std::make_pair(".nsf"s,		AudioContainerFormat::NESSoundFormat),
		std::make_pair(".ogg"s,		AudioContainerFormat::Ogg),
		std::make_pair(".oga"s,		AudioContainerFormat::Ogg),
		std::make_pair(".ogv"s,		AudioContainerFormat::Ogg),
		std::make_pair(".ogx"s,		AudioContainerFormat::Ogg),
		std::make_pair(".ogm"s,		AudioContainerFormat::Ogg),
		std::make_pair(".ofr"s,		AudioContainerFormat::OptimFROG),
		std::make_pair(".opus"s,	AudioContainerFormat::Opus),
		std::make_pair(".ra"s,		AudioContainerFormat::RealAudio),
		std::make_pair(".rm"s,		AudioContainerFormat::RealAudio),
		std::make_pair(".ram"s,		AudioContainerFormat::RealAudio),
		std::make_pair(".rmvb"s,	AudioContainerFormat::RealAudio),
		std::make_pair(".dvf"s,		AudioContainerFormat::SonyVoiceFormat),
		std::make_pair(".spx"s,		AudioContainerFormat::Speex),
		std::make_pair(".3gp"s,		AudioContainerFormat::ThirdGenerationPartnership),
		std::make_pair(".tak"s,		AudioContainerFormat::TomsAudioKompressor),
		std::make_pair(".tta"s,		AudioContainerFormat::TTA),
		std::make_pair(".wav"s,		AudioContainerFormat::WaveAudio),
		std::make_pair(".wave"s,	AudioContainerFormat::WaveAudio),
		std::make_pair(".wv"s,		AudioContainerFormat::WavPack),
		std::make_pair(".wma"s,		AudioContainerFormat::WindowsMediaAudio)
	};
}


namespace tag::string {
	const std::string& toString(AudioContainerFormat audioContainerFormat) {
		static const std::string EMPTY;
		
		if (audioContainerFormat == AudioContainerFormat::Unspecified)
			return priv::UNSPECIFIED.descriptableName;

		std::size_t idx = static_cast<std::size_t>(audioContainerFormat);
		if (idx < priv::CONTAINER_INFO.size())
			return priv::CONTAINER_INFO[idx].descriptableName;
		return EMPTY;
	}
}


namespace tag::util {
	AudioContainerFormat fileContainerFormat(const std::filesystem::path & filePath) {
		auto it = priv::EXTENSION_MAP.find(filePath.extension().string());
		if (it != priv::EXTENSION_MAP.end())
			return it->second;
		return AudioContainerFormat::Invalid;
	}

	const std::vector<std::string>& containerFormatExtensions(AudioContainerFormat audioContainerFormat) {
		static const std::vector<std::string> EMPTY;

		std::size_t idx = static_cast<std::size_t>(audioContainerFormat);
		if (idx < priv::CONTAINER_INFO.size())
			return priv::CONTAINER_INFO[idx].extensions;
		return EMPTY;
	}

	bool canContainTags(AudioContainerFormat audioContainerFormat) {
		if (audioContainerFormat == AudioContainerFormat::Unspecified)
			return priv::UNSPECIFIED.canContainTags;

		std::size_t idx = static_cast<std::size_t>(audioContainerFormat);
		if (idx < priv::CONTAINER_INFO.size())
			return priv::CONTAINER_INFO[idx].canContainTags;
		return false;
	}

	bool canContainTags(const std::filesystem::path & filePath) {
		return canContainTags(fileContainerFormat(filePath));
	}

    bool isValidContainer(AudioContainerFormat audioContainerFormat) {
        return audioContainerFormat != AudioContainerFormat::Invalid &&
               audioContainerFormat != AudioContainerFormat::Unspecified;
    }
}