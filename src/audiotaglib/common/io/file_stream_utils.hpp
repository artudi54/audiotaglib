#pragma once
#include <filesystem>
#include <fstream>

namespace audiotaglib::common {
    std::ifstream validInputFileStream(const std::filesystem::path &filePath, bool binary = true, bool exceptions = true);
    std::ifstream validInputFileStreamWithCreation(const std::filesystem::path &filePath, bool binary = true, bool exceptions = true);
    std::pair<std::ifstream, std::uint64_t> validInputFileStreamWithSize(const std::filesystem::path &filePath, bool binary = true, bool exceptions = true);

    std::ofstream validOutputFileStream(const std::filesystem::path &filePath, bool binary = true, bool exceptions = true);
}