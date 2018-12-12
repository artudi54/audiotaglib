#include "MonthDayDate.hpp"
#include <array>

namespace tag::priv::id3 {
    MonthDayDate::MonthDayDate(std::uint32_t month, std::uint32_t day) noexcept
            : Date() {
        setMonthDayOnly(month, day);
    }

    bool MonthDayDate::setMonthDayOnly(std::uint32_t month, std::uint32_t day) noexcept {
        //todo: FIXME
        this->year = 0;
        this->month = month;
        this->day = day;
        return true;
    }
}