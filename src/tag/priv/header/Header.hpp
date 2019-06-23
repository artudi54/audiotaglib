#pragma once
#include <cstdint>
#include <istream>
#include <ostream>

namespace tag::priv::headers {
    template < class T >
    class Header {
        std::uint32_t headerSize() const {
            return static_cast<const T*>(this)->headerSize();
        }

        std::uint64_t dataSize() const {
            return static_cast<const T*>(this)->dataSize();
        }

        void writeHeader(std::ostream &writeStream) const {
            static_cast<const T*>(this)->writeHeader(writeStream);
        }

        static void readHeader(std::istream &readStream) {
            return T::readHeader(readStream);
        }
    };
}