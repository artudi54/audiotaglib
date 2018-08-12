#pragma once
#include <cstdint>
#include <string>

namespace tag::types {

	class Date {
	public:
		Date() noexcept;
		Date(unsigned year)  noexcept;
		Date(unsigned year, unsigned month) noexcept;
		Date(unsigned year, unsigned month, unsigned day) noexcept;

		static Date parseString(const std::string_view &dateString);

		unsigned getYear() const noexcept;
        unsigned getMonth() const noexcept;
        unsigned getDay() const noexcept;
		
		bool isNull() const noexcept;
		bool isYearOnly() const noexcept;
		bool isYearMonthOnly() const noexcept;
		bool isAllSet() const noexcept;

		bool setYearOnly(unsigned year) noexcept;
		bool setYearMonthOnly(unsigned year, unsigned month) noexcept;
		bool setAll(unsigned year, unsigned month, unsigned day) noexcept;

	protected:
		static bool isIntercalary(unsigned year) noexcept;
		unsigned year, month, day;

		static constexpr std::uint8_t MONTH_DAYS[] = {
			31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
		};
	};

}

