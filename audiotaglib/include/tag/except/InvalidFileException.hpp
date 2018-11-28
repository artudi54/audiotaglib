#pragma once
#include <tag/except/FileException.hpp>

namespace tag::except {
    class InvalidFileException : FileException {
    public:
        InvalidFileException(const std::filesystem::path &filePath, const std::string &cause);
    private:
    };
}