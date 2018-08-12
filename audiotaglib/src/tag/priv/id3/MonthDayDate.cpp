#include "MonthDayDate.hpp"

namespace tag::priv::id3 {
    MonthDayDate::MonthDayDate(unsigned month, unsigned day) noexcept
            : Date() {
        setMonthDayOnly(month, day);
    }


    bool MonthDayDate::setMonthDayOnly(unsigned month, unsigned day) noexcept {
        if (month == 0 || day == 0 || month > 12 || day > MONTH_DAYS[month - 1]) {
            this->year = this->month = this->day = 0;
            return false;
        }
        this->year = 0;
        this->month = month;
        this->day = day;
        return true;
    }
}