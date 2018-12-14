#pragma once
#include <tag/AudioTagMap.hpp>
#include <tag/AudioContainerFormat.hpp>
#include <tag/manager/AudioTagManagerConfiguration.hpp>

namespace tag::util {
    AudioTagMap tagMapFrom(const std::filesystem::path &filePath,
                           const manager::AudioTagManagerConfiguration &configuration = manager::AudioTagManagerConfiguration());
    void clearTags(const std::filesystem::path &filePath,
                   const manager::AudioTagManagerConfiguration &configuration = manager::AudioTagManagerConfiguration());
    void clearTags(const std::filesystem::directory_entry &directory, bool recursive = false,
                   const manager::AudioTagManagerConfiguration &configuration = manager::AudioTagManagerConfiguration());
    void copyTags(const std::filesystem::path &fileFrom, const std::filesystem::path &fileTo,
                  const manager::AudioTagManagerConfiguration &configuration = manager::AudioTagManagerConfiguration());
}