#pragma once
#include <audiotaglib/writer/AudioTagWriter.hpp>

namespace audiotaglib::writer {
    class ID3v1TagWriter : public AudioTagWriter {
    protected:
        virtual void writeTagImpl(const TagMap &tagMap, std::ostream &writeStream,
                                  const config::WriteConfiguration &writeConfiguration) const override;
        virtual std::uint64_t calculateSizeImpl(const TagMap &tagMap,
                                                const config::WriteConfiguration &writeConfiguration) const override;
    };
}