#pragma once
#include <audiotaglib/TagContainerFormat.hpp>
#include <audiotaglib/writer/AudioTagWriter.hpp>

namespace audiotaglib::writer {
    class StaticWriterFactory {
    public:
        static SharedAudioTagWriter getWriter(TagContainerFormat format);
    };
}