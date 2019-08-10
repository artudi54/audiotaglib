#pragma once
#include <tag/reader/AudioTagReader.hpp>
#include <tag/except/StreamParseException.hpp>


namespace tag::reader {
	class ASFMetadataReader : public AudioTagReader {
	public:
		virtual TagMap readTag(std::istream &readStream) const override;
	private:
		void processHeader(TagMap &map, std::istream &readStream, std::uint64_t size, std::uint32_t objectsNumber) const;
		void processContentDescription(TagMap &map, std::istream &readStream, std::uint64_t size) const;
		void processExtendedContentDescription(TagMap &map, std::istream &readStream, std::uint64_t size) const;
	};
}