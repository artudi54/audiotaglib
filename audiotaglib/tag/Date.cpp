#include "Date.hpp"

namespace tag::type {
	Date::Date(unsigned year) noexcept
		: year(0), month(0), day(0) {
		setYearOnly(year);
	}

	Date::Date(unsigned year, std::uint8_t month) noexcept
		: year(0), month(0), day(0) {
		setYearMonthOnly(year, month);
	}

	Date::Date(std::uint8_t month, std::uint8_t day) noexcept
		: year(0), month(0), day(0) {
		setMonthDayOnly(month, day);
	}

	Date::Date(unsigned year, std::uint8_t month, std::uint8_t day) noexcept
		: year(0), month(0), day(0) {
		setAll(year, month, day);
	}
	





	unsigned Date::getYear() const noexcept {
		return year;
	}

	std::uint8_t Date::getMonth() const noexcept {
		return month;
	}

	std::uint8_t Date::getDay() const noexcept {
		return day;
	}





	bool Date::isNull() const noexcept {
		return year == 0 && month == 0 && day == 0;
	}

	bool Date::isYearOnly() const noexcept {
		return year != 0 && month == 0 && day == 0;
	}

	bool Date::isYearMonthOnly() const noexcept {
		return year != 0 && month != 0 && day == 0;
	}

	bool Date::isMonthDayOnly() const noexcept {
		return year == 0 && month != 0 && day != 0;
	}

	bool Date::isAllSet() const noexcept {
		return year != 0 && month != 0 && day != 0;
	}







	bool Date::setYearOnly(unsigned year) noexcept {
		if (year >= 1000 && year <= 9999) {
			this->year = year;
			month = day = 0;
			return true;
		}
		return false;
	}

	bool Date::setYearMonthOnly(unsigned year, std::uint8_t month) noexcept {
		if (month == 0 || day == 0 || month > 12) {
			this->year = this->month = this->day = 0;
			return false;
		}
		this->year = year;
		this->month = month;
		this->day = 0;
		return true;
	}

	bool Date::setMonthDayOnly(std::uint8_t month, std::uint8_t day) noexcept {
		if (month == 0 || day == 0 || month > 12 && day > MONTH_DAYS[month - 1]) {
			this->year = this->month = this->day = 0;
			return false;
		}
		this->year = 0;
		this->month = month;
		this->day = day;
		return true;
	}


	bool Date::setAll(unsigned year, std::uint8_t month, std::uint8_t day) noexcept {

		if (year == 0 || month == 0 || day == 0) {
			this->year = this->month = this->day = 0;
			return false;
		}

		if (year >= 1000 && year <= 9999 && month <= 12 && day <= MONTH_DAYS[month - 1]
			&& (month != 2 || day != 29 || isIntercalary(year))
			) {
			this->year = year;
			this->month = month;
			this->day = day;
			return true;
		} else
			return false;
	}




	bool Date::isIntercalary(unsigned year) noexcept {
		return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
	}
}
