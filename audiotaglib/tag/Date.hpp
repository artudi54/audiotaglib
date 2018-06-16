#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

namespace tag::type {

	class Date {
	public:
		Date() noexcept;
		Date(unsigned year)  noexcept;
		Date(unsigned year, std::uint8_t month) noexcept;
		Date(std::uint8_t month, std::uint8_t day) noexcept;
		Date(unsigned year, std::uint8_t month, std::uint8_t day) noexcept;

		static Date parseString(const std::string_view &dateString);

		unsigned getYear() const noexcept;
		std::uint8_t getMonth() const noexcept;
		std::uint8_t getDay() const noexcept;
		
		bool isNull() const noexcept;
		bool isYearOnly() const noexcept;
		bool isYearMonthOnly() const noexcept;
		bool isMonthDayOnly() const noexcept;
		bool isAllSet() const noexcept;

		bool setYearOnly(unsigned year) noexcept;
		bool setYearMonthOnly(unsigned year, std::uint8_t month) noexcept;
		bool setMonthDayOnly(std::uint8_t month, std::uint8_t day) noexcept;
		bool setAll(unsigned year, std::uint8_t month, std::uint8_t day) noexcept;

	private:
		static bool isIntercalary(unsigned year) noexcept;
		unsigned year;
		std::uint8_t month, day;

		static constexpr std::uint8_t MONTH_DAYS[] = {
			31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
		};
	};

}

