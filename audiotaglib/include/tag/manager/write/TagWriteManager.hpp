#pragma once
#include <tag/AudioContainerFormat.hpp>
#include <tag/AudioFileInformation.hpp>
#include <tag/AudioTagMap.hpp>
#include <tag/config/WriteConfiguration.hpp>

namespace tag::manager::write {
    class TagWriteManager {
    public:
        virtual const std::vector<AudioContainerFormat>& supportedContainerFormats() const noexcept = 0;
        void write(const AudioTagMap &tagMap, AudioFileInformation &fileInformation,
                   const config::WriteConfiguration &writeConfiguration = config::WriteConfiguration()) const;
    protected:
        virtual void writeImpl(const AudioTagMap &tagMap, AudioFileInformation &fileInformation,
                               const config::WriteConfiguration &writeConfiguration) const = 0;
    };
    using SharedTagWriteManager = std::shared_ptr<TagWriteManager>;
}