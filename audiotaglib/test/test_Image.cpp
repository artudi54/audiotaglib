#include <boost/test/unit_test.hpp>
#include <tag/types/Image.hpp>

BOOST_AUTO_TEST_SUITE(Image)


BOOST_AUTO_TEST_CASE(InvalidPath) {
    BOOST_CHECK_THROW(tag::types::Image emptyJpg("none"), tag::except::FileException);
    BOOST_CHECK_THROW(tag::types::Image emptyJpg(""), tag::except::FileException);
    BOOST_CHECK_THROW(tag::types::Image emptyJpg("images/emptypng.jpge"), tag::except::FileException);
}

BOOST_AUTO_TEST_CASE(EmptyImages) {
    try {
        tag::types::Image emptyNotImage("images/empty.notimage");
    } catch (std::exception &) {
        int i = 2;
        i +=2;
    }
    //BOOST_CHECK_THROW(tag::types::Image emptyJpeg("images/emptyJpeg.jpeg"), tag::except::FileException);
    //BOOST_CHECK_THROW(tag::types::Image emptyJpg("images/emptyJpg.jpg"), tag::except::FileException);
    //BOOST_CHECK_THROW(tag::types::Image emptyPng("images/emptyPng.png"), tag::except::FileException);
}

BOOST_AUTO_TEST_SUITE_END()