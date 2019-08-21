#pragma once
#include <string>
#include <vector>

namespace audiotaglib::string {
	const std::vector<std::string>& getGenres();
	const std::string& getGenreByIndex(std::size_t idx);
	std::size_t getIndexByGenre(const std::string &genre);
}