#include "TagsNotSupportedException.hpp"
using namespace std::literals;
namespace fs = std::filesystem;

namespace audiotaglib::except {

    TagsNotSupportedException::TagsNotSupportedException(const fs::path &filePath)
        : FileException(filePath, "File \""s + filePath.string() +"\" does not support audio tags"s) {}
}