#include "util.hpp"
#include <audiotaglib/FileManager.hpp>
namespace fs = std::filesystem;

namespace audiotaglib::util {
    TagMap tagMapFrom(const fs::path &filePath, const config::Configuration &configuration) {
        return ConfigurableFileManager(filePath, configuration).getTagMap();
    }

    void clearTags(const fs::path &filePath, const config::Configuration &configuration) {
        if (canContainTags(filePath))
            ConfigurableFileManager(filePath, configuration).clearTags();
    }

    void clearTags(const fs::directory_entry &directory, bool recursive,
                   const config::Configuration &configuration) {
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
                  const config::Configuration &configuration) {
        ConfigurableFileManager(fileFrom, configuration).writeTagsTo(fileTo);
    }
}