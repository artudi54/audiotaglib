#include <tag/types/Lyrics.hpp>

namespace tag::types {

	Lyrics::Lyrics(const std::string & description, const std::string & lyrics)
		: description(description), lyrics(lyrics) {}


	const std::string & Lyrics::getDescription() const {
		return description;
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




	bool Lyrics::isEmpty() const noexcept {
		return description.empty() && lyrics.empty();
	}
}