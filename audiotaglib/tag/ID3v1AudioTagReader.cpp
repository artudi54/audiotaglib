#include "ID3v1AudioTagReader.hpp"
#include <tag/string/genres.hpp>

namespace tag::reader {

	AudioTagMap ID3v1AudioTagReader::readTag(std::istream & readStream) const {
		AudioTagMap map;
		if (!readAndEquals(readStream, Headers::ID3_V1))
			return map;

		std::string tag;

		if (tag = readUtf8(readStream, 30); !tag.empty())
			map.setTitle(tag);
		if (tag = readUtf8(readStream, 30); !tag.empty())
			map.setArtist(tag);
		if (tag = readUtf8(readStream, 30); !tag.empty())
			map.setAlbum(tag);

		if (tag = readUtf8(readStream, 4); !tag.empty()) {
			try {
				unsigned year = static_cast<unsigned>(std::stoul(tag));
				map.setYear(year);
			} catch (std::logic_error&) {}
		}

		tag = readUtf8(readStream, 30);
		if (tag.size() == 30 && tag[28] == '\0') {
			unsigned trackNumber = tag.back();
			tag.pop_back();
			truncatePadding(tag);
			map.setTrackNumber(trackNumber);
		}
		if (!tag.empty())
			map.setComment(tag);

		char index = readStream.get();
		const std::string& genre = tag::string::getGenreByIndex(index);
		if (!genre.empty())
			map.setGenre(genre);

		return map;
	}
}