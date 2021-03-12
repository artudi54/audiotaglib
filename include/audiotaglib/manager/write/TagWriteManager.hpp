#pragma once
#include <audiotaglib/ContainerFormat.hpp>
#include <audiotaglib/ContainerMetadata.hpp>
#include <audiotaglib/TagMap.hpp>
#include <audiotaglib/config/WriteConfiguration.hpp>

namespace audiotaglib::manager::write {
    // TODO: rename to container_manager
    class TagWriteManager {
    public:
        [[nodiscard]] virtual const std::vector<ContainerFormat>& supportedContainerFormats() const noexcept = 0;
        void write(const TagMap &tagMap, ContainerMetadata &containerMetadata,
                   const config::WriteConfiguration &writeConfiguration = config::WriteConfiguration()) const;
    protected:
        virtual void writeImpl(const TagMap &tagMap, ContainerMetadata &containerMetadata,
                               const config::WriteConfiguration &writeConfiguration) const = 0;
    };
}