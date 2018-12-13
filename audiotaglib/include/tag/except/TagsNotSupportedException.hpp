#pragma once
#include <FileException.hpp>

namespace tag::except {
    class TagsNotSupportedException : public FileException {
    public:
        explicit TagsNotSupportedException(const std::filesystem::path &filePath);
    };
}
