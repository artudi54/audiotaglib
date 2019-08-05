#include <boost/test/unit_test.hpp>
#include <tag/types/Date.hpp>
#include <array>
using namespace std::literals;

BOOST_AUTO_TEST_SUITE(Date)

BOOST_AUTO_TEST_CASE(Comparison) {
    // given
    tag::types::Date date1(1500), date2(1500), date3(1500, 1, 1), date4(2000, 1, 1),
                     date5(2000, 1, 2);

    // then
    BOOST_CHECK(date1 == date2);
    BOOST_CHECK(date1 <= date2);
    BOOST_CHECK(date3 >= date2);
    BOOST_CHECK(date4 > date3);
    BOOST_CHECK(date4 < date5);
    BOOST_CHECK(date1 != date5);
}

BOOST_AUTO_TEST_CASE(Year) {
    // given
    tag::types::Date date;

    // then
    BOOST_CHECK(date.isEmpty());
    // set valid fields
    BOOST_CHECK(date.setYearOnly(2010));
    BOOST_CHECK(!date.isEmpty());
    // empty years
    BOOST_CHECK(!date.setYearOnly(1));
    BOOST_CHECK(!date.isEmpty());
    BOOST_CHECK_EQUAL(date.getYear(), 2010);
    BOOST_CHECK(!date.setYearOnly(10000));
    BOOST_CHECK(!date.isEmpty());
    BOOST_CHECK_EQUAL(date.getYear(), 2010);
    // set valid fields
    BOOST_CHECK(date.setYearOnly(2005));
    BOOST_CHECK_EQUAL(date.getYear(), 2005);
    BOOST_CHECK(date.isYearOnly());
    BOOST_CHECK(!date.isEmpty());
}

BOOST_AUTO_TEST_CASE(YearMonth) {
    // given
    tag::types::Date date;

    // then
    BOOST_CHECK(date.isEmpty());
    // set valid fields
    BOOST_CHECK(date.setYearMonthOnly(2010, 10));
    BOOST_CHECK(!date.isEmpty());
    // empty year-month
    BOOST_CHECK(!date.setYearMonthOnly(1, 10));
    BOOST_CHECK(!date.isEmpty());
    BOOST_CHECK(!date.setYearMonthOnly(10000, 10));
    BOOST_CHECK(!date.isEmpty());
    BOOST_CHECK(!date.setYearMonthOnly(1000, 0));
    BOOST_CHECK(!date.isEmpty());
    BOOST_CHECK(!date.setYearMonthOnly(9999, 13));
    BOOST_CHECK(!date.isEmpty());
    // minimal
    BOOST_CHECK(date.setYearMonthOnly(9999, 12));
    BOOST_CHECK(!date.isEmpty());
    BOOST_CHECK(date.isYearMonthOnly());
    // maximal
    BOOST_CHECK(date.setYearMonthOnly(1000, 1));
    BOOST_CHECK(!date.isEmpty());
    BOOST_CHECK(date.isYearMonthOnly());
}

BOOST_AUTO_TEST_CASE(YearMonthDay) {
    // given
    tag::types::Date date;

    //then
    //set valid fields
    BOOST_CHECK(date.setAll(2010, 10, 5));
    BOOST_CHECK(!date.isEmpty());
    //empty year-month
    BOOST_CHECK(!date.setAll(1, 10, 15));
    BOOST_CHECK(!date.isEmpty());
    BOOST_CHECK(!date.setAll(10000, 10, 5));
    BOOST_CHECK(!date.isEmpty());
    BOOST_CHECK(!date.setAll(1000, 0, 5));
    BOOST_CHECK(!date.isEmpty());
    BOOST_CHECK(!date.setAll(9999, 13, 5));
    BOOST_CHECK(!date.isEmpty());
    BOOST_CHECK(!date.setAll(9999, 6, 31));
    BOOST_CHECK(!date.isEmpty());
    BOOST_CHECK(!date.setAll(9999, 6, 0));
    BOOST_CHECK(!date.isEmpty());
    BOOST_CHECK(date.setAll(0, 0, 0));
    BOOST_CHECK(date.isEmpty());
    BOOST_CHECK(date.setAll(2000, 2, 29));
    BOOST_CHECK(!date.isEmpty());
    BOOST_CHECK(!date.setAll(1900, 2, 29));
    BOOST_CHECK(!date.isEmpty());
    BOOST_CHECK(date.setAll(9999, 7, 31));
    BOOST_CHECK(!date.isEmpty());
    BOOST_CHECK(date.setAll(9999, 12, 31));
    BOOST_CHECK(!date.isEmpty());
}

BOOST_AUTO_TEST_CASE(String) {
    // given
    static const std::array validDates = {
        std::pair("1999-17-25"s, tag::types::Date(1999, 17, 25)),
        std::pair("2018-09-22T07:45:30+00:00"s, tag::types::Date(2018, 9, 22)),
        std::pair("2018-09-22"s, tag::types::Date(2018, 9, 22)),
        std::pair("2018-09-22T07:45:30+00:00"s, tag::types::Date(2018, 9, 22)),
        std::pair("1999-01-1T07:45:30Z"s, tag::types::Date(1999, 1, 1)),
        std::pair("1999"s, tag::types::Date(1999)),
        std::pair("1999-4"s, tag::types::Date(1999, 4))
    };
    static const std::array invalidDates = {
        "5-17-25"s,
        "2018-14-29T07:45:30+00:00"s,
        "2018-09-31"s,
        "2018-00-22T07:45:30+00:00"s,
        "10521-521-521T07:45:30Z"s,
        "15215"s,
        "-6"s,
        "fsa"s,
        "not a valid date"s,
        "-1"s,
    };

    // then
    for (const auto &datePair : validDates) {
        BOOST_CHECK(tag::types::Date::parseString(datePair.first) == datePair.second);
        BOOST_CHECK(tag::types::Date::parseString(datePair.second.toString()) == datePair.second);
    }
    for (const auto &dateStr : invalidDates) {
        BOOST_CHECK(tag::types::Date::parseString(dateStr).isEmpty());
    }
}

BOOST_AUTO_TEST_SUITE_END()
