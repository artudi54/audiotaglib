#include "AudioTagFormat.hpp"
using namespace std::literals;

namespace tag::string {
	
	void append(std::string &str, const std::string &text) {
		if (str.empty())
			str += text;
		else
			str += ", "s + text;
	};


	std::string toString(AudioTagFormat audioTagFormat) {
		std::string result;
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::ID3v1))
			append(result, "ID3v1"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::ID3v22))
			append(result, "ID3v2.2"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::ID3v23))
			append(result, "ID3v2.3"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::ID3v24))
			append(result, "ID3v2.4"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::APEv1))
			append(result, "APEv1"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::APEv2))
			append(result, "APEv2"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::VorbisComments))
			append(result, "Vorbis Comments"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::ASFMetadata))
			append(result, "ASF Metadata"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::RiffInfo))
			append(result, "Riff Info"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::AiffChunks))
			append(result, "Aiff Chunks"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::MatroskaMetadata))
			append(result, "Matroska Metadata"s);
		if (util::hasAnyTag(audioTagFormat & AudioTagFormat::MP4Metadata))
			append(result, "MP4 Metadata"s);

		if (result.empty())
			result = "None"s;

		return result;
	}
}