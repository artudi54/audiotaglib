#pragma once
#include <tag/reader/AudioTagReader.hpp>
#include <tag/except/StreamParseException.hpp>


namespace tag::reader {
	class ASFMetadataReader : public AudioTagReader {
	public:
		virtual AudioTagMap readTag(std::istream &readStream) const override;
	private:
		void processHeader(AudioTagMap &map, std::istream &readStream, std::uint64_t size, std::uint32_t objectsNumber) const;
		void processContentDescription(AudioTagMap &map, std::istream &readStream, std::uint64_t size) const;
		void processExtendedContentDescription(AudioTagMap &map, std::istream &readStream, std::uint64_t size) const;
	};
}