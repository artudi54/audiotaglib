#include "util.hpp"
#include <tag/manager/AudioTagManager.hpp>
namespace fs = std::filesystem;

namespace tag::util {
    AudioTagMap tagMapFrom(const fs::path &filePath, const config::AudioTagConfiguration &configuration) {
        return manager::ConfigurableAudioTagManager(filePath, configuration).getTagMap();
    }

    void clearTags(const fs::path &filePath, const config::AudioTagConfiguration &configuration) {
        if (canContainTags(filePath))
            manager::ConfigurableAudioTagManager(filePath, configuration).clearTags();
    }

    void clearTags(const fs::directory_entry &directory, bool recursive,
                   const config::AudioTagConfiguration &configuration) {
        if (recursive) {
            for (auto &entry : fs::recursive_directory_iterator(directory))
                if (fs::is_regular_file(fs::canonical(entry.path())))
                    clearTags(entry.path(), configuration);
        } else {
            for (auto &entry : fs::directory_iterator(directory))
                if (fs::is_regular_file(fs::canonical(entry.path())))
                    clearTags(entry.path(), configuration);
        }
    }

    void copyTags(const fs::path &fileFrom, const fs::path &fileTo,
                  const config::AudioTagConfiguration &configuration) {
        manager::ConfigurableAudioTagManager(fileFrom, configuration).writeTagsTo(fileTo);
    }
}