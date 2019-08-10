#include "ID3v1TagReader.hpp"
#include <tag/string/genres.hpp>
#include <tag/priv/read_util.hpp>

namespace tag::reader {
	TagMap ID3v1AudioTagReader::readTag(std::istream & readStream) const {
		TagMap map;
		if (!priv::readAndEquals(readStream, priv::headers::ID3_V1))
			throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 3);

		std::string tag;

		if (tag = priv::readUtf8(readStream, 30); !tag.empty())
			map.setTitle(tag);
		if (tag = priv::readUtf8(readStream, 30); !tag.empty())
			map.setArtist(tag);
		if (tag = priv::readUtf8(readStream, 30); !tag.empty())
			map.setAlbum(tag);

		if (tag = priv::readUtf8(readStream, 4); !tag.empty()) {
			try {
				std::uint32_t year = static_cast<std::uint32_t>(std::stoul(tag));
				map.setYear(year);
			} catch (std::logic_error&) {}
		}

		tag = priv::readUtf8(readStream, 30);
		if (tag.size() == 30 && tag[28] == '\0') {
			std::uint32_t trackNumber = tag.back();
			tag.pop_back();
			priv::truncatePadding(tag);
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
