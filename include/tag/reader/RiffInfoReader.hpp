#pragma once

#include <tag/reader/AudioTagReader.hpp>
#include <tag/except/StreamParseException.hpp>
#include <memory>
#include <unordered_map>
#include <regex>

namespace tag::reader {
	class RiffInfoReader : public AudioTagReader {
		virtual AudioTagMap readTag(std::istream &readStream) const;
	};
}