#include "read_util.hpp"
#include <regex>
#include <boost/algorithm/string.hpp>
#include <tag/string/genres.hpp>
using namespace std::literals;

namespace tag::priv {



	std::string readUtf8(std::istream & readStream, std::streamsize length) {
		std::string result;
		if (length != -1) {
			result.resize(length);
			readStream.read(result.data(), length);
			truncatePadding(result);
		} else
			std::getline(readStream, result, '\0');
		return result;
	}




	void truncatePadding(std::string & string) {
		while (!string.empty() && (string.back() == '\0' || string.back() == ' '))
			string.pop_back();
	}










	std::string processMultistring(const std::string & text) {
		static const std::regex PATTERN(R"(\s*[;,/\\0\\]\s*)"s);
		std::string newText;
		newText.reserve(text.size());
		std::regex_replace(std::back_inserter(newText), text.begin(), text.end(), PATTERN, "; "s);
		return newText;
	}


	std::string processGenreString(std::string genres) {
		static const std::regex PATTERN(R"((?:^|[^\(])\((\d+)\))");

		std::smatch match;
		while (std::regex_search(genres, match, PATTERN)) {
			try {
				std::size_t index = std::stol(match[1].str());
				auto beg = std::prev(match[1].first), end = std::next(match[1].second);
				std::string replacement = (end == genres.end()) ?
					string::getGenreByIndex(index) : string::getGenreByIndex(index) + "; "s;
				genres.replace(beg, end, replacement);
			}
			catch (std::logic_error&) {
				genres.erase(std::prev(match[1].first), std::next(match[1].second));
			}
		}
		boost::replace_all(genres, "(("s, "("s);
		return genres;
	}










	unsigned readBigEndianSize(std::istream & readStream) {
		std::array<std::byte, 4> readSize;
		readStream.read(reinterpret_cast<char*>(readSize.data()), 4);
		return
			(unsigned(readSize[0]) << 24) | (unsigned(readSize[1]) << 16) |
			(unsigned(readSize[2]) << 8) | (unsigned(readSize[3]));
	}


	unsigned readSyncSafeBigEndianSize(std::istream & readStream) {
		std::array<std::byte, 4> readSize;
		readStream.read(reinterpret_cast<char*>(readSize.data()), 4);

		return (unsigned(readSize[0]) << 21) | (unsigned(readSize[1]) << 14) |
			   (unsigned(readSize[2]) << 7)  | (unsigned(readSize[3]));
	}







	unsigned readLittleEndianSize(std::istream & readStream) {
		std::array<std::byte, 4> readSize;
		readStream.read(reinterpret_cast<char*>(readSize.data()), 4);
		return
			(unsigned(readSize[0]))		  | (unsigned(readSize[1]) << 8) |
			(unsigned(readSize[2]) << 16) | (unsigned(readSize[3]) << 24);
	}


	std::uint64_t readLongLittleEndianSize(std::istream & readStream) {
		std::array<std::byte, 8> readSize;
		readStream.read(reinterpret_cast<char*>(readSize.data()), 8);
		return
			(std::uint64_t(readSize[0]))		  | (std::uint64_t(readSize[1]) << 8ull) |
			(std::uint64_t(readSize[2]) << 16ull) | (std::uint64_t(readSize[3]) << 24ull) |
			(std::uint64_t(readSize[4]) << 32ull) | (std::uint64_t(readSize[5]) << 40ull) |
			(std::uint64_t(readSize[6]) << 48ull) | (std::uint64_t(readSize[7]) << 56ull);
	}
}