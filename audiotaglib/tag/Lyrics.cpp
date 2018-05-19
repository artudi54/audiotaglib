#include "Lyrics.hpp"

namespace tag::type {
	Lyrics::Lyrics(const std::string & language, const std::string & description, const std::string & lyrics)
		:language(), description(description), lyrics(lyrics) {
		setLanguage(language);
	}
	const std::string Lyrics::getLanguage() const {
		return language;
	}
	void Lyrics::setLanguage(const std::string & language) {
		if (language.size() == 3) {
			this->language = boost::to_upper_copy(language);
		}
	}
	const std::string & Lyrics::getDescription() const {
		return descritpion;
	}
	std::string & Lyrics::getDescription() {
		return description;
	}
	void Lyrics::setDescription(const std::string & description) {
		this->description = description;
	}
	const std::string & Lyrics::getLyrics() const {
		return lyrics;
	}
	std::string & Lyrics::getLyrics() {
		return lyrics;
	}
	void Lyrics::setLyrics(const std::string & lyrics) {
		this->lyrics = lyrics;
	}
}