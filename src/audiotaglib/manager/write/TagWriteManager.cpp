#include "TagWriteManager.hpp"

namespace audiotaglib::manager::write {
    void TagWriteManager::write(const audiotaglib::TagMap &tagMap, audiotaglib::ContainerMetadata &containerMetadata,
                                const audiotaglib::config::WriteConfiguration &writeConfiguration) const {
        writeImpl(tagMap, containerMetadata, writeConfiguration);
    }
}
