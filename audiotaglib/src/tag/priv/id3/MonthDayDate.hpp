#pragma once
#include <tag/types/Date.hpp>

namespace tag::priv::id3 {
    class MonthDayDate : public types::Date {
    public:
        MonthDayDate(unsigned month, unsigned day) noexcept;
        bool setMonthDayOnly(unsigned month, unsigned day) noexcept;
    };
}