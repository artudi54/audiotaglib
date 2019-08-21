#pragma once
#include <audiotaglib/reader/AudioTagReader.hpp>
#include <audiotaglib/except/StreamParseException.hpp>


namespace audiotaglib::reader {
	class ASFMetadataReader : public AudioTagReader {
	public:
		virtual TagMap readTag(std::istream &readStream) const override;
	private:
		void processHeader(TagMap &map, std::istream &readStream, std::uint64_t size, std::uint32_t objectsNumber) const;
		void processContentDescription(TagMap &map, std::istream &readStream, std::uint64_t size) const;
		void processExtendedContentDescription(TagMap &map, std::istream &readStream, std::uint64_t size) const;
	};
}