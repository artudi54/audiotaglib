#pragma once
#include <tag/ContainerFormat.hpp>
#include <tag/ContainerMetadata.hpp>
#include <tag/AudioTagMap.hpp>
#include <tag/config/WriteConfiguration.hpp>

namespace tag::manager::write {
    // TODO: rename to container_manager
    class TagWriteManager {
    public:
        virtual const std::vector<ContainerFormat>& supportedContainerFormats() const noexcept = 0;
        void write(const AudioTagMap &tagMap, ContainerMetadata &containerMetadata,
                   const config::WriteConfiguration &writeConfiguration = config::WriteConfiguration()) const;
    protected:
        virtual void writeImpl(const AudioTagMap &tagMap, ContainerMetadata &containerMetadata,
                               const config::WriteConfiguration &writeConfiguration) const = 0;
    };
}