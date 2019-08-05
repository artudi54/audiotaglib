#include "ContainerFormat.hpp"
#include <vector>
#include <unordered_map>
using namespace std::literals;
namespace fs = std::filesystem;

namespace tag::priv {
	struct ContainerFormatInfo {
		std::vector<std::string> extensions;
		std::string descriptableName;
		bool canContainTags;

		ContainerFormatInfo(const std::vector<std::string> &extensions,
                            const std::string &descriptableName,
                            bool canContainTags)
			: extensions(extensions), descriptableName(descriptableName)
			, canContainTags(canContainTags) {}
	};

	static const std::vector<ContainerFormatInfo> CONTAINER_INFO = {
            ContainerFormatInfo({}, "Unknown"s, false),
            ContainerFormatInfo({".ac3"s }, "AC-3"s, false),
            ContainerFormatInfo({".act"s }, "ACT"s, false),
            ContainerFormatInfo({".amr"s, ".3ga"s }, "Adaptive Multi-Rate"s, false),
            ContainerFormatInfo({".awb"s}, "Adaptive Multi-Rate Wideband"s, false),
            ContainerFormatInfo({".aac"s }, "Advanced Audio Codec", true),
            ContainerFormatInfo({".au"s }, "Au"s, false),
            ContainerFormatInfo({".aa"s }, "Audible Audiobook", false),
            ContainerFormatInfo({".aax"s }, "Audible Audiobook Enhanced", false),
            ContainerFormatInfo({".aiff"s, ".aif"s }, "Audio Interchange File Format"s, true),
            ContainerFormatInfo({".dct"s }, "dct"s, false),
            ContainerFormatInfo({".dss"s }, "Digital Speech Standard"s, false),
            ContainerFormatInfo({".flac"s }, "Free Lossless Audio Codec"s, true),
            ContainerFormatInfo({".gsm"s }, "GSM"s, false),
            ContainerFormatInfo({".iklax"s }, "iKlax Media"s, false),
            ContainerFormatInfo({".mkv"s, ".mka"s }, "Matroska"s, true),
            ContainerFormatInfo({".ape"s }, "Monkey's Audio"s, true),
            ContainerFormatInfo({".mpc"s, ".mp+"s, ".mpp"s }, "Mousepack"s, true),
            ContainerFormatInfo({".mp4"s, ".m4a"s, ".m4b"s, ".m4p"s, ".m4v"s }, "MPEG-4"s, true),
            ContainerFormatInfo({".mp1"s }, "MPEG Layer I Audio"s, true),
            ContainerFormatInfo({".mp2"s }, "MPEG Layer II Audio"s, true),
            ContainerFormatInfo({".mp3"s }, "MPEG Layer III Audio"s, true),
            ContainerFormatInfo({".nsf"s }, "NES Sound Format"s, false),
            ContainerFormatInfo({".ogg"s, ".oga"s, ".ogv"s, ".ogx"s, ".ogm"s }, "Ogg"s, true),
            ContainerFormatInfo({".ofr"s }, "OptimFROG"s, true),
            ContainerFormatInfo({".opus"s }, "Opus"s, true),
            ContainerFormatInfo({".ra"s, ".rm"s, ".ram"s, ".rmvb"s }, "RealAudio"s, false),
            ContainerFormatInfo({".dvf"s }, "Sony Voice Format"s, false),
            ContainerFormatInfo({".spx"s }, "Speex"s, true),
            ContainerFormatInfo({".3gp"s }, "Third Generation Partnership", false),
            ContainerFormatInfo({".tak"s }, "Tom's Audio Kompressor"s, true),
            ContainerFormatInfo({".tta"s }, "TTA"s, true),
            ContainerFormatInfo({".wav"s, ".wave"s }, "Wave Audio File Format"s, true),
            ContainerFormatInfo({".wv"s }, "WavPack"s, true),
            ContainerFormatInfo({".wma"s }, "Windows Media Audio"s, true)
	};

	static const std::unordered_map<std::string, ContainerFormat> EXTENSION_MAP = {
		std::make_pair(""s,			ContainerFormat::Unknown),
		std::make_pair(".ac3"s,		ContainerFormat::AC3),
		std::make_pair(".act"s,		ContainerFormat::ACT),
		std::make_pair(".amr"s,		ContainerFormat::AdaptiveMultiRate),
		std::make_pair(".3ga"s,		ContainerFormat::AdaptiveMultiRate),
		std::make_pair(".awb"s,		ContainerFormat::AdaptiveMultiRateWideband),
		std::make_pair(".aac"s,		ContainerFormat::AdvancedAudioCodec),
		std::make_pair(".au"s,		ContainerFormat::Au),
		std::make_pair(".aa"s,		ContainerFormat::AudibleAudiobook),
		std::make_pair(".aax"s,		ContainerFormat::AudibleAudiobookEnhanced),
        std::make_pair(".aif"s,		ContainerFormat::AudioInterchangeFileFormat),
		std::make_pair(".aiff"s,	ContainerFormat::AudioInterchangeFileFormat),
		std::make_pair(".dct"s,		ContainerFormat::Dct),
		std::make_pair(".dss"s,		ContainerFormat::DigitalSpeechStandard),
		std::make_pair(".flac"s,	ContainerFormat::FreeLosslessAudioCodec),
		std::make_pair(".gsm"s,		ContainerFormat::GSM),
		std::make_pair(".iklax"s,	ContainerFormat::IKlaxMedia),
		std::make_pair(".mkv"s,		ContainerFormat::Matroska),
		std::make_pair(".mka"s,		ContainerFormat::Matroska),
		std::make_pair(".ape"s,		ContainerFormat::MonkeysAudio),
		std::make_pair(".mpc"s,		ContainerFormat::Mousepack),
		std::make_pair(".mp+"s,		ContainerFormat::Mousepack),
		std::make_pair(".mpp"s,		ContainerFormat::Mousepack),
		std::make_pair(".mp4"s,		ContainerFormat::Mpeg4),
		std::make_pair(".m4a"s,		ContainerFormat::Mpeg4),
		std::make_pair(".m4b"s,		ContainerFormat::Mpeg4),
		std::make_pair(".m4p"s,		ContainerFormat::Mpeg4),
		std::make_pair(".m4v"s,		ContainerFormat::Mpeg4),
		std::make_pair(".mp1"s,		ContainerFormat::MpegLayer1),
		std::make_pair(".mp2"s,		ContainerFormat::MpegLayer2),
		std::make_pair(".mp3"s,		ContainerFormat::MpegLayer3),
		std::make_pair(".nsf"s,		ContainerFormat::NESSoundFormat),
		std::make_pair(".ogg"s,		ContainerFormat::Ogg),
		std::make_pair(".oga"s,		ContainerFormat::Ogg),
		std::make_pair(".ogv"s,		ContainerFormat::Ogg),
		std::make_pair(".ogx"s,		ContainerFormat::Ogg),
		std::make_pair(".ogm"s,		ContainerFormat::Ogg),
		std::make_pair(".ofr"s,		ContainerFormat::OptimFROG),
		std::make_pair(".opus"s,	ContainerFormat::Opus),
		std::make_pair(".ra"s,		ContainerFormat::RealAudio),
		std::make_pair(".rm"s,		ContainerFormat::RealAudio),
		std::make_pair(".ram"s,		ContainerFormat::RealAudio),
		std::make_pair(".rmvb"s,	ContainerFormat::RealAudio),
		std::make_pair(".dvf"s,		ContainerFormat::SonyVoiceFormat),
		std::make_pair(".spx"s,		ContainerFormat::Speex),
		std::make_pair(".3gp"s,		ContainerFormat::ThirdGenerationPartnership),
		std::make_pair(".tak"s,		ContainerFormat::TomsAudioKompressor),
		std::make_pair(".tta"s,		ContainerFormat::TTA),
		std::make_pair(".wav"s,		ContainerFormat::WaveAudio),
		std::make_pair(".wave"s,	ContainerFormat::WaveAudio),
		std::make_pair(".wv"s,		ContainerFormat::WavPack),
		std::make_pair(".wma"s,		ContainerFormat::WindowsMediaAudio)
	};
}


namespace tag::string {
	const std::string& toString(ContainerFormat containerFormat) {
		static const std::string EMPTY;

		std::size_t idx = static_cast<std::size_t>(containerFormat);
		if (idx < priv::CONTAINER_INFO.size())
			return priv::CONTAINER_INFO[idx].descriptableName;
		return EMPTY;
	}
}


namespace tag::util {
	ContainerFormat containerFormatByExtension(const fs::path &filePath) {
		auto it = priv::EXTENSION_MAP.find(filePath.extension().string());
		if (it != priv::EXTENSION_MAP.end())
			return it->second;
		return ContainerFormat::Unknown;
	}

	const std::vector<std::string>& containerFormatExtensions(ContainerFormat containerFormat) {
		static const std::vector<std::string> EMPTY;

		std::size_t idx = static_cast<std::size_t>(containerFormat);
		if (idx < priv::CONTAINER_INFO.size())
			return priv::CONTAINER_INFO[idx].extensions;
		return EMPTY;
	}

	bool canContainTags(ContainerFormat containerFormat) {
		std::size_t idx = static_cast<std::size_t>(containerFormat);
		if (idx < priv::CONTAINER_INFO.size())
			return priv::CONTAINER_INFO[idx].canContainTags;
		return false;
	}

	bool canContainTags(const fs::path & filePath) {
		return canContainTags(containerFormatByExtension(filePath));
	}

    bool isValidContainer(ContainerFormat containerFormat) {
        return containerFormat != ContainerFormat::Unknown;
    }
}