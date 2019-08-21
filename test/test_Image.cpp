#include <boost/test/unit_test.hpp>
#include <audiotaglib/types/Image.hpp>
#include <audiotaglib/except/FileException.hpp>

BOOST_AUTO_TEST_SUITE(Image)

    BOOST_AUTO_TEST_CASE(InvalidPath) {
        // given
        audiotaglib::types::Image none("none");
        audiotaglib::types::Image empty("");
        audiotaglib::types::Image longPath("this/image/does/not/exist.jpg");

        // then
        BOOST_CHECK(none.isEmpty());
        BOOST_CHECK(empty.isEmpty());
        BOOST_CHECK(longPath.isEmpty());
    }

    BOOST_AUTO_TEST_CASE(ValidImages) {
        // given
        audiotaglib::types::Image jpg;
        audiotaglib::types::Image jpeg;
        audiotaglib::types::Image png;

        // when
        jpg.setFromFile("resources/images/jpg-image.jpg");
        jpeg.setFromFile("resources/images/jpeg-image.jpeg");
        png.setFromFile("resources/images/png-image.png");

        // then
        // not empty
        BOOST_CHECK(!jpg.isEmpty());
        BOOST_CHECK(!jpeg.isEmpty());
        BOOST_CHECK(!png.isEmpty());
        // valid mime type
        BOOST_CHECK(jpg.getMimeType() == audiotaglib::types::Image::MimeType::ImageJpeg);
        BOOST_CHECK(jpeg.getMimeType() == audiotaglib::types::Image::MimeType::ImageJpeg);
        BOOST_CHECK(png.getMimeType() == audiotaglib::types::Image::MimeType::ImagePng);
    }

    BOOST_AUTO_TEST_CASE(EmptyImages) {
        // given
        audiotaglib::types::Image jpg;
        audiotaglib::types::Image jpeg;
        audiotaglib::types::Image png;

        // when
        jpg.setFromFile("resources/images/empty/jpg-empty.jpg");
        jpeg.setFromFile("resources/images/empty/jpeg-empty.jpeg");
        png.setFromFile("resources/images/empty/png-empty.png");

        // then
        // empty
        BOOST_CHECK(jpg.isEmpty());
        BOOST_CHECK(jpeg.isEmpty());
        BOOST_CHECK(png.isEmpty());
        // invalid mime type
        BOOST_CHECK(jpg.getMimeType() == audiotaglib::types::Image::MimeType::None);
        BOOST_CHECK(jpeg.getMimeType() == audiotaglib::types::Image::MimeType::None);
        BOOST_CHECK(png.getMimeType() == audiotaglib::types::Image::MimeType::None);
    }

BOOST_AUTO_TEST_SUITE_END()
