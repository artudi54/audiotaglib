#pragma once
#include <cstdint>
#include <istream>
#include <ostream>
#include <audiotaglib/common/ReadStream.hpp>

namespace audiotaglib::common {
    template < class T >
    class GenericHeader {
        [[nodiscard]] std::uint32_t getHeaderSize() const {
            return static_cast<const T*>(this)->getHeaderSize();
        }

        [[nodiscard]] std::uint64_t getDataSize() const {
            return static_cast<const T*>(this)->getDataSize();
        }

        static T readHeader(ReadStream &readStream) {
            return T::readHeader(readStream);
        }
    };
}