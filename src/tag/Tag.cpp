#include "Tag.hpp"
#include <array>
#include <boost/algorithm/string.hpp>

namespace tag {
	Tag::Tag(const std::string & name)
		: name(name) {
	}

    bool Tag::equals(const Tag *other) const {
	    if (other == nullptr)
	        return false;
	    return equals(*other);
	}

	const std::string & Tag::getName() const noexcept {
		return name;
	}



	StringTag::StringTag(const std::string & name, const std::string & text)
		: Tag(name)
		, text(text) {
	}

	Tag::Type StringTag::getType() const noexcept {
		return Type::String;
	}

	bool StringTag::isEmpty() const noexcept {
		return text.empty();
	}

    bool StringTag::equals(const Tag &other) const {
        if (getType() != other.getType())
            return false;
        return *this == dynamic_cast<const StringTag&>(other);
    }

	const std::string & StringTag::getText() const noexcept {
		return text;
	}

	std::string & StringTag::getText() noexcept {
		return text;
	}

	void StringTag::setText(const std::string & text) {
		this->text = text;
	}

    bool StringTag::operator==(const StringTag &other) const {
        return getName() == other.getName() && getText() == other.getText();
    }

    bool StringTag::operator!=(const StringTag &other) const {
        return !(*this == other);
    }



	DateTag::DateTag(const std::string & name, const types::Date &date)
		: Tag(name), date(date) {}

	Tag::Type DateTag::getType() const noexcept {
		return Type::Date;
	}

	bool DateTag::isEmpty() const noexcept {
		return date.isEmpty();
	}

    bool DateTag::equals(const Tag &other) const {
        if (getType() != other.getType())
            return false;
        return *this == dynamic_cast<const DateTag&>(other);
    }

	const types::Date & DateTag::getDate() const noexcept {
		return date;
	}

	types::Date & DateTag::getDate() noexcept {
		return date;
	}

	void DateTag::setDate(const types::Date & date) noexcept {
		this->date = date;
	}

    bool DateTag::operator==(const DateTag &other) const {
        return getName() == other.getName() && getDate() == other.getDate();
    }

    bool DateTag::operator!=(const DateTag &other) const {
        return !(*this == other);
    }



	NumberTag::NumberTag(const std::string & name, std::uint32_t number)
		: Tag(name)
		, number(number) {
	}

	Tag::Type NumberTag::getType() const noexcept {
		return Type::Number;
	}

	bool NumberTag::isEmpty() const noexcept {
		return number == std::uint32_t(-1);
	}

    bool NumberTag::equals(const Tag &other) const {
        if (getType() != other.getType())
            return false;
        return *this == dynamic_cast<const NumberTag&>(other);
    }

	std::uint32_t NumberTag::getNumber() const noexcept {
		return number;
	}

	void NumberTag::setNumber(std::uint32_t number) noexcept {
		this->number = number;
	}

    bool NumberTag::operator==(const NumberTag &other) const {
        return getName() == other.getName() && getNumber() == other.getNumber();
    }

    bool NumberTag::operator!=(const NumberTag &other) const {
        return !(*this == other);
    }



	ImageTag::ImageTag(ImageType imageType, const types::Image &image)
		: ImageTag(string::toString(imageType), image) {
	}

	ImageTag::ImageTag(const std::string &name, const types::Image &image)
		: Tag(name), image(image) {
	}

	ImageTag::ImageTag(ImageType imageType, types::Image && image)
		: ImageTag(string::toString(imageType), std::move(image)) {
	}

	ImageTag::ImageTag(const std::string &name, types::Image && image)
		: Tag(name), image(std::move(image)) {
	}

	Tag::Type ImageTag::getType() const noexcept {
		return Type::Image;
	}

	bool ImageTag::isEmpty() const noexcept {
		return image.getData().empty();
	}

    bool ImageTag::equals(const Tag &other) const {
        if (getType() != other.getType())
            return false;
        return *this == dynamic_cast<const ImageTag&>(other);
    }

	const types::Image & ImageTag::getImage() const {
		return image;
	}

	types::Image & ImageTag::getImage() {
		return image;
	}

	void ImageTag::setImage(const types::Image & image) {
		this->image = image;
	}

	void ImageTag::setImage(types::Image && image) {
		this->image = std::move(image);
	}

    bool ImageTag::operator==(const ImageTag &other) const {
        return getName() == other.getName() && getImage() == other.getImage();
    }

    bool ImageTag::operator!=(const ImageTag &other) const {
        return !(*this == other);
    }



	LyricsTag::LyricsTag(const std::string &language, const types::Lyrics & lyrics)
		: Tag(LYRICS + boost::to_upper_copy(language))
		, lyrics(lyrics) {}

	LyricsTag::LyricsTag(const std::string &language, types::Lyrics && lyrics)
		: Tag(LYRICS + boost::to_upper_copy(language))
		, lyrics(std::move(lyrics)) {}


	Tag::Type LyricsTag::getType() const noexcept {
		return Type::Lyrics;
	}

	bool LyricsTag::isEmpty() const noexcept {
		return lyrics.isEmpty();
	}

    bool LyricsTag::equals(const Tag &other) const {
        if (getType() != other.getType())
            return false;
        return *this == dynamic_cast<const LyricsTag&>(other);
    }

	const types::Lyrics & LyricsTag::getLyrics() const {
		return lyrics;
	}

	types::Lyrics & LyricsTag::getLyrics() {
		return lyrics;
	}

	void LyricsTag::setLyrics(const types::Lyrics & lyrics) {
		this->lyrics = lyrics;
	}

	void LyricsTag::setLyrics(types::Lyrics && lyrics) {
		this->lyrics = std::move(lyrics);
	}

    bool LyricsTag::operator==(const LyricsTag &other) const {
        return getName() == other.getName() && getLyrics() == other.getLyrics();
    }
    bool LyricsTag::operator!=(const LyricsTag &other) const {
        return !(*this == other);
    }

	const std::string LyricsTag::LYRICS = "LYRICS"s;



	ISRCTag::ISRCTag(const types::ISRC & isrc)
		: Tag("ISRC"s), isrc(isrc) {}

	ISRCTag::Type ISRCTag::getType() const noexcept {
		return Type::ISRC;
	}

	bool ISRCTag::isEmpty() const noexcept {
		return isrc.isEmpty();
	}

    bool ISRCTag::equals(const Tag &other) const {
        if (getType() != other.getType())
            return false;
        return *this == dynamic_cast<const ISRCTag&>(other);
    }

	const types::ISRC& ISRCTag::getISRC() const noexcept {
		return isrc;
	}

	types::ISRC & ISRCTag::getISRC() noexcept {
		return isrc;
	}

	void ISRCTag::setISRC(const types::ISRC & isrc) noexcept {
		this->isrc = isrc;
	}

    bool ISRCTag::operator==(const ISRCTag &other) const {
        return getName() == other.getName() && getISRC() == other.getISRC();
    }

    bool ISRCTag::operator!=(const ISRCTag &other) const {
        return !(*this == other);
    }



	BarcodeTag::BarcodeTag(const types::Barcode & barcode)
			: Tag("BARCODE"s), barcode(barcode) {}

	BarcodeTag::Type BarcodeTag::getType() const noexcept {
		return Type::Barcode;
	}

	bool BarcodeTag::isEmpty() const noexcept {
		return barcode.isEmpty();
	}

    bool BarcodeTag::equals(const Tag &other) const {
        if (getType() != other.getType())
            return false;
        return *this == dynamic_cast<const BarcodeTag&>(other);
    }

	const types::Barcode& BarcodeTag::getBarcode() const noexcept {
		return barcode;
	}

	types::Barcode & BarcodeTag::getBarcode() noexcept {
		return barcode;
	}

	void BarcodeTag::setBarcode(const types::Barcode & barcode) noexcept {
		this->barcode = barcode;
	}

    bool BarcodeTag::operator==(const BarcodeTag &other) const {
        return getName() == other.getName() && getBarcode() == other.getBarcode();
    }

    bool BarcodeTag::operator!=(const BarcodeTag &other) const {
        return !(*this == other);
    }
}



namespace tag::string {
	std::string toString(Tag::Type types) {
		static const std::array ARRAY = {
			"String"s, "Number"s,
			"Date"s, "Image"s,
			"Lyrics"s, "ISRC"s,
			"Barcode"s
		};
		std::size_t index = static_cast<std::size_t>(types);
		if (index < ARRAY.size())
			return ARRAY[index];
		return std::string();
	}

	std::string toString(tag::ImageTag::ImageType imageType) {
        static const std::array ARRAY = {
			"IMAGEOTHER"s, "IMAGEICON"s, "IMAGEOTHERICON"s, "IMAGECOVERFRONT"s,
			"IMAGECOVERBACK"s, "IMAGELEAFLET"s, "IMAGEMEDIA"s,
			"IMAGEARTIST"s, "IMAGECONDUCTOR"s, "IMAGEBAND"s,
			"IMAGECOMPOSER"s, "IMAGELYRICIST"s, "IMAGERECORDINGLOCATION"s,
			"IMAGEDURINGRECORDING"s, "IMAGEDURINGPERFORMANCE"s,
			"IMAGEVIDEOCAPTURE"s, "IMAGEABRIGHTCOLOUREDFISH"s,
			"IMAGEILLUSTRATION"s, "IMAGEBANDLOGO"s, "IMAGEPUBLISHERLOGO"s
		};
		std::size_t index = static_cast<std::size_t>(imageType);
		if (index < ARRAY.size())
			return ARRAY[index];
		return std::string();
	}
}
