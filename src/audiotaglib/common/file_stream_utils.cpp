#include "file_stream_utils.hpp"
#include <audiotaglib/except/FileNotFoundException.hpp>
#include <audiotaglib/except/FileNotReadableException.hpp>
#include <audiotaglib/except/FileNotWritableException.hpp>

namespace fs = std::filesystem;

namespace audiotaglib::common {
    std::ifstream validInputFileStream(const fs::path &filePath, bool binary) {
        std::error_code dummy;

        if (!fs::exists(filePath, dummy))
            throw except::FileNotFoundException(filePath);

        std::ifstream readStream;
        if (binary)
            readStream.open(filePath, std::ios::in | std::ios::binary);
        else
            readStream.open(filePath, std::ios::in);
        if (!readStream.is_open())
            throw except::FileNotReadableException(filePath);
        readStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        return readStream;
    }

    std::pair<std::ifstream, std::uint64_t> validInputFileStreamWithSize(const fs::path &filePath, bool binary) {
        std::error_code dummy;

        std::uintmax_t size = fs::file_size(filePath, dummy);
        if (size == static_cast<std::uintmax_t>(-1))
            throw except::FileNotReadableException(filePath);

        return { validInputFileStream(filePath, binary), static_cast<std::uint64_t>(size) };
    }

    std::ofstream validOutputFileStream(const fs::path &filePath, bool binary) {
        std::error_code dummy;

        if (!fs::exists(filePath, dummy))
            throw except::FileNotFoundException(filePath);

        std::ofstream writeStream;
        if (binary)
            writeStream.open(filePath, std::ios::out | std::ios::binary);
        else
            writeStream.open(filePath, std::ios::out);
        if (!writeStream.is_open())
            throw except::FileNotWritableException(filePath);
        writeStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        return writeStream;
    }
}