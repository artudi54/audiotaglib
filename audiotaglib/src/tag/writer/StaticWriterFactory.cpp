#include "StaticWriterFactory.hpp"

namespace tag::writer {

    SharedAudioTagWriter StaticWriterFactory::getWriter(AudioTagFormat format) {
        return tag::writer::SharedAudioTagWriter();
    }
}