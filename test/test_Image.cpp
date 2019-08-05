#include <boost/test/unit_test.hpp>
#include <tag/types/Image.hpp>
#include <tag/except/FileException.hpp>

BOOST_AUTO_TEST_SUITE(Image)

    BOOST_AUTO_TEST_CASE(InvalidPath) {
        // given
        tag::types::Image none("none");
        tag::types::Image empty("");
        tag::types::Image longPath("this/image/does/not/exist.jpg");

        // then
        BOOST_CHECK(none.isEmpty());
        BOOST_CHECK(empty.isEmpty());
        BOOST_CHECK(longPath.isEmpty());
    }

    BOOST_AUTO_TEST_CASE(ValidImages) {
        // given
        tag::types::Image jpg;
        tag::types::Image jpeg;
        tag::types::Image png;

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
        BOOST_CHECK(jpg.getMimeType() == tag::types::Image::MimeType::ImageJpeg);
        BOOST_CHECK(jpeg.getMimeType() == tag::types::Image::MimeType::ImageJpeg);
        BOOST_CHECK(png.getMimeType() == tag::types::Image::MimeType::ImagePng);
    }

    BOOST_AUTO_TEST_CASE(EmptyImages) {
        // given
        tag::types::Image jpg;
        tag::types::Image jpeg;
        tag::types::Image png;

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
        BOOST_CHECK(jpg.getMimeType() == tag::types::Image::MimeType::None);
        BOOST_CHECK(jpeg.getMimeType() == tag::types::Image::MimeType::None);
        BOOST_CHECK(png.getMimeType() == tag::types::Image::MimeType::None);
    }

BOOST_AUTO_TEST_SUITE_END()
