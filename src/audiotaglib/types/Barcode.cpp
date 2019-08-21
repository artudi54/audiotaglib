#include "Barcode.hpp"
#include <cstring>


namespace audiotaglib::priv {
    static bool isValid(const std::string_view & value) noexcept {
        auto size = value.size();
        if (value.size() != 12 && value.size() != 13)
            return false;
        for (char c : value)
            if (c < '0' || c > '9')
                return false;
        return true;
    }
}

namespace audiotaglib::types {

    Barcode::Barcode()
        : barcodeBuffer{} {}

    Barcode::Barcode(const std::string_view &value)
        : Barcode() {
        setValue(value);
    }

    std::string_view Barcode::getValue() const noexcept {
        return std::string_view(barcodeBuffer.data());
    }

    bool Barcode::setValue(const std::string_view &value) noexcept {
        if (priv::isValid(value)) {
            std::memcpy(barcodeBuffer.data(), value.data(), value.size());
            barcodeBuffer[value.size()] = '\0';
            return true;
        }
        return false;
    }

    bool Barcode::isEmpty() const noexcept {
        return barcodeBuffer[0] == '\0';
    }

    std::string Barcode::toString() const {
        return std::string(barcodeBuffer.data());
    }

    bool Barcode::operator==(const Barcode &other) const {
        return std::string_view(barcodeBuffer.data()) == std::string_view(other.barcodeBuffer.data());
    }

    bool Barcode::operator!=(const Barcode &other) const {
        return !(*this == other);
    }
}