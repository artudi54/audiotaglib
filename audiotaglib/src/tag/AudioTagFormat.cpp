#include "AudioTagFormat.hpp"
using namespace std::literals;

namespace tag::priv {
	void append(std::string &str, const std::string &text) {
		if (str.empty())
			str += text;
		else
			str += ", "s + text;
	};
}

namespace tag::string {
	std::string toString(AudioTagFormat audioTagFormat) {
		std::string result;
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::ID3v1))
			priv::append(result, "ID3v1"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::ID3v22))
			priv::append(result, "ID3v2.2"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::ID3v23))
			priv::append(result, "ID3v2.3"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::ID3v24))
			priv::append(result, "ID3v2.4"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::APEv1))
			priv::append(result, "APEv1"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::APEv2))
			priv::append(result, "APEv2"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::FLACPictures))
			priv::append(result, "Flac Pictures"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::VorbisComments))
			priv::append(result, "Vorbis Comments"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::ASFMetadata))
			priv::append(result, "ASF Metadata"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::RiffInfo))
			priv::append(result, "Riff Info"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::AiffChunks))
			priv::append(result, "Aiff Chunks"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::MatroskaMetadata))
			priv::append(result, "Matroska Metadata"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::MP4Metadata))
			priv::append(result, "MP4 Metadata"s);

		if (result.empty())
			result = "None"s;

		return result;
	}
}