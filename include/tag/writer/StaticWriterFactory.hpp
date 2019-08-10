#pragma once
#include <tag/TagContainerFormat.hpp>
#include <tag/writer/AudioTagWriter.hpp>

namespace tag::writer {
    class StaticWriterFactory {
    public:
        static SharedAudioTagWriter getWriter(TagContainerFormat format);
    };
}