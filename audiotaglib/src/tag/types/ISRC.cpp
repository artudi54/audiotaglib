#include <tag/types/ISRC.hpp>

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
		if (isValid(value)) {
			std::memcpy(isrcBuffer.data(), value.data(), 12);
			isrcBuffer[12] = '\0';
			return true;
		}
		return false;
	}

	bool ISRC::isEmpty() const noexcept {
		return isrcBuffer[0] == '\0';
	}



	bool ISRC::isValid(const std::string_view & value) noexcept {
		if (value.size() != 12)
			return false;
		for (char c : value)
			if (!(c >= '0' && c <= '9') && !(c >= 'A' && c <= 'Z'))
				return false;
		return true;
	}
}