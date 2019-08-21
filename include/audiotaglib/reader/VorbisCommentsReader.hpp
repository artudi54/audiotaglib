#pragma once
#include <audiotaglib/reader/AudioTagReader.hpp>
#include <audiotaglib/except/StreamParseException.hpp>

namespace audiotaglib::reader {
    class VorbisCommentsReader : public AudioTagReader {
    public:
        virtual TagMap readTag(std::istream &readStream) const override;
    };
}