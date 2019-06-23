#include "TagWriteManager.hpp"

namespace tag::manager::write {
    void TagWriteManager::write(const tag::AudioTagMap &tagMap, tag::AudioFileInformation &fileInformation,
                                 const tag::config::WriteConfiguration &writeConfiguration) const {
        writeImpl(tagMap, fileInformation, writeConfiguration);
    }
}
