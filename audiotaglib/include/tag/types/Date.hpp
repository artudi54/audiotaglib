#pragma once
#include <cstdint>
#include <string>
#include <string_view>

namespace tag::types {

	class Date {
	public:
		explicit Date() noexcept;
        explicit Date(unsigned year)  noexcept;
        explicit Date(unsigned year, unsigned month) noexcept;
        explicit  Date(unsigned year, unsigned month, unsigned day) noexcept;

		static Date parseString(const std::string_view &dateString);

		unsigned getYear() const noexcept;
        unsigned getMonth() const noexcept;
        unsigned getDay() const noexcept;
		
		bool isEmpty() const noexcept;
		bool isYearOnly() const noexcept;
		bool isYearMonthOnly() const noexcept;
		bool isAllSet() const noexcept;

		bool setYearOnly(unsigned year) noexcept;
		bool setYearMonthOnly(unsigned year, unsigned month) noexcept;
		bool setAll(unsigned year, unsigned month, unsigned day) noexcept;

		std::string toYearString() const;
		std::string toString() const;

		bool operator==(const Date &date) const noexcept;
		bool operator!=(const Date &date) const noexcept;
		bool operator<(const Date &date) const noexcept;
		bool operator<=(const Date &date) const noexcept;
		bool operator>(const Date &date) const noexcept;
		bool operator>=(const Date &date) const noexcept;
	protected:
		unsigned year, month, day;
	};

}

