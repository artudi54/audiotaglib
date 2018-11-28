#pragma once
#include <array>
#include <string_view>
#include <cstring>

namespace tag::types {
	class ISRC {
	public:
		explicit ISRC() noexcept;
		explicit ISRC(const std::string_view &value) noexcept;
		std::string_view getValue() const noexcept;
		bool setValue(const std::string_view &isrc) noexcept;
		bool isEmpty() const noexcept;
		std::string toString() const;
	private:
		static bool isValid(const std::string_view &isrc) noexcept;

		std::array<char, 13> isrcBuffer;
	};
}
