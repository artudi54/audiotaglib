#pragma once
#include <tag/TagMap.hpp>
#include <tag/ContainerFormat.hpp>
#include <tag/config/Configuration.hpp>

namespace tag::util {
    TagMap tagMapFrom(const std::filesystem::path &filePath,
                           const config::Configuration &configuration = config::Configuration());
    void clearTags(const std::filesystem::path &filePath,
                   const config::Configuration &configuration = config::Configuration());
    void clearTags(const std::filesystem::directory_entry &directory, bool recursive = false,
                   const config::Configuration &configuration = config::Configuration());
    void copyTags(const std::filesystem::path &fileFrom, const std::filesystem::path &fileTo,
                  const config::Configuration &configuration = config::Configuration());
}