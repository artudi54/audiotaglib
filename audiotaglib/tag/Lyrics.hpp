#pragma once
#include <string>
#include <boost/algorithm/string.hpp>

namespace tag::type {
	class Lyrics {
	public:
		Lyrics(const std::string &description = std::string(),
			   const std::string &lyrics = std::string());

		const std::string& getDescription() const;
		std::string& getDescription();
		void setDescription(const std::string &description);

		const std::string& getLyrics() const;
		std::string& getLyrics();
		void setLyrics(const std::string &lyrics);

		bool isEmpty() const noexcept;

	private:
		std::string description;
		std::string lyrics;
	};
}