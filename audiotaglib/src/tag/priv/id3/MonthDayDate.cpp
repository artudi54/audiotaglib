#include "MonthDayDate.hpp"
#include <array>

namespace tag::priv::id3 {
    MonthDayDate::MonthDayDate(unsigned month, unsigned day) noexcept
            : Date() {
        setMonthDayOnly(month, day);
    }

    bool MonthDayDate::setMonthDayOnly(unsigned month, unsigned day) noexcept {
        //todo: FIXME
        this->year = 0;
        this->month = month;
        this->day = day;
        return true;
    }
}