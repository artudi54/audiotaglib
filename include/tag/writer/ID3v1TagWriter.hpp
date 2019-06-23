#pragma once
#include <tag/writer/AudioTagWriter.hpp>

namespace tag::writer {
    class ID3v1TagWriter : public AudioTagWriter {
    protected:
        virtual void writeTagImpl(const AudioTagMap &tagMap, std::ostream &writeStream,
                                  const config::WriteConfiguration &writeConfiguration) const override;
        virtual std::uint64_t calculateSizeImpl(const AudioTagMap &tagMap,
                                                const config::WriteConfiguration &writeConfiguration) const override;
    };
}