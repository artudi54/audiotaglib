#include "StaticWriterFactory.hpp"

namespace audiotaglib::writer {

    SharedAudioTagWriter StaticWriterFactory::getWriter(TagContainerFormat format) {
        return audiotaglib::writer::SharedAudioTagWriter();
    }
}