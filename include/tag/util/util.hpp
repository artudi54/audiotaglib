#pragma once
#include <tag/AudioTagMap.hpp>
#include <tag/ContainerFormat.hpp>
#include <tag/config/AudioTagConfiguration.hpp>

namespace tag::util {
    AudioTagMap tagMapFrom(const std::filesystem::path &filePath,
                           const config::AudioTagConfiguration &configuration = config::AudioTagConfiguration());
    void clearTags(const std::filesystem::path &filePath,
                   const config::AudioTagConfiguration &configuration = config::AudioTagConfiguration());
    void clearTags(const std::filesystem::directory_entry &directory, bool recursive = false,
                   const config::AudioTagConfiguration &configuration = config::AudioTagConfiguration());
    void copyTags(const std::filesystem::path &fileFrom, const std::filesystem::path &fileTo,
                  const config::AudioTagConfiguration &configuration = config::AudioTagConfiguration());
}