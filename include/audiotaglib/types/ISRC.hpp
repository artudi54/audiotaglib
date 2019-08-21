#pragma once
#include <array>
#include <string_view>

namespace audiotaglib::types {
	class ISRC {
	public:
		explicit ISRC() noexcept;
		explicit ISRC(const std::string_view &value) noexcept;
		std::string_view getValue() const noexcept;
		bool setValue(const std::string_view &value) noexcept;
		bool isEmpty() const noexcept;
		std::string toString() const;
        bool operator==(const ISRC &other) const;
        bool operator!=(const ISRC &other) const;
	private:
		std::array<char, 13> isrcBuffer;
	};
}

namespace audiotaglib::string {
    std::string toString(types::ISRC isrc);
}
