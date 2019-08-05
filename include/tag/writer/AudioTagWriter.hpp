#pragma once
#include <ostream>
#include <tag/config/WriteConfiguration.hpp>
#include <tag/AudioTagMap.hpp>

namespace  tag::writer {
    // TODO: rename ns to tag_writer
    class AudioTagWriter {
    public:
        virtual ~AudioTagWriter() noexcept;
        void writeTag(const AudioTagMap &tagMap, std::ostream &writeStream,
                                  const config::WriteConfiguration &writeConfiguration = config::WriteConfiguration()) const;
        std::uint64_t calculateSize(const AudioTagMap &tagMap,
                                                const config::WriteConfiguration &writeConfiguration = config::WriteConfiguration()) const;

    protected:
        virtual void writeTagImpl(const AudioTagMap &tagMap, std::ostream &writeStream,
                              const config::WriteConfiguration &writeConfiguration) const = 0;
        virtual std::uint64_t calculateSizeImpl(const AudioTagMap &tagMap,
                                            const config::WriteConfiguration &writeConfiguration) const =0;
    };
    using SharedAudioTagWriter=std::shared_ptr<AudioTagWriter>;
}