#pragma once
#include <tag/TagMap.hpp>
#include <tag/ContainerFormat.hpp>
#include <tag/config/FileManagerConfiguration.hpp>

namespace tag::util {
    TagMap tagMapFrom(const std::filesystem::path &filePath,
                           const config::FileManagerConfiguration &configuration = config::FileManagerConfiguration());
    void clearTags(const std::filesystem::path &filePath,
                   const config::FileManagerConfiguration &configuration = config::FileManagerConfiguration());
    void clearTags(const std::filesystem::directory_entry &directory, bool recursive = false,
                   const config::FileManagerConfiguration &configuration = config::FileManagerConfiguration());
    void copyTags(const std::filesystem::path &fileFrom, const std::filesystem::path &fileTo,
                  const config::FileManagerConfiguration &configuration = config::FileManagerConfiguration());
}