#include "ID3v1TagWriter.hpp"
#include <tag/priv/write_util.hpp>
#include <tag/string/genres.hpp>
#include <tag/writer/ID3v1TagWriter.hpp>


namespace tag::writer {
    void ID3v1TagWriter::writeTagImpl(const AudioTagMap &tagMap, std::ostream &writeStream,
                                      const config::WriteConfiguration &writeConfiguration) const {
        priv::writeHeader(priv::headers::ID3_V1, writeStream);

        if (tagMap.containsTag(AudioTagMap::TITLE()))
            priv::writeUtf8Len(tagMap.getTitle()->getText(), writeStream, 30);
        else
            priv::writeNull(writeStream, 30);

        if (tagMap.containsTag(AudioTagMap::ARTIST()))
            priv::writeUtf8Len(tagMap.getArtist()->getText(), writeStream, 30);
        else
            priv::writeNull(writeStream, 30);

        if (tagMap.containsTag(AudioTagMap::ALBUM()))
            priv::writeUtf8Len(tagMap.getAlbum()->getText(), writeStream, 30);
        else
            priv::writeNull(writeStream, 30);

        if (tagMap.containsTag(AudioTagMap::DATE()))
            priv::writeUtf8(tagMap.getDate()->getDate().toYearString(), writeStream, false);
        else
            priv::writeNull(writeStream, 4);

        if (tagMap.containsTag(AudioTagMap::TRACKNUMBER())) {
            if (tagMap.containsTag(AudioTagMap::COMMENT()))
                priv::writeUtf8Len(tagMap.getComment()->getText(), writeStream, 28);
            else
                priv::writeNull(writeStream, 28);
            priv::writeNull(writeStream);
            writeStream.put(tagMap.getTrackNumber()->getNumber());
        } else if (tagMap.containsTag(AudioTagMap::COMMENT()))
            priv::writeUtf8Len(tagMap.getComment()->getText(), writeStream, 30);
        else
            priv::writeNull(writeStream, 30);

        if (tagMap.containsTag(AudioTagMap::GENRE())) {
            std::size_t idx = string::getIndexByGenre(tagMap.getGenre()->getText());
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