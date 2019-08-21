#pragma once
#include <audiotaglib/except/FileException.hpp>

namespace audiotaglib::except {
    class TagsNotSupportedException : public FileException {
    public:
        explicit TagsNotSupportedException(const std::filesystem::path &filePath);
    };
}
