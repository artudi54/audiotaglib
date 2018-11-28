
#include <tag/writer/AudioTagWriter.hpp>

#include "AudioTagWriter.hpp"

namespace tag::writer {
    AudioTagWriter::~AudioTagWriter() noexcept {}

    void AudioTagWriter::writeTag(const AudioTagMap &tagMap, std::ostream &writeStream,
                                  const config::WriteConfiguration &writeConfiguration) const {
        writeTagImpl(tagMap, writeStream, writeConfiguration);
    }

    std::uint64_t AudioTagWriter::calculateSize(const AudioTagMap &tagMap,
                                                const config::WriteConfiguration &writeConfiguration) const {
        return calculateSizeImpl(tagMap, writeConfiguration);
    }
}