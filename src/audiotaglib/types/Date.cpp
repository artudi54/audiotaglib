#include "Date.hpp"
#include <vector>
#include <sstream>
#include <iomanip>
#include <array>
#include <boost/algorithm/string.hpp>
using namespace std::literals;

namespace audiotaglib::priv {
    bool isIntercalary(std::uint32_t year) noexcept {
        return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
    }
    bool isYearValid(std::uint32_t year) noexcept {
        return year >= 1000 && year <= 9999;
    }

    bool isMonthValid(std::uint32_t month) noexcept {
        return month >= 1 && month <= 12;
    }

    bool isYearMonthDayValid(std::uint32_t year, std::uint32_t month, std::uint32_t day) noexcept {
        static constexpr std::array<std::uint8_t, 12> MONTH_DAYS = {
                31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
        };
        if (!isYearValid(year) || !isMonthValid(month))
            return false;
        if (month == 2 && day == 29 && isIntercalary(year))
            return true;
        return day > 0 && day <= MONTH_DAYS[month - 1];
    }
}

namespace audiotaglib::types {
	Date::Date() noexcept
		: year(0), month(0), day(0) {}

	Date::Date(std::uint32_t year) noexcept
		: year(0), month(0), day(0) {
		setYearOnly(year);
	}

	Date::Date(std::uint32_t year, std::uint32_t month) noexcept
		: year(0), month(0), day(0) {
		setYearMonthOnly(year, month);
	}

	Date::Date(std::uint32_t year, std::uint32_t month, std::uint32_t day) noexcept
		: year(0), month(0), day(0) {
		setAll(year, month, day);
	}


	Date Date::parseString(const std::string_view & dateString) {
		std::vector<std::string> splitted;
		types::Date date;

		splitted.reserve(3);
		boost::split(splitted, dateString, boost::is_any_of("- :"s), boost::token_compress_on);

		if (splitted.empty() || splitted.front().size() != 4)
			return date;

		try {
			if (splitted.size() == 1)
				date.setYearOnly(static_cast<std::uint32_t>(std::stol(splitted[0])));
			else if (splitted.size() == 2)
				date.setYearMonthOnly(
					static_cast<std::uint32_t>(std::stoul(splitted[0])),
					static_cast<std::uint32_t>(std::stoul(splitted[1]))
				);
			else if (splitted.size() >= 3)
				date.setAll(
					static_cast<std::uint32_t>(std::stoul(splitted[0])),
					static_cast<std::uint32_t>(std::stoul(splitted[1])),
					static_cast<std::uint32_t>(std::stoul(splitted[2]))
				);
		}
		catch (std::logic_error &) {}

		return date;
	}


	std::uint32_t Date::getYear() const noexcept {
		return year;
	}

    std::uint32_t Date::getMonth() const noexcept {
		return month;
	}

    std::uint32_t Date::getDay() const noexcept {
		return day;
	}


	bool Date::isEmpty() const noexcept {
		return year == 0 && month == 0 && day == 0;
	}

	bool Date::isYearOnly() const noexcept {
		return year != 0 && month == 0 && day == 0;
	}

	bool Date::isYearMonthOnly() const noexcept {
		return year != 0 && month != 0 && day == 0;
	}

	bool Date::isAllSet() const noexcept {
		return year != 0 && month != 0 && day != 0;
	}


	bool Date::setYearOnly(std::uint32_t year) noexcept {
		if (priv::isYearValid(year)) {
		    this->year = year;
		    return true;
		}
		return false;
	}

	bool Date::setYearMonthOnly(std::uint32_t year, std::uint32_t month) noexcept {
		if (priv::isYearValid(year) && priv::isMonthValid(month)) {
            this->year = year;
            this->month = month;
            this->day = 0;
            return true;
        }
        return false;
	}

	bool Date::setAll(std::uint32_t year, std::uint32_t month, std::uint32_t day) noexcept {
		if (year == 0 && month == 0 && day == 0) {
			this->year = this->month = this->day = 0;
			return true;
		}
		if (priv::isYearMonthDayValid(year, month, day)) {
		    this->year = year;
		    this->month = month;
		    this->day = day;
		    return true;
		}
		return false;
	}


    std::string Date::toYearString() const {
        if (year != 0)
            return std::to_string(year);
        return std::string();
    }

    std::string Date::toString() const {
        if (isEmpty())
            return std::string();
        std::stringstream dateStream;
        dateStream << year;
        if (month != 0)
            dateStream << '-' <<  std::setw(2) << std::setfill('0') << month;
        if (day != 0)
            dateStream << '-' <<  std::setw(2) << std::setfill('0') << day;
        return dateStream.str();
    }

    bool Date::operator==(const Date &date) const noexcept {
        return std::tie(year, month, day) == std::tie(date.year, date.month, date.day);
    }

    bool Date::operator!=(const Date &date) const noexcept {
        return !(*this == date);
    }

    bool Date::operator<(const Date &date) const noexcept {
        return std::tie(year, month, day) < std::tie(date.year, date.month, date.day);
    }

    bool Date::operator<=(const Date &date) const noexcept {
        return !(date < *this);
    }

    bool Date::operator>(const Date &date) const noexcept {
        return (date < *this);
    }

    bool Date::operator>=(const Date &date) const noexcept {
        return !(*this < date);
    }
}
