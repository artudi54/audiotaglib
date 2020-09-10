#include "file_stream_utils.hpp"
#include <audiotaglib/except/FileNotFoundException.hpp>
#include <audiotaglib/except/FileNotReadableException.hpp>
#include <audiotaglib/except/FileNotWritableException.hpp>

namespace fs = std::filesystem;

namespace audiotaglib::common {
    std::ifstream validInputFileStream(const fs::path &filePath, bool binary, bool exceptions) {
        std::error_code dummy;

        if (!fs::exists(filePath, dummy))
            throw except::FileNotFoundException(filePath);

        std::ios::openmode openMode = binary ? std::ios::in | std::ios::binary : std::ios::in;
        std::ifstream readStream(filePath, openMode);
        if (!readStream.is_open())
            throw except::FileNotReadableException(filePath);
        if (exceptions)
            readStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        return readStream;
    }

    std::ifstream validInputFileStreamWithCreation(const std::filesystem::path &filePath, bool binary, bool exceptions) {
        std::error_code dummy;

        std::ios::openmode openMode = binary ? std::ios::in | std::ios::binary : std::ios::in;
        std::ifstream readStream(filePath, openMode);
        if (!readStream.is_open())
            readStream.open(filePath, openMode | std::ios::out | std::ios::trunc);
        if (!readStream.is_open())
            throw except::FileNotReadableException(filePath);
        if (exceptions)
            readStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        return readStream;
    }

    std::pair<std::ifstream, std::uint64_t> validInputFileStreamWithSize(const fs::path &filePath, bool binary, bool exceptions) {
        std::error_code dummy;

        std::uintmax_t size = fs::file_size(filePath, dummy);
        if (size == static_cast<std::uintmax_t>(-1))
            throw except::FileNotReadableException(filePath);

        return { validInputFileStream(filePath, binary, exceptions), static_cast<std::uint64_t>(size) };
    }

    std::ofstream validOutputFileStream(const fs::path &filePath, bool binary, bool exceptions) {
        std::error_code dummy;

        if (!fs::exists(filePath, dummy))
            throw except::FileNotFoundException(filePath);

        std::ios::openmode openMode = binary ? std::ios::out | std::ios::binary : std::ios::out;
        std::ofstream writeStream(filePath, openMode);
        if (!writeStream.is_open())
            throw except::FileNotWritableException(filePath);
        if (exceptions)
            writeStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        return writeStream;
    }
}