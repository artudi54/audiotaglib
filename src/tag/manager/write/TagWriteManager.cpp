#include "TagWriteManager.hpp"

namespace tag::manager::write {
    void TagWriteManager::write(const tag::TagMap &tagMap, tag::ContainerMetadata &containerMetadata,
                                 const tag::config::WriteConfiguration &writeConfiguration) const {
        writeImpl(tagMap, containerMetadata, writeConfiguration);
    }
}