#pragma once
#include <string_view>
#include <array>

namespace tag::types {
    class Barcode {
    public:
        explicit Barcode();
        explicit Barcode(const std::string_view &value);
        std::string_view getValue() const noexcept;
        bool setValue(const std::string_view &value) noexcept;
        bool isEmpty() const noexcept;
        std::string toString() const;
    private:
        std::array<char, 14> barcodeBuffer;
    };
}