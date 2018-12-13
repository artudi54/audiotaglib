#pragma once
#include <tag/AudioTagFormat.hpp>
#include <tag/writer/AudioTagWriter.hpp>

namespace tag::writer {
    class StaticWriterFactory {
    public:
        static SharedAudioTagWriter getWriter(AudioTagFormat format);
    };
}