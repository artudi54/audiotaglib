#pragma once
#include <ostream>
#include <audiotaglib/config/WriteConfiguration.hpp>
#include <audiotaglib/TagMap.hpp>

namespace  audiotaglib::writer {
    // TODO: rename ns to tag_writer
    class AudioTagWriter {
    public:
        virtual ~AudioTagWriter() noexcept;
        void writeTag(const TagMap &tagMap, std::ostream &writeStream,
                                  const config::WriteConfiguration &writeConfiguration = config::WriteConfiguration()) const;
        std::uint64_t calculateSize(const TagMap &tagMap,
                                                const config::WriteConfiguration &writeConfiguration = config::WriteConfiguration()) const;

    protected:
        virtual void writeTagImpl(const TagMap &tagMap, std::ostream &writeStream,
                              const config::WriteConfiguration &writeConfiguration) const = 0;
        virtual std::uint64_t calculateSizeImpl(const TagMap &tagMap,
                                            const config::WriteConfiguration &writeConfiguration) const =0;
    };
    using SharedAudioTagWriter=std::shared_ptr<AudioTagWriter>;
}