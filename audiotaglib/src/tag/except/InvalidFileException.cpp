#include "InvalidFileException.hpp"
using namespace std::literals;

namespace tag::except {
    tag::except::InvalidFileException::InvalidFileException(const std::filesystem::path &filePath,
                                                            const std::string &cause)
        : FileException(filePath, "File \"" + filePath.filename().string() + "\" is invalid: "s + cause) {
        int i = 2;
        i +=2;
    }
}
