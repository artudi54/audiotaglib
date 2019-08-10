#include "StaticWriterFactory.hpp"

namespace tag::writer {

    SharedAudioTagWriter StaticWriterFactory::getWriter(TagContainerFormat format) {
        return tag::writer::SharedAudioTagWriter();
    }
}