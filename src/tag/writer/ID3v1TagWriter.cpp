#include "ID3v1TagWriter.hpp"
#include <tag/priv/write_util.hpp>
#include <tag/string/genres.hpp>

namespace tag::writer {
    void ID3v1TagWriter::writeTagImpl(const AudioTagMap &tagMap, std::ostream &writeStream,
                                      const config::WriteConfiguration &writeConfiguration) const {
        priv::writeHeader(priv::headers::ID3_V1, writeStream);

        if (tagMap.containsTag(AudioTagMap::TITLE()))
            priv::writeUtf8Len(tagMap.getTitlePointer()->getText(), writeStream, 30);
        else
            priv::writeNull(writeStream, 30);

        if (tagMap.containsTag(AudioTagMap::ARTIST()))
            priv::writeUtf8Len(tagMap.getArtistPointer()->getText(), writeStream, 30);
        else
            priv::writeNull(writeStream, 30);

        if (tagMap.containsTag(AudioTagMap::ALBUM()))
            priv::writeUtf8Len(tagMap.getAlbumPointer()->getText(), writeStream, 30);
        else
            priv::writeNull(writeStream, 30);

        if (tagMap.containsTag(AudioTagMap::DATE()))
            priv::writeUtf8(tagMap.getDatePointer()->getDate().toYearString(), writeStream, false);
        else
            priv::writeNull(writeStream, 4);

        if (tagMap.containsTag(AudioTagMap::TRACKNUMBER())) {
            if (tagMap.containsTag(AudioTagMap::COMMENT()))
                priv::writeUtf8Len(tagMap.getCommentPointer()->getText(), writeStream, 28);
            else
                priv::writeNull(writeStream, 28);
            priv::writeNull(writeStream);
            writeStream.put(tagMap.getTrackNumberPointer()->getNumber());
        } else if (tagMap.containsTag(AudioTagMap::COMMENT()))
            priv::writeUtf8Len(tagMap.getCommentPointer()->getText(), writeStream, 30);
        else
            priv::writeNull(writeStream, 30);

        if (tagMap.containsTag(AudioTagMap::GENRE())) {
            std::size_t idx = string::getIndexByGenre(tagMap.getGenrePointer()->getText());
            if (idx != -1)
             writeStream.put(idx);
        }
        else
            priv::writeNull(writeStream);
    }

    std::uint64_t ID3v1TagWriter::calculateSizeImpl(const AudioTagMap &tagMap,
                                                    const config::WriteConfiguration &writeConfiguration) const {
        return 128;
    }
}