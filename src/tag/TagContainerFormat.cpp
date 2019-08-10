#include "TagContainerFormat.hpp"
using namespace std::literals;

namespace tag::priv {
	void append(std::string &str, const std::string &text) {
		if (str.empty())
			str += text;
		else
			str += ", "s + text;
	}
}

namespace tag::string {
	std::string toString(TagContainerFormat tagContainerFormat) {
		std::string result;
		if (util::hasAnyFormat(tagContainerFormat & TagContainerFormat::ID3v1))
			priv::append(result, "ID3v1"s);
		if (util::hasAnyFormat(tagContainerFormat & TagContainerFormat::ID3v22))
			priv::append(result, "ID3v2.2"s);
		if (util::hasAnyFormat(tagContainerFormat & TagContainerFormat::ID3v23))
			priv::append(result, "ID3v2.3"s);
		if (util::hasAnyFormat(tagContainerFormat & TagContainerFormat::ID3v24))
			priv::append(result, "ID3v2.4"s);
		if (util::hasAnyFormat(tagContainerFormat & TagContainerFormat::APEv1))
			priv::append(result, "APEv1"s);
		if (util::hasAnyFormat(tagContainerFormat & TagContainerFormat::APEv2))
			priv::append(result, "APEv2"s);
        if (util::hasAnyFormat(tagContainerFormat & TagContainerFormat::VorbisComments))
            priv::append(result, "Vorbis Comments"s);
		if (util::hasAnyFormat(tagContainerFormat & TagContainerFormat::FLACPictures))
			priv::append(result, "Flac Pictures"s);
		if (util::hasAnyFormat(tagContainerFormat & TagContainerFormat::ASFMetadata))
			priv::append(result, "ASF Metadata"s);
		if (util::hasAnyFormat(tagContainerFormat & TagContainerFormat::RiffInfo))
			priv::append(result, "Riff Info"s);
		if (util::hasAnyFormat(tagContainerFormat & TagContainerFormat::AiffChunks))
			priv::append(result, "Aiff Chunks"s);
		if (util::hasAnyFormat(tagContainerFormat & TagContainerFormat::MatroskaMetadata))
			priv::append(result, "Matroska Metadata"s);
		if (util::hasAnyFormat(tagContainerFormat & TagContainerFormat::MP4Metadata))
			priv::append(result, "MP4 Metadata"s);

		if (result.empty())
			result = "None"s;

		return result;
	}
}