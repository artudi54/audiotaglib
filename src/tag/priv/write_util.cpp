#include "write_util.hpp"

namespace tag::priv {
    void writeUtf8(const std::string_view &str, std::ostream &writeStream, bool nullTerminated) {
        writeStream.write(str.data(), str.size());
        if (nullTerminated)
            writeStream.put('\0');
    }

    void writeUtf8Len(const std::string_view &str, std::ostream &writeStream, std::uint64_t length) {
        std::uint64_t writeLength = std::min(str.size(), length);
        writeStream.write(str.data(), writeLength);
        for (; writeLength < length; ++writeLength)
            writeStream.put('\0');
    }

    void writeNull(std::ostream &writeStream, std::uint64_t count) {
        for (std::uint64_t i = 0; i < count; ++i)
            writeStream.put('\0');
    }
}
