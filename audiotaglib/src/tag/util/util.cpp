#include "util.hpp"
#include <tag/manager/AudioTagManager.hpp>
namespace fs = std::filesystem;

namespace tag::util {
    AudioTagMap tagMapFrom(const fs::path &filePath, const manager::AudioTagManagerConfiguration &configuration) {
        return manager::ConfigurableAudioTagManager(filePath, configuration).getTagMap();
    }

    void clearTags(const fs::path &filePath, const manager::AudioTagManagerConfiguration &configuration) {
        if (canContainTags(filePath))
            manager::ConfigurableAudioTagManager(filePath, configuration).clearTags();
    }

    void clearTags(const fs::directory_entry &directory, bool recursive,
                   const manager::AudioTagManagerConfiguration &configuration) {
        if (recursive) {
            for (auto &entry : fs::recursive_directory_iterator(directory))
                if (fs::is_regular_file(fs::canonical(entry.path())))
                    clearTags(entry.path());
        } else {
            for (auto &entry : fs::directory_iterator(directory))
                if (fs::is_regular_file(fs::canonical(entry.path())))
                    clearTags(entry.path());
        }
    }

    void copyTags(const fs::path &fileFrom, const fs::path &fileTo,
                  const manager::AudioTagManagerConfiguration &configuration) {
        manager::ConfigurableAudioTagManager(fileFrom, configuration).writeTagsTo(fileTo);
    }
}