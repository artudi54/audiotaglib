#pragma once
#include <array>
#include <string_view>
#include <string>

namespace audiotaglib::types {
    class Barcode {
    public:
        explicit Barcode();
        explicit Barcode(const std::string_view &value);
        std::string_view getValue() const noexcept;
        bool setValue(const std::string_view &value) noexcept;
        bool isEmpty() const noexcept;
        std::string toString() const;
        bool operator==(const Barcode &other) const;
        bool operator!=(const Barcode &other) const;
    private:
        std::array<char, 14> barcodeBuffer;
    };
}