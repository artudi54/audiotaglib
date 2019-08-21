#pragma once
#include <cstdint>
#include <string>
#include <string_view>

namespace audiotaglib::types {

	class Date {
	public:
		explicit Date() noexcept;
        explicit Date(std::uint32_t year)  noexcept;
        explicit Date(std::uint32_t year, std::uint32_t month) noexcept;
        explicit Date(std::uint32_t year, std::uint32_t month, std::uint32_t day) noexcept;

		static Date parseString(const std::string_view &dateString);

		std::uint32_t getYear() const noexcept;
        std::uint32_t getMonth() const noexcept;
        std::uint32_t getDay() const noexcept;
		
		bool isEmpty() const noexcept;
		bool isYearOnly() const noexcept;
		bool isYearMonthOnly() const noexcept;
		bool isAllSet() const noexcept;

		bool setYearOnly(std::uint32_t year) noexcept;
		bool setYearMonthOnly(std::uint32_t year, std::uint32_t month) noexcept;
		bool setAll(std::uint32_t year, std::uint32_t month, std::uint32_t day) noexcept;

		std::string toYearString() const;
		std::string toString() const;

		bool operator==(const Date &date) const noexcept;
		bool operator!=(const Date &date) const noexcept;
		bool operator<(const Date &date) const noexcept;
		bool operator<=(const Date &date) const noexcept;
		bool operator>(const Date &date) const noexcept;
		bool operator>=(const Date &date) const noexcept;
	protected:
		std::uint32_t year, month, day;
	};

}

