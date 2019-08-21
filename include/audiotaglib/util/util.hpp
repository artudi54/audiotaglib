#pragma once
#include <audiotaglib/TagMap.hpp>
#include <audiotaglib/ContainerFormat.hpp>
#include <audiotaglib/config/Configuration.hpp>

namespace audiotaglib::util {
    TagMap tagMapFrom(const std::filesystem::path &filePath,
                           const config::Configuration &configuration = config::Configuration());
    void clearTags(const std::filesystem::path &filePath,
                   const config::Configuration &configuration = config::Configuration());
    void clearTags(const std::filesystem::directory_entry &directory, bool recursive = false,
                   const config::Configuration &configuration = config::Configuration());
    void copyTags(const std::filesystem::path &fileFrom, const std::filesystem::path &fileTo,
                  const config::Configuration &configuration = config::Configuration());
}