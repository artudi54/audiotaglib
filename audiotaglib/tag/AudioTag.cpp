#include "AudioTag.hpp"

namespace tag {
	AudioTag::AudioTag(const std::string & name)
		: name(name) {
	}

	AudioTag::~AudioTag() {}

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








	DateAudioTag::DateAudioTag(const std::string & name, const type::Date &date)
		: AudioTag(name), date(date) {
	}

	AudioTag::Type DateAudioTag::getType() const noexcept {
		return Type::Date;
	}

	bool DateAudioTag::isNull() const noexcept {
		return date.isNull();
	}

	const type::Date & DateAudioTag::getDate() const noexcept {
		return date;
	}

	type::Date & DateAudioTag::getDate() noexcept {
		return date;
	}

	void DateAudioTag::setDate(const type::Date date) noexcept {
		this->date = date;
	}






	NumberAudioTag::NumberAudioTag(const std::string & name, unsigned number)
		: AudioTag(name)
		, number(number) {
	}

	AudioTag::Type NumberAudioTag::getType() const noexcept {
		return Type::Number;
	}

	bool NumberAudioTag::isNull() const noexcept {
		return number == -1;
	}

	unsigned NumberAudioTag::getNumber() const noexcept {
		return number;
	}

	void NumberAudioTag::setNumber(unsigned number) noexcept {
		this->number = number;
	}





	ImageAudioTag::ImageAudioTag(ImageType imageType, const type::Image &image)
		: ImageAudioTag(string::toString(imageType), image) {
	}

	ImageAudioTag::ImageAudioTag(const std::string &name, const type::Image &image)
		: AudioTag(name), image(image) {
	}

	ImageAudioTag::ImageAudioTag(ImageType imageType, type::Image && image)
		: ImageAudioTag(string::toString(imageType), std::move(image)) {
	}

	ImageAudioTag::ImageAudioTag(const std::string &name, type::Image && image)
		: AudioTag(name), image(std::move(image)) {
	}

	AudioTag::Type ImageAudioTag::getType() const noexcept {
		return Type::Image;
	}

	bool ImageAudioTag::isNull() const noexcept {
		return image.getData().empty();
	}

	const type::Image & ImageAudioTag::getImage() const {
		return image;
	}

	type::Image & ImageAudioTag::getImage() {
		return image;
	}

	void ImageAudioTag::setImage(const type::Image & image) {
		this->image = image;
	}

	void ImageAudioTag::setImage(type::Image && image) {
		this->image = std::move(image);
	}






	LyricsAudioTag::LyricsAudioTag(const std::string &language, const type::Lyrics & lyrics)
		:AudioTag(LYRICS + boost::to_upper_copy(language))
		, lyrics(lyrics) {}

	LyricsAudioTag::LyricsAudioTag(const std::string &language, type::Lyrics && lyrics)
		: AudioTag(LYRICS + boost::to_upper_copy(language))
		, lyrics(std::move(lyrics)) {}


	AudioTag::Type LyricsAudioTag::getType() const noexcept {
		return Type::Lyrics;
	}

	bool LyricsAudioTag::isNull() const noexcept {
		return lyrics.isEmpty();
	}




	const type::Lyrics & LyricsAudioTag::getLyrics() const {
		return lyrics;
	}

	type::Lyrics & LyricsAudioTag::getLyrics() {
		return lyrics;
	}

	void LyricsAudioTag::setLyrics(const type::Lyrics & lyrics) {
		this->lyrics = lyrics;
	}

	void LyricsAudioTag::setLyrics(type::Lyrics && lyrics) {
		this->lyrics = std::move(lyrics);
	}


	const std::string LyricsAudioTag::LYRICS = "LYRICS"s;







	ISRCAudioTag::ISRCAudioTag(const type::ISRC & isrc)
		: AudioTag("ISRC"s), isrc(isrc) {}



	ISRCAudioTag::Type ISRCAudioTag::getType() const noexcept {
		return Type::ISRC;
	}

	bool ISRCAudioTag::isNull() const noexcept {
		return isrc.isEmpty();
	}




	const type::ISRC& ISRCAudioTag::getISRC() const noexcept {
		return isrc;
	}

	type::ISRC & ISRCAudioTag::getISRC() noexcept {
		return isrc;
	}

	void ISRCAudioTag::setISRC(const type::ISRC & isrc) noexcept {
		this->isrc = isrc;
	}




}







std::string tag::string::toString(AudioTag::Type type) {
	static const std::string ARRAY[] = {
		"String"s, "Number"s,
		"Date"s, "Image"s
	};
	std::size_t index = static_cast<std::size_t>(type);
	if (index < sizeof(ARRAY) / sizeof(*ARRAY))
		return ARRAY[index];
	return std::string();
}

std::string tag::string::toString(tag::ImageAudioTag::ImageType imageType) {
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
