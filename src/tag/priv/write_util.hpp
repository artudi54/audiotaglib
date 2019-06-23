#pragma once
#include <string>
#include <string_view>
#include <ostream>
#include <tag/priv/headers.hpp>

namespace tag::priv {
    template < std::size_t N >
    inline void writeHeader(const ByteArray<N> &header, std::ostream &writeStream) {
        writeStream.write(reinterpret_cast<const char*>(header.data()), header.size());
    }

    void writeNull(std::ostream &writeStream, std::uint64_t count = 1);

    void writeUtf8(const std::string_view &str, std::ostream &writeStream, bool nullTerminated = true);
    void writeUtf8Len(const std::string_view &str, std::ostream &writeStream, std::uint64_t length);
}