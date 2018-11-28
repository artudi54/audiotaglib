#include <tag/types/ISRC.hpp>
#include <cstring>
using namespace std::literals;

namespace tag::priv {
    static bool isValid(const std::string_view & value) noexcept {
        if (value.size() != 12)
            return false;
        for (char c : value)
            if (!(c >= '0' && c <= '9') && !(c >= 'A' && c <= 'Z'))
                return false;
        return true;
    }
}

namespace tag::types {
	ISRC::ISRC() noexcept
		: isrcBuffer{} {}

	ISRC::ISRC(const std::string_view & isrc) noexcept
		: ISRC() {
		setValue(isrc);
	}


	std::string_view ISRC::getValue() const noexcept {
		return std::string_view(isrcBuffer.data());
	}

	bool ISRC::setValue(const std::string_view & value) noexcept {
		if (priv::isValid(value)) {
			std::memcpy(isrcBuffer.data(), value.data(), 12);
			isrcBuffer[12] = '\0';
			return true;
		}
		return false;
	}

	bool ISRC::isEmpty() const noexcept {
		return isrcBuffer[0] == '\0';
	}

    std::string ISRC::toString() const {
        return std::string(isrcBuffer.data());
    }
}

namespace tag::string {
    std::string toString(types::ISRC isrc) {
        return isrc.toString();
    }
}