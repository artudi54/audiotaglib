#include "AudioTag.hpp"
#include <boost/algorithm/string.hpp>

namespace tag {
	AudioTag::AudioTag(const std::string & name)
		: name(name) {
	}

    bool AudioTag::equals(const AudioTag *other) const {
	    if (other == nullptr)
	        return false;
	    return equals(*other);
	}

	const std::string & AudioTag::getName() const noexcept {
		return name;
	}



	StringAudioTag::StringAudioTag(const std::string & name, const std::string & text)
		: AudioTag(name)
		, text(text) {
	}

	AudioTag::Type StringAudioTag::getType() const noexcept {
		return Type::String;
	}

	bool StringAudioTag::isEmpty() const noexcept {
		return text.empty();
	}

    bool StringAudioTag::equals(const AudioTag &other) const {
        if (getType() != other.getType())
            return false;
        return *this == dynamic_cast<const StringAudioTag&>(other);
    }

	const std::string & StringAudioTag::getText() const noexcept {
		return text;
	}

	std::string & StringAudioTag::getText() noexcept {
		return text;
	}

	void StringAudioTag::setText(const std::string & text) {
		this->text = text;
	}

    bool StringAudioTag::operator==(const StringAudioTag &other) const {
        return getName() == other.getName() && getText() == other.getText();
    }



	DateAudioTag::DateAudioTag(const std::string & name, const types::Date &date)
		: AudioTag(name), date(date) {}

	AudioTag::Type DateAudioTag::getType() const noexcept {
		return Type::Date;
	}

	bool DateAudioTag::isEmpty() const noexcept {
		return date.isEmpty();
	}

    bool DateAudioTag::equals(const AudioTag &other) const {
        if (getType() != other.getType())
            return false;
        return *this == dynamic_cast<const DateAudioTag&>(other);
    }

	const types::Date & DateAudioTag::getDate() const noexcept {
		return date;
	}

	types::Date & DateAudioTag::getDate() noexcept {
		return date;
	}

	void DateAudioTag::setDate(const types::Date & date) noexcept {
		this->date = date;
	}

    bool DateAudioTag::operator==(const DateAudioTag &other) const {
        return getName() == other.getName() && getDate() == other.getDate();
    }



	NumberAudioTag::NumberAudioTag(const std::string & name, std::uint32_t number)
		: AudioTag(name)
		, number(number) {
	}

	AudioTag::Type NumberAudioTag::getType() const noexcept {
		return Type::Number;
	}

	bool NumberAudioTag::isEmpty() const noexcept {
		return number == std::uint32_t(-1);
	}

    bool NumberAudioTag::equals(const AudioTag &other) const {
        if (getType() != other.getType())
            return false;
        return *this == dynamic_cast<const NumberAudioTag&>(other);
    }

	std::uint32_t NumberAudioTag::getNumber() const noexcept {
		return number;
	}

	void NumberAudioTag::setNumber(std::uint32_t number) noexcept {
		this->number = number;
	}

    bool NumberAudioTag::operator==(const NumberAudioTag &other) const {
        return getName() == other.getName() && getNumber() == other.getNumber();
    }



	ImageAudioTag::ImageAudioTag(ImageType imageType, const types::Image &image)
		: ImageAudioTag(string::toString(imageType), image) {
	}

	ImageAudioTag::ImageAudioTag(const std::string &name, const types::Image &image)
		: AudioTag(name), image(image) {
	}

	ImageAudioTag::ImageAudioTag(ImageType imageType, types::Image && image)
		: ImageAudioTag(string::toString(imageType), std::move(image)) {
	}

	ImageAudioTag::ImageAudioTag(const std::string &name, types::Image && image)
		: AudioTag(name), image(std::move(image)) {
	}

	AudioTag::Type ImageAudioTag::getType() const noexcept {
		return Type::Image;
	}

	bool ImageAudioTag::isEmpty() const noexcept {
		return image.getData().empty();
	}

    bool ImageAudioTag::equals(const AudioTag &other) const {
        if (getType() != other.getType())
            return false;
        return *this == dynamic_cast<const ImageAudioTag&>(other);
    }

	const types::Image & ImageAudioTag::getImage() const {
		return image;
	}

	types::Image & ImageAudioTag::getImage() {
		return image;
	}

	void ImageAudioTag::setImage(const types::Image & image) {
		this->image = image;
	}

	void ImageAudioTag::setImage(types::Image && image) {
		this->image = std::move(image);
	}

    bool ImageAudioTag::operator==(const ImageAudioTag &other) const {
        return getName() == other.getName() && getImage() == other.getImage();
    }



	LyricsAudioTag::LyricsAudioTag(const std::string &language, const types::Lyrics & lyrics)
		:AudioTag(LYRICS + boost::to_upper_copy(language))
		, lyrics(lyrics) {}

	LyricsAudioTag::LyricsAudioTag(const std::string &language, types::Lyrics && lyrics)
		: AudioTag(LYRICS + boost::to_upper_copy(language))
		, lyrics(std::move(lyrics)) {}


	AudioTag::Type LyricsAudioTag::getType() const noexcept {
		return Type::Lyrics;
	}

	bool LyricsAudioTag::isEmpty() const noexcept {
		return lyrics.isEmpty();
	}

    bool LyricsAudioTag::equals(const AudioTag &other) const {
        if (getType() != other.getType())
            return false;
        return *this == dynamic_cast<const LyricsAudioTag&>(other);
    }

	const types::Lyrics & LyricsAudioTag::getLyrics() const {
		return lyrics;
	}

	types::Lyrics & LyricsAudioTag::getLyrics() {
		return lyrics;
	}

	void LyricsAudioTag::setLyrics(const types::Lyrics & lyrics) {
		this->lyrics = lyrics;
	}

	void LyricsAudioTag::setLyrics(types::Lyrics && lyrics) {
		this->lyrics = std::move(lyrics);
	}

    bool LyricsAudioTag::operator==(const LyricsAudioTag &other) const {
        return getName() == other.getName() && getLyrics() == other.getLyrics();
    }

	const std::string LyricsAudioTag::LYRICS = "LYRICS"s;



	ISRCAudioTag::ISRCAudioTag(const types::ISRC & isrc)
		: AudioTag("ISRC"s), isrc(isrc) {}

	ISRCAudioTag::Type ISRCAudioTag::getType() const noexcept {
		return Type::ISRC;
	}

	bool ISRCAudioTag::isEmpty() const noexcept {
		return isrc.isEmpty();
	}

    bool ISRCAudioTag::equals(const AudioTag &other) const {
        if (getType() != other.getType())
            return false;
        return *this == dynamic_cast<const ISRCAudioTag&>(other);
    }

	const types::ISRC& ISRCAudioTag::getISRC() const noexcept {
		return isrc;
	}

	types::ISRC & ISRCAudioTag::getISRC() noexcept {
		return isrc;
	}

	void ISRCAudioTag::setISRC(const types::ISRC & isrc) noexcept {
		this->isrc = isrc;
	}

    bool ISRCAudioTag::operator==(const ISRCAudioTag &other) const {
        return getName() == other.getName() && getISRC() == other.getISRC();
    }



	BarcodeAudioTag::BarcodeAudioTag(const types::Barcode & barcode)
			: AudioTag("BARCODE"s), barcode(barcode) {}

	BarcodeAudioTag::Type BarcodeAudioTag::getType() const noexcept {
		return Type::Barcode;
	}

	bool BarcodeAudioTag::isEmpty() const noexcept {
		return barcode.isEmpty();
	}

    bool BarcodeAudioTag::equals(const AudioTag &other) const {
        if (getType() != other.getType())
            return false;
        return *this == dynamic_cast<const BarcodeAudioTag&>(other);
    }

	const types::Barcode& BarcodeAudioTag::getBarcode() const noexcept {
		return barcode;
	}

	types::Barcode & BarcodeAudioTag::getBarcode() noexcept {
		return barcode;
	}

	void BarcodeAudioTag::setBarcode(const types::Barcode & barcode) noexcept {
		this->barcode = barcode;
	}

    bool BarcodeAudioTag::operator==(const BarcodeAudioTag &other) const {
        return getName() == other.getName() && getBarcode() == other.getBarcode();
    }
}



namespace tag::string {
	std::string toString(AudioTag::Type types) {
		static const std::string ARRAY[] = {
			"String"s, "Number"s,
			"Date"s, "Image"s
		};
		std::size_t index = static_cast<std::size_t>(types);
		if (index < sizeof(ARRAY) / sizeof(*ARRAY))
			return ARRAY[index];
		return std::string();
	}

	std::string toString(tag::ImageAudioTag::ImageType imageType) {
		static const std::string ARRAY[] = {
			"IMAGEOTHER"s, "IMAGEICON"s, "IMAGEOTHERICON"s, "IMAGECOVERFRONT"s,
			"IMAGECOVERBACK"s, "IMAGELEAFLET"s, "IMAGEMEDIA"s,
			"IMAGEARTIST"s, "IMAGECONDUCTOR"s, "IMAGEBAND"s,
			"IMAGECOMPOSER"s, "IMAGELYRICIST"s, "IMAGERECORDINGLOCATION"s,
			"IMAGEDURINGRECORDING"s, "IMAGEDURINGPERFORMANCE"s,
			"IMAGEVIDEOCAPTURE"s, "IMAGEABRIGHTCOLOUREDFISH"s,
			"IMAGEILLUSTRATION"s, "IMAGEBANDLOGO"s, "IMAGEPUBLISHERLOGO"s
		};
		std::size_t index = static_cast<std::size_t>(imageType);
		if (index < sizeof(ARRAY) / sizeof(*ARRAY))
			return ARRAY[index];
		return std::string();
	}
}
