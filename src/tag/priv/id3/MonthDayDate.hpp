#pragma once
#include <tag/types/Date.hpp>

namespace tag::priv::id3 {
    class MonthDayDate : public types::Date {
    public:
        MonthDayDate(std::uint32_t month, std::uint32_t day) noexcept;
        bool setMonthDayOnly(std::uint32_t month, std::uint32_t day) noexcept;
    };
}