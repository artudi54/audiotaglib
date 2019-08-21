#pragma once
#include <audiotaglib/reader/AudioTagReader.hpp>
#include <audiotaglib/except/StreamParseException.hpp>
#include <memory>
#include <unordered_map>
#include <regex>

namespace audiotaglib::reader {
	class RiffInfoReader : public AudioTagReader {
		virtual TagMap readTag(std::istream &readStream) const;
	};
}