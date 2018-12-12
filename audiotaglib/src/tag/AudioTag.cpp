#include "AudioTag.hpp"
#include <boost/algorithm/string.hpp>

namespace tag {
	AudioTag::AudioTag(const std::string & name)
		: name(name) {
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

	bool StringAudioTag::isNull() const noexcept {
		return text.empty();
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



	DateAudioTag::DateAudioTag(const std::string & name, const types::Date &date)
		: AudioTag(name), date(date) {}

	AudioTag::Type DateAudioTag::getType() const noexcept {
		return Type::Date;
	}

	bool DateAudioTag::isNull() const noexcept {
		return date.isEmpty();
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



	NumberAudioTag::NumberAudioTag(const std::string & name, std::uint32_t number)
		: AudioTag(name)
		, number(number) {
	}

	AudioTag::Type NumberAudioTag::getType() const noexcept {
		return Type::Number;
	}

	bool NumberAudioTag::isNull() const noexcept {
		return number == std::uint32_t(-1);
	}

	std::uint32_t NumberAudioTag::getNumber() const noexcept {
		return number;
	}

	void NumberAudioTag::setNumber(std::uint32_t number) noexcept {
		this->number = number;
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

	bool ImageAudioTag::isNull() const noexcept {
		return image.getData().empty();
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



	LyricsAudioTag::LyricsAudioTag(const std::string &language, const types::Lyrics & lyrics)
		:AudioTag(LYRICS + boost::to_upper_copy(language))
		, lyrics(lyrics) {}

	LyricsAudioTag::LyricsAudioTag(const std::string &language, types::Lyrics && lyrics)
		: AudioTag(LYRICS + boost::to_upper_copy(language))
		, lyrics(std::move(lyrics)) {}


	AudioTag::Type LyricsAudioTag::getType() const noexcept {
		return Type::Lyrics;
	}

	bool LyricsAudioTag::isNull() const noexcept {
		return lyrics.isEmpty();
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

	const std::string LyricsAudioTag::LYRICS = "LYRICS"s;



	ISRCAudioTag::ISRCAudioTag(const types::ISRC & isrc)
		: AudioTag("ISRC"s), isrc(isrc) {}

	ISRCAudioTag::Type ISRCAudioTag::getType() const noexcept {
		return Type::ISRC;
	}

	bool ISRCAudioTag::isNull() const noexcept {
		return isrc.isEmpty();
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



	BarcodeAudioTag::BarcodeAudioTag(const types::Barcode & barcode)
			: AudioTag("BARCODE"s), barcode(barcode) {}

	BarcodeAudioTag::Type BarcodeAudioTag::getType() const noexcept {
		return Type::Barcode;
	}

	bool BarcodeAudioTag::isNull() const noexcept {
		return barcode.isEmpty();
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
