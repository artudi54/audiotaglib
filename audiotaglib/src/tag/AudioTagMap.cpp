#include "AudioTagMap.hpp"
#include <boost/algorithm/string.hpp>
#include <tag/AudioTagMap.hpp>


namespace tag {

    const std::string& AudioTagMap::ALBUM() {
        static const std::string _ALBUM = "ALBUM"s;
        return _ALBUM;
    }

    const std::string& AudioTagMap::ALBUMSORT() {
        static const std::string _ALBUMSORT = "ALBUMSORT"s;
        return _ALBUMSORT;
    }

    const std::string& AudioTagMap::ALBUMARTIST() {
        static const std::string _ALBUMARTIST = "ALBUMARTIST"s;
        return _ALBUMARTIST;
    }

    const std::string& AudioTagMap::ALBUMARTISTSORT() {
        static const std::string _ALBUMARTISTSORT = "ALBUMARTISTSORT"s;
        return _ALBUMARTISTSORT;
    }

    const std::string& AudioTagMap::ARRANGER() {
        static const std::string _ARRANGER = "ARRANGER"s;
        return _ARRANGER;
    }

    const std::string& AudioTagMap::ARTIST() {
        static const std::string _ARTIST = "ARTIST"s;
        return _ARTIST;
    }

    const std::string& AudioTagMap::ARTISTSORT() {
        static const std::string _ARTISTSORT = "ARTISTSORT"s;
        return _ARTISTSORT;
    }

    const std::string &AudioTagMap::BARCODE() {
        static const std::string _BARCODE = "BARCODE"s;
        return _BARCODE;
    }

    const std::string& AudioTagMap::BPM() {
        static const std::string _BPM = "BPM"s;
        return _BPM;
    }

    const std::string& AudioTagMap::COMMENT() {
        static const std::string _COMMENT = "COMMENT"s;
        return _COMMENT;
    }

    const std::string& AudioTagMap::COMPOSER() {
        static const std::string _COMPOSER = "COMPOSER"s;
        return _COMPOSER;
    }

    const std::string& AudioTagMap::COMPOSERSORT() {
        static const std::string _COMPOSERSORT = "COMPOSERSORT"s;
        return _COMPOSERSORT;
    }

    const std::string& AudioTagMap::CONDUCTOR() {
        static const std::string _CONDUCTOR = "CONDUCTOR"s;
        return _CONDUCTOR;
    }

    const std::string & AudioTagMap::CONTENTGROUP() {
        static const std::string _CONTENTGROUP = "CONTENTGROUP"s;
        return _CONTENTGROUP;
    }

    const std::string & AudioTagMap::COPYRIGHT() {
        static const std::string _COPYRIGHT = "COPYRIGHT"s;
        return _COPYRIGHT;
    }

    const std::string& AudioTagMap::DATE() {
        static const std::string _DATE = "DATE"s;
        return _DATE;
    }

    const std::string& AudioTagMap::DISCNUMBER() {
        static const std::string _DISCNUMBER = "DISCNUMBER"s;
        return _DISCNUMBER;
    }

    const std::string &AudioTagMap::ENGINEER() {
        static const std::string _ENGINEER = "ENGINEER"s;
        return _ENGINEER;
    }

    const std::string & AudioTagMap::ENCODEDBY() {
        static const std::string _ENCODEDBY = "ENCODEDBY"s;
        return _ENCODEDBY;
    }

    const std::string & AudioTagMap::ENCODERSETTINGS() {
        static const std::string _ENCODERSETTINGS = "ENCODERSETTINGS"s;
        return _ENCODERSETTINGS;
    }

    const std::string & AudioTagMap::ENCODINGDATE() {
        static const std::string _ENCODINGDATE = "ENCODINGDATE"s;
        return _ENCODINGDATE;
    }

    const std::string& AudioTagMap::GENRE() {
        static const std::string _GENRE = "GENRE"s;
        return _GENRE;
    }

    const std::string& AudioTagMap::IMAGEOTHER() {
        static const std::string _IMAGEOTHER = "IMAGEOTHER"s;
        return _IMAGEOTHER;
    }

    const std::string& AudioTagMap::IMAGEICON() {
        static const std::string _IMAGEICON = "IMAGEICON"s;
        return _IMAGEICON;
    }

    const std::string& AudioTagMap::IMAGEOTHERICON() {
        static const std::string _IMAGEOTHERICON = "IMAGEOTHERICON"s;
        return _IMAGEOTHERICON;
    }

    const std::string& AudioTagMap::IMAGECOVERFRONT() {
        static const std::string _IMAGECOVERFRONT = "IMAGECOVERFRONT"s;
        return _IMAGECOVERFRONT;
    }

    const std::string& AudioTagMap::IMAGECOVERBACK() {
        static const std::string _IMAGECOVERBACK = "IMAGECOVERBACK"s;
        return _IMAGECOVERBACK;
    }

    const std::string& AudioTagMap::IMAGELEAFLET() {
        static const std::string _IMAGELEAFLET = "IMAGELEAFLET"s;
        return _IMAGELEAFLET;
    }

    const std::string& AudioTagMap::IMAGEMEDIA() {
        static const std::string _IMAGEMEDIA = "IMAGEMEDIA"s;
        return _IMAGEMEDIA;
    }

    const std::string& AudioTagMap::IMAGEARTIST() {
        static const std::string _IMAGEARTIST = "IMAGEARTIST"s;
        return _IMAGEARTIST;
    }

    const std::string& AudioTagMap::IMAGECONDUCTOR() {
        static const std::string _IMAGECONDUCTOR = "IMAGECONDUCTOR"s;
        return _IMAGECONDUCTOR;
    }

    const std::string& AudioTagMap::IMAGEBAND() {
        static const std::string _IMAGEBAND = "IMAGEBAND"s;
        return _IMAGEBAND;
    }

    const std::string& AudioTagMap::IMAGECOMPOSER() {
        static const std::string _IMAGECOMPOSER = "IMAGECOMPOSER"s;
        return _IMAGECOMPOSER;
    }

    const std::string& AudioTagMap::IMAGELEADARTIST() {
        static const std::string _IMAGELEADARTIST = "IMAGELEADARTIST"s;
        return _IMAGELEADARTIST;
    }

    const std::string& AudioTagMap::IMAGELYRICIST() {
        static const std::string _IMAGELYRICIST = "IMAGELYRICIST"s;
        return _IMAGELYRICIST;
    }

    const std::string& AudioTagMap::IMAGERECORDINGLOCATION() {
        static const std::string _IMAGERECORDINGLOCATION = "IMAGERECORDINGLOCATION"s;
        return _IMAGERECORDINGLOCATION;
    }

    const std::string& AudioTagMap::IMAGEDURINGRECORDING() {
        static const std::string _IMAGEDURINGRECORDING = "IMAGEDURINGRECORDING"s;
        return _IMAGEDURINGRECORDING;
    }

    const std::string& AudioTagMap::IMAGEDURINGPERFORMANCE() {
        static const std::string _IMAGEDURINGPERFORMANCE = "IMAGEDURINGPERFORMANCE"s;
        return _IMAGEDURINGPERFORMANCE;
    }

    const std::string& AudioTagMap::IMAGEVIDEOCAPTURE() {
        static const std::string _IMAGEVIDEOCAPTURE = "IMAGEVIDEOCAPTURE"s;
        return _IMAGEVIDEOCAPTURE;
    }

    const std::string& AudioTagMap::IMAGEABRIGHTCOLOUREDFISH() {
        static const std::string _IMAGEABRIGHTCOLOUREDFISH = "IMAGEABRIGHTCOLOUREDFISH"s;
        return _IMAGEABRIGHTCOLOUREDFISH;
    }

    const std::string& AudioTagMap::IMAGEILLUSTRATION() {
        static const std::string _IMAGEILLUSTRATION = "IMAGEILLUSTRATION"s;
        return _IMAGEILLUSTRATION;
    }

    const std::string& AudioTagMap::IMAGEBANDLOGO() {
        static const std::string _IMAGEBANDLOGO = "IMAGEBANDLOGO"s;
        return _IMAGEBANDLOGO;
    }

    const std::string& AudioTagMap::IMAGEPUBLISHERLOGO() {
        static const std::string _IMAGEPUBLISHERLOGO = "IMAGEPUBLISHERLOGO"s;
        return _IMAGEPUBLISHERLOGO;
    }

    const std::string & AudioTagMap::INITIALKEY() {
        static const std::string _INITIALKEY = "INITIALKEY"s;
        return _INITIALKEY;
    }

    const std::string & AudioTagMap::ISRC() {
        static const std::string _ISRC = "ISRC"s;
        return _ISRC;
    }

    const std::string& AudioTagMap::LYRICS() {
        static const std::string _LYRICS = "LYRICS"s;
        return _LYRICS;
    }


    const std::string& AudioTagMap::LYRICSENG() {
        static const std::string _LYRICSENG = "LYRICSENG"s;
        return _LYRICSENG;
    }


    const std::string& AudioTagMap::LYRICIST() {
        static const std::string _LYRICIST = "LYRICIST"s;
        return _LYRICIST;
    }

    const std::string & AudioTagMap::MOOD() {
        static const std::string _MOOD = "MOOD"s;
        return _MOOD;
    }

    const std::string & AudioTagMap::MIXDJ() {
        static const std::string _MIXDJ = "MIXDJ"s;
        return _MIXDJ;
    }

    const std::string & AudioTagMap::MIXENGINEER() {
        static const std::string _MIXENGINEER = "MIXENGINEER"s;
        return _MIXENGINEER;
    }

    const std::string& AudioTagMap::ORIGINALALBUM() {
        static const std::string _ORIGINALALBUM = "ORIGINALALBUM"s;
        return _ORIGINALALBUM;
    }

    const std::string& AudioTagMap::ORIGINALARTIST() {
        static const std::string _ORIGINALARTIST = "ORIGINALARTIST"s;
        return _ORIGINALARTIST;
    }

    const std::string& AudioTagMap::ORIGINALDATE() {
        static const std::string _ORIGINALDATE = "ORIGINALDATE"s;
        return _ORIGINALDATE;
    }

    const std::string& AudioTagMap::ORIGINALLYRICIST() {
        static const std::string _ORIGINALLYRICIST = "ORIGINALLYRICIST"s;
        return _ORIGINALLYRICIST;
    }

    const std::string& AudioTagMap::PRODUCER() {
        static const std::string _PRODUCER = "PRODUCER"s;
        return _PRODUCER;
    }

    const std::string& AudioTagMap::PUBLISHER() {
        static const std::string _PUBLISHER = "PUBLISHER"s;
        return _PUBLISHER;
    }

    const std::string & AudioTagMap::RADIOSTATION() {
        static const std::string _RADIOSTATION = "RADIOSTATION"s;
        return _RADIOSTATION;
    }

    const std::string & AudioTagMap::RADIOSTATIONOWNER() {
        static const std::string _RADIOSTATIONOWNER = "RADIOSTATIONOWNER"s;
        return _RADIOSTATIONOWNER;
    }

    const std::string & AudioTagMap::REMIXER() {
        static const std::string _REMIXER = "REMIXER"s;
        return _REMIXER;
    }

    const std::string & AudioTagMap::SETSUBTITLE() {
        static const std::string _SETSUBTITLE = "SETSUBTITLE"s;
        return _SETSUBTITLE;
    }

    const std::string& AudioTagMap::SUBTITLE() {
        static const std::string _SUBTITLE = "SUBTITLE"s;
        return _SUBTITLE;
    }

    const std::string& AudioTagMap::TITLE() {
        static const std::string _TITLE = "TITLE"s;
        return _TITLE;
    }

    const std::string& AudioTagMap::TITLESORT() {
        static const std::string _TITLESORT = "TITLESORT"s;
        return _TITLESORT;
    }

    const std::string& AudioTagMap::TOTALDISCNUMBER() {
        static const std::string _TOTALDISCNUMBER = "TOTALDISCNUMBER"s;
        return _TOTALDISCNUMBER;
    }

    const std::string& AudioTagMap::TOTALTRACKNUMBER() {
        static const std::string _TOTALTRACKNUMBER = "TOTALTRACKNUMBER"s;
        return _TOTALTRACKNUMBER;
    }

    const std::string& AudioTagMap::TRACKNUMBER() {
        static const std::string _TRACKNUMBER = "TRACKNUMBER"s;
        return _TRACKNUMBER;
    }

    const std::string& AudioTagMap::WWWCOMMERCIAL() {
        static const std::string _WWWCOMMERCIAL = "WWWCOMMERCIAL"s;
        return _WWWCOMMERCIAL;
    }

    const std::string& AudioTagMap::WWWCOPYRIGHT() {
        static const std::string _WWWCOPYRIGHT = "WWWCOPYRIGHT"s;
        return _WWWCOPYRIGHT;
    }

    const std::string& AudioTagMap::WWWFILE() {
        static const std::string _WWWFILE = "WWWFILE"s;
        return _WWWFILE;
    }

    const std::string& AudioTagMap::WWWARTIST() {
        static const std::string _WWWARTIST = "WWWARTIST"s;
        return _WWWARTIST;
    }

    const std::string& AudioTagMap::WWWFILESOURCE() {
        static const std::string _WWWFILESOURCE = "WWWFILESOURCE"s;
        return _WWWFILESOURCE;
    }

    const std::string& AudioTagMap::WWWPAYMENT() {
        static const std::string _WWWPAYMENT = "WWWPAYMENT"s;
        return _WWWPAYMENT;
    }

    const std::string& AudioTagMap::WWWPODCAST() {
        static const std::string _WWWPODCAST = "WWWPODCAST"s;
        return _WWWPODCAST;
    }

    const std::string& AudioTagMap::WWWPUBLISHER() {
        static const std::string _WWWPUBLISHER = "WWWPUBLISHER"s;
        return _WWWPUBLISHER;
    }

    const std::string& AudioTagMap::WWWRADIOPAGE() {
        static const std::string _WWWRADIOPAGE = "WWWRADIOPAGE"s;
        return _WWWRADIOPAGE;
    }






    AudioTagMap::iterator AudioTagMap::begin() {
        return iterator(tagMap.begin());
    }
    AudioTagMap::const_iterator AudioTagMap::begin() const {
        return cbegin();
    }
    AudioTagMap::const_iterator AudioTagMap::cbegin() const {
        return const_iterator(const_cast<AudioTagMap*>(this)->tagMap.begin());
    }




    AudioTagMap::iterator AudioTagMap::end() {
        return iterator(tagMap.end());
    }

    AudioTagMap::const_iterator AudioTagMap::end() const {
        return cend();
    }

    AudioTagMap::const_iterator AudioTagMap::cend() const {
        return const_iterator(const_cast<AudioTagMap*>(this)->tagMap.begin());
    }

    void AudioTagMap::merge(AudioTagMap & source) {
        tagMap.merge(source.tagMap);

    }

    void AudioTagMap::merge(AudioTagMap && source) {
        tagMap.merge(source.tagMap);
    }




    void AudioTagMap::mergeWithOverwrite(AudioTagMap & source) {
        for (auto &item : source.tagMap)
            tagMap.erase(item.first);
        tagMap.merge(source.tagMap);
    }

    void AudioTagMap::mergeWithOverwrite(AudioTagMap && source) {
        for (auto &item : source.tagMap)
            tagMap.erase(item.first);
        tagMap.merge(source.tagMap);
    }





    void AudioTagMap::clear() {
        tagMap.clear();
    }

    std::size_t AudioTagMap::getSize() const noexcept {
        return tagMap.size();
    }

    bool AudioTagMap::isEmpty() const noexcept {
        return tagMap.empty();
    }

    bool AudioTagMap::containsTag(const std::string_view &name) const {
        return tagMap.find(name) != tagMap.end();
    }

    bool AudioTagMap::removeTag(const std::string &name) {
        return tagMap.erase(name) > 0;
    }

    std::size_t AudioTagMap::removeEmpty() {
        std::size_t count = 0;
        for (auto it = tagMap.begin(); it != tagMap.end();) {
            if (it->second->isEmpty()) {
                it = tagMap.erase(it);
                ++count;
            } else {
                ++it;
            }
        }
        return count;
    }





    AudioTagMap::iterator AudioTagMap::getTagIterator(const std::string_view & name) {
        return iterator(tagMap.find(name));
    }

    AudioTagMap::const_iterator AudioTagMap::getTagIterator(const std::string_view & name) const {
        return iterator(const_cast<AudioTagMap*>(this)->tagMap.find(name));
    }

    SharedConstAudioTag AudioTagMap::getTagPointer(const std::string_view &name) const {
        const_iterator it = getTagIterator(name);
        if (it != end())
            return *it;
        return SharedConstAudioTag();
    }

    SharedAudioTag AudioTagMap::getTagPointer(const std::string_view &name) {
        iterator it = getTagIterator(name);
        if (it != end())
            return *it;
        return SharedAudioTag();
    }








    SharedStringAudioTag AudioTagMap::getStringTagPointer(const std::string_view &name) {
        return getTypeTagPointer<StringAudioTag>(name);
    }

    SharedConstStringAudioTag AudioTagMap::getStringTagPointer(const std::string_view &name) const {
        return getTypeTagPointer<StringAudioTag>(name);
    }

    std::optional<std::string> AudioTagMap::getStringTagOptional(const std::string_view &name) const {
        auto tag = getStringTagPointer(name);
        if (tag == nullptr)
            return std::nullopt;
        return tag->getText();
    }

    std::string AudioTagMap::getStringTag(const std::string_view &name) const {
        auto tag = getStringTagPointer(name);
        if (tag == nullptr)
            return std::string();
        return tag->getText();
    }

    bool AudioTagMap::setStringTag(const std::string_view & name, const std::string & text) {
        if (boost::starts_with(name, LYRICS()))
            return false;
        bool defined = TAG_NAMES.find(name) != TAG_NAMES.end();
        bool stringDefined = STRING_TAG_NAMES.find(name) != STRING_TAG_NAMES.end();

        if (!stringDefined && defined)
            return false;
        SharedStringAudioTag tag = getStringTagPointer(name);
        if (tag != nullptr)
            tag->setText(text);
        else
            tagMap.insert(std::make_pair(std::string(name), std::make_shared<StringAudioTag>(std::string(name), text)));
        return true;
    }





    SharedNumberAudioTag AudioTagMap::getNumberTagPointer(const std::string_view &name) {
        return getTypeTagPointer<NumberAudioTag>(name);
    }

    SharedConstNumberAudioTag AudioTagMap::getNumberTagPointer(const std::string_view &name) const {
        return getTypeTagPointer<NumberAudioTag>(name);
    }

    std::optional<std::uint32_t> AudioTagMap::getNumberTagOptional(const std::string_view &name) const {
        auto tag = getNumberTagPointer(name);
        if (tag == nullptr)
            return std::nullopt;
        return tag->getNumber();
    }

    std::uint32_t AudioTagMap::getNumberTag(const std::string_view &name) const {
        auto tag = getNumberTagPointer(name);
        if (tag == nullptr)
            return std::uint32_t(-1);
        return tag->getNumber();
    }

    bool AudioTagMap::setNumberTag(const std::string_view & name, std::uint32_t number) {
        if (boost::starts_with(name, LYRICS()))
            return false;
        bool numberDefined = NUMBER_TAG_NAMES.find(name) != NUMBER_TAG_NAMES.end();
        if (!numberDefined)
            return false;
        SharedNumberAudioTag tag = getNumberTagPointer(name);
        if (tag != nullptr)
            tag->setNumber(number);
        else
            tagMap.insert(std::make_pair(std::string(name), std::make_shared<NumberAudioTag>(std::string(name), number)));
        return true;
    }



    SharedDateAudioTag AudioTagMap::getDateTagPointer(const std::string_view &name) {
        return getTypeTagPointer<DateAudioTag>(name);
    }

    SharedConstDateAudioTag AudioTagMap::getDateTagPointer(const std::string_view &name) const {
        return getTypeTagPointer<DateAudioTag>(name);
    }

    std::optional<types::Date> AudioTagMap::getDateTagOptional(const std::string_view &name) const {
        auto tag = getDateTagPointer(name);
        if (tag == nullptr)
            return std::nullopt;
        return tag->getDate();
    }

    types::Date AudioTagMap::getDateTag(const std::string_view &name) const {
        auto tag = getDateTagPointer(name);
        if (tag == nullptr)
            return types::Date();
        return tag->getDate();
    }

    bool AudioTagMap::setDateTag(const std::string_view & name, const types::Date &date) {
        if (boost::starts_with(name, LYRICS()))
            return false;
        bool dateDefined = DATE_TAG_NAMES.find(name) != DATE_TAG_NAMES.end();
        if (!dateDefined)
            return false;
        SharedDateAudioTag tag = getDateTagPointer(name);
        if (tag != nullptr)
            tag->setDate(date);
        else
            tagMap.insert(std::make_pair(std::string(name), std::make_shared<DateAudioTag>(std::string(name), date)));
        return true;
    }




    SharedLyricsAudioTag AudioTagMap::getLyricsTagPointerByLang(std::string language) {
        boost::to_upper(language);
        return getTypeTagPointer<LyricsAudioTag>(LYRICS() + language);
    }

    SharedConstLyricsAudioTag AudioTagMap::getLyricsTagPointerByLang(std::string language) const {
        boost::to_upper(language);
        return getTypeTagPointer<LyricsAudioTag>(LYRICS() + language);
    }

    SharedLyricsAudioTag AudioTagMap::getLyricsTagPointer(const std::string_view &name) {
        return getTypeTagPointer<LyricsAudioTag>(name);
    }

    SharedConstLyricsAudioTag AudioTagMap::getLyricsTagPointer(const std::string_view &name) const {
        return getTypeTagPointer<LyricsAudioTag>(name);
    }

    std::optional<types::Lyrics> AudioTagMap::getLyricsTagOptionalByLang(std::string language) const {
        auto tag = getLyricsTagPointerByLang(std::move(language));
        if (tag == nullptr)
            return std::nullopt;
        return tag->getLyrics();
    }

    std::optional<types::Lyrics> AudioTagMap::getLyricsTagOptional(const std::string_view &name) const {
        auto tag = getLyricsTagPointer(name);
        if (tag == nullptr)
            return std::nullopt;
        return tag->getLyrics();
    }

    types::Lyrics AudioTagMap::getLyricsTagByLang(std::string language) const {
        auto tag = getLyricsTagPointerByLang(std::move(language));
        if (tag == nullptr)
            return types::Lyrics();
        return tag->getLyrics();
    }

    types::Lyrics AudioTagMap::getLyricsTag(const std::string_view &name) const {
        auto tag = getLyricsTagPointer(name);
        if (tag == nullptr)
            return types::Lyrics();
        return tag->getLyrics();    }

    bool AudioTagMap::setLyricsTagByLang(const std::string & language, const types::Lyrics & lyrics) {
        if (language.empty())
            return false;
        std::string name = LYRICS() + boost::to_upper_copy(language);
        SharedLyricsAudioTag tag = getLyricsTagPointerByLang(name);
        if (tag != nullptr)
            tag->setLyrics(lyrics);
        else
            tagMap.insert(std::make_pair(name, std::make_shared<LyricsAudioTag>(language, lyrics)));
        return true;
    }

    bool AudioTagMap::setLyricsTag(const std::string_view & name, const types::Lyrics & lyrics) {
        if (!boost::starts_with(LYRICS(), name))
            return false;
        if (name == LYRICS())
            return false;
        SharedLyricsAudioTag tag = getLyricsTagPointer(name);
        if (tag != nullptr) {
            tag->setLyrics(lyrics);
        } else {
            std::string language = std::string(name.substr(LYRICS().size()));
            tagMap.insert(std::make_pair(std::string(name), std::make_shared<LyricsAudioTag>(language, lyrics)));
        }
        return true;
    }



    SharedImageAudioTag AudioTagMap::getImageTagPointer(const std::string_view &name) {
        return getTypeTagPointer<ImageAudioTag>(name);

    }

    SharedImageAudioTag AudioTagMap::getImageTagPointer(ImageAudioTag::ImageType imageType) {
        return getImageTagPointer(string::toString(imageType));
    }

    SharedConstImageAudioTag AudioTagMap::getImageTagPointer(const std::string_view &name) const {
        return getTypeTagPointer<ImageAudioTag>(name);
    }

    SharedConstImageAudioTag AudioTagMap::getImageTagPointer(ImageAudioTag::ImageType imageType) const {
        return getImageTagPointer(string::toString(imageType));
    }

    std::optional<types::Image> AudioTagMap::getImageTagOptional(const std::string_view &name) const {
        auto tag = getImageTagPointer(name);
        if (tag == nullptr)
            return std::nullopt;
        return tag->getImage();
    }

    std::optional<types::Image> AudioTagMap::getImageTagOptional(ImageAudioTag::ImageType imageType) const {
        auto tag = getImageTagPointer(imageType);
        if (tag == nullptr)
            return std::nullopt;
        return tag->getImage();
    }

    types::Image AudioTagMap::getImageTag(const std::string_view &name) const {
        auto tag = getImageTagPointer(name);
        if (tag == nullptr)
            return types::Image();
        return tag->getImage();
    }

    types::Image AudioTagMap::getImageTag(ImageAudioTag::ImageType imageType) const {
        auto tag = getImageTagPointer(imageType);
        if (tag == nullptr)
            return types::Image();
        return tag->getImage();
    }

    bool AudioTagMap::setImageTag(const std::string_view & name, const types::Image & image) {
        if (boost::starts_with(name, LYRICS()))
            return false;
        bool imageDefined = IMAGE_TAG_NAMES.find(name) != IMAGE_TAG_NAMES.end();
        if (!imageDefined)
            return false;
        SharedImageAudioTag tag = getImageTagPointer(name);
        if (tag != nullptr)
            tag->setImage(image);
        else
            tagMap.insert(std::make_pair(std::string(name), std::make_shared<ImageAudioTag>(std::string(name), image)));
        return true;
    }

    bool AudioTagMap::setImageTag(const std::string_view & name, types::Image && image) {
        if (boost::starts_with(name, LYRICS()))
            return false;
        bool imageDefined = IMAGE_TAG_NAMES.find(name) != IMAGE_TAG_NAMES.end();
        if (!imageDefined)
            return false;
        SharedImageAudioTag tag = getImageTagPointer(name);
        if (tag != nullptr)
            tag->setImage(std::move(image));
        else
            tagMap.insert(std::make_pair(std::string(name), std::make_shared<ImageAudioTag>(std::string(name), std::move(image))));
        return true;
    }

    bool AudioTagMap::setImageTag(ImageAudioTag::ImageType imageType, const types::Image & image) {
        return setImageTag(string::toString(imageType), image);
    }

    bool AudioTagMap::setImageTag(ImageAudioTag::ImageType imageType, types::Image && image) {
        return setImageTag(string::toString(imageType), std::move(image));
    }



    SharedConstISRCAudioTag AudioTagMap::getISRCTagPointer(const std::string_view &name) const {
        return getTypeTagPointer<ISRCAudioTag>(name);

    }

    SharedISRCAudioTag AudioTagMap::getISRCTagPointer(const std::string_view &name) {
        return getTypeTagPointer<ISRCAudioTag>(name);
    }

    std::optional<types::ISRC> AudioTagMap::getISRCTagOptional(const std::string_view &name) const {
        auto tag = getISRCTagPointer(name);
        if (tag == nullptr)
            return std::nullopt;
        return tag->getISRC();
    }

    types::ISRC AudioTagMap::getISRCTag(const std::string_view &name) const {
        auto tag = getISRCTagPointer(name);
        if (tag == nullptr)
            return types::ISRC();
        return tag->getISRC();
    }

    bool AudioTagMap::setISRCTag(const std::string_view &name, const types::ISRC & isrc) {
        if (name != ISRC())
            return false;
        SharedISRCAudioTag tag = getISRCTagPointer(name);
        if (tag != nullptr) {
            tag->setISRC(isrc);
            return true;
        } else
            return tagMap.insert(std::make_pair(
                                     ISRC(), std::make_shared<ISRCAudioTag>(isrc)
                                 )).second;
    }



    SharedConstBarcodeAudioTag AudioTagMap::getBarcodeTagPointer(const std::string_view &name) const {
        return getTypeTagPointer<BarcodeAudioTag>(name);

    }

    SharedBarcodeAudioTag AudioTagMap::getBarcodeTagPointer(const std::string_view &name) {
        return getTypeTagPointer<BarcodeAudioTag>(name);
    }

    std::optional<types::Barcode> AudioTagMap::getBarcodeTagOptional(const std::string_view &name) const {
        auto tag = getBarcodeTagPointer(name);
        if (tag == nullptr)
            return std::nullopt;
        return tag->getBarcode();
    }

    types::Barcode AudioTagMap::getBarcodeTag(const std::string_view &name) const {
        auto tag = getBarcodeTagPointer(name);
        if (tag == nullptr)
            return types::Barcode();
        return tag->getBarcode();
    }

    bool AudioTagMap::setBarcodeTag(const std::string_view &name, const types::Barcode & barcode) {
        if (name != BARCODE())
            return false;
        SharedBarcodeAudioTag tag = getBarcodeTagPointer(name);
        if (tag != nullptr) {
            tag->setBarcode(barcode);
            return true;
        } else
            return tagMap.insert(std::make_pair(
                    BARCODE(), std::make_shared<BarcodeAudioTag>(barcode)
            )).second;
    }











    SharedConstStringAudioTag AudioTagMap::getAlbumPointer() const {
        return getStringTagPointer(ALBUM());
    }

    SharedStringAudioTag AudioTagMap::getAlbumPointer() {
        return getStringTagPointer(ALBUM());
    }

    std::optional<std::string> AudioTagMap::getAlbumOptional() const {
        return getStringTagOptional(ALBUM());
    }

    std::string AudioTagMap::getAlbum() const {
        return getStringTag(ALBUM());
    }

    bool AudioTagMap::setAlbum(const std::string& album) {
        return setStringTag(ALBUM(), album);
    }



    SharedConstStringAudioTag AudioTagMap::getAlbumArtistPointer() const {
        return getStringTagPointer(ALBUMARTIST());
    }

    SharedStringAudioTag AudioTagMap::getAlbumArtistPointer() {
        return getStringTagPointer(ALBUMARTIST());
    }

    std::optional<std::string> AudioTagMap::getAlbumArtistOptional() const {
        return getStringTagOptional(ALBUMARTIST());
    }

    std::string AudioTagMap::getAlbumArtist() const {
        return getStringTag(ALBUMARTIST());
    }

    bool AudioTagMap::setAlbumArtist(const std::string& albumArtist) {
        return setStringTag(ALBUMARTIST(), albumArtist);
    }



    SharedConstStringAudioTag AudioTagMap::getAlbumArtistSortPointer() const {
        return getStringTagPointer(ALBUMARTISTSORT());
    }

    SharedStringAudioTag AudioTagMap::getAlbumArtistSortPointer() {
        return getStringTagPointer(ALBUMARTISTSORT());
    }

    std::optional<std::string> AudioTagMap::getAlbumArtistSortOptional() const {
        return getStringTagOptional(ALBUMARTISTSORT());
    }

    std::string AudioTagMap::getAlbumArtistSort() const {
        return getStringTag(ALBUMARTISTSORT());
    }

    bool AudioTagMap::setAlbumArtistSort(const std::string& albumArtistSort) {
        return setStringTag(ALBUMARTISTSORT(), albumArtistSort);
    }



    SharedConstStringAudioTag AudioTagMap::getAlbumSortPointer() const {
        return getStringTagPointer(ALBUMSORT());
    }

    SharedStringAudioTag AudioTagMap::getAlbumSortPointer() {
        return getStringTagPointer(ALBUMSORT());
    }

    std::optional<std::string> AudioTagMap::getAlbumSortOptional() const {
        return getStringTagOptional(ALBUMSORT());
    }

    std::string AudioTagMap::getAlbumSort() const {
        return getStringTag(ALBUMSORT());
    }

    bool AudioTagMap::setAlbumSort(const std::string& albumSort) {
        return setStringTag(ALBUMSORT(), albumSort);
    }



    SharedConstStringAudioTag AudioTagMap::getArrangerPointer() const {
        return getStringTagPointer(ARRANGER());
    }

    SharedStringAudioTag AudioTagMap::getArrangerPointer() {
        return getStringTagPointer(ARRANGER());
    }

    std::optional<std::string> AudioTagMap::getArrangerOptional() const {
        return getStringTagOptional(ARRANGER());
    }

    std::string AudioTagMap::getArranger() const {
        return getStringTag(ARRANGER());
    }

    bool AudioTagMap::setArranger(const std::string& arranger) {
        return setStringTag(ARRANGER(), arranger);
    }



    SharedConstStringAudioTag AudioTagMap::getArtistPointer() const {
        return getStringTagPointer(ARTIST());
    }

    SharedStringAudioTag AudioTagMap::getArtistPointer() {
        return getStringTagPointer(ARTIST());
    }

    std::optional<std::string> AudioTagMap::getArtistOptional() const {
        return getStringTagOptional(ARTIST());
    }

    std::string AudioTagMap::getArtist() const {
        return getStringTag(ARTIST());
    }

    bool AudioTagMap::setArtist(const std::string& artist) {
        return setStringTag(ARTIST(), artist);
    }



    SharedConstStringAudioTag AudioTagMap::getArtistSortPointer() const {
        return getStringTagPointer(ARTISTSORT());
    }

    SharedStringAudioTag AudioTagMap::getArtistSortPointer() {
        return getStringTagPointer(ARTISTSORT());
    }

    std::optional<std::string> AudioTagMap::getArtistSortOptional() const {
        return getStringTagOptional(ARTISTSORT());
    }

    std::string AudioTagMap::getArtistSort() const {
        return getStringTag(ARTISTSORT());
    }

    bool AudioTagMap::setArtistSort(const std::string& artistSort) {
        return setStringTag(ARTISTSORT(), artistSort);
    }



    SharedConstStringAudioTag AudioTagMap::getCommentPointer() const {
        return getStringTagPointer(COMMENT());
    }

    SharedStringAudioTag AudioTagMap::getCommentPointer() {
        return getStringTagPointer(COMMENT());
    }

    std::optional<std::string> AudioTagMap::getCommentOptional() const {
        return getStringTagOptional(COMMENT());
    }

    std::string AudioTagMap::getComment() const {
        return getStringTag(COMMENT());
    }

    bool AudioTagMap::setComment(const std::string& comment) {
        return setStringTag(COMMENT(), comment);
    }



    SharedConstStringAudioTag AudioTagMap::getComposerPointer() const {
        return getStringTagPointer(COMPOSER());
    }

    SharedStringAudioTag AudioTagMap::getComposerPointer() {
        return getStringTagPointer(COMPOSER());
    }

    std::optional<std::string> AudioTagMap::getComposerOptional() const {
        return getStringTagOptional(COMPOSER());
    }

    std::string AudioTagMap::getComposer() const {
        return getStringTag(COMPOSER());
    }

    bool AudioTagMap::setComposer(const std::string& composer) {
        return setStringTag(COMPOSER(), composer);
    }



    SharedConstStringAudioTag AudioTagMap::getComposerSortPointer() const {
        return getStringTagPointer(COMPOSERSORT());
    }

    SharedStringAudioTag AudioTagMap::getComposerSortPointer() {
        return getStringTagPointer(COMPOSERSORT());
    }

    std::optional<std::string> AudioTagMap::getComposerSortOptional() const {
        return getStringTagOptional(COMPOSERSORT());
    }

    std::string AudioTagMap::getComposerSort() const {
        return getStringTag(COMPOSERSORT());
    }

    bool AudioTagMap::setComposerSort(const std::string& composerSort) {
        return setStringTag(COMPOSERSORT(), composerSort);
    }



    SharedConstStringAudioTag AudioTagMap::getConductorPointer() const {
        return getStringTagPointer(CONDUCTOR());
    }

    SharedStringAudioTag AudioTagMap::getConductorPointer() {
        return getStringTagPointer(CONDUCTOR());
    }

    std::optional<std::string> AudioTagMap::getConductorOptional() const {
        return getStringTagOptional(CONDUCTOR());
    }

    std::string AudioTagMap::getConductor() const {
        return getStringTag(CONDUCTOR());
    }

    bool AudioTagMap::setConductor(const std::string& conductor) {
        return setStringTag(CONDUCTOR(), conductor);
    }



    SharedConstStringAudioTag AudioTagMap::getContentGroupPointer() const {
        return getStringTagPointer(CONTENTGROUP());
    }

    SharedStringAudioTag AudioTagMap::getContentGroupPointer() {
        return getStringTagPointer(CONTENTGROUP());
    }

    std::optional<std::string> AudioTagMap::getContentGroupOptional() const {
        return getStringTagOptional(CONTENTGROUP());
    }

    std::string AudioTagMap::getContentGroup() const {
        return getStringTag(CONTENTGROUP());
    }

    bool AudioTagMap::setContentGroup(const std::string& contentGroup) {
        return setStringTag(CONTENTGROUP(), contentGroup);
    }



    SharedConstStringAudioTag AudioTagMap::getCopyrightPointer() const {
        return getStringTagPointer(COPYRIGHT());
    }

    SharedStringAudioTag AudioTagMap::getCopyrightPointer() {
        return getStringTagPointer(COPYRIGHT());
    }

    std::optional<std::string> AudioTagMap::getCopyrightOptional() const {
        return getStringTagOptional(COPYRIGHT());
    }

    std::string AudioTagMap::getCopyright() const {
        return getStringTag(COPYRIGHT());
    }

    bool AudioTagMap::setCopyright(const std::string& copyright) {
        return setStringTag(COPYRIGHT(), copyright);
    }



    SharedConstStringAudioTag AudioTagMap::getEngineerPointer() const {
        return getStringTagPointer(ENGINEER());
    }

    SharedStringAudioTag AudioTagMap::getEngineerPointer() {
        return getStringTagPointer(ENGINEER());
    }

    std::optional<std::string> AudioTagMap::getEngineerOptional() const {
        return getStringTagOptional(ENGINEER());
    }

    std::string AudioTagMap::getEngineer() const {
        return getStringTag(ENGINEER());
    }

    bool AudioTagMap::setEngineer(const std::string& engineer) {
        return setStringTag(ENGINEER(), engineer);
    }



    SharedConstStringAudioTag AudioTagMap::getEncodedBYPointer() const {
        return getStringTagPointer(ENCODEDBY());
    }

    SharedStringAudioTag AudioTagMap::getEncodedBYPointer() {
        return getStringTagPointer(ENCODEDBY());
    }

    std::optional<std::string> AudioTagMap::getEncodedBYOptional() const {
        return getStringTagOptional(ENCODEDBY());
    }

    std::string AudioTagMap::getEncodedBY() const {
        return getStringTag(ENCODEDBY());
    }

    bool AudioTagMap::setEncodedBY(const std::string& encodedBY) {
        return setStringTag(ENCODEDBY(), encodedBY);
    }



    SharedConstStringAudioTag AudioTagMap::getEncoderSettingsPointer() const {
        return getStringTagPointer(ENCODERSETTINGS());
    }

    SharedStringAudioTag AudioTagMap::getEncoderSettingsPointer() {
        return getStringTagPointer(ENCODERSETTINGS());
    }

    std::optional<std::string> AudioTagMap::getEncoderSettingsOptional() const {
        return getStringTagOptional(ENCODERSETTINGS());
    }

    std::string AudioTagMap::getEncoderSettings() const {
        return getStringTag(ENCODERSETTINGS());
    }

    bool AudioTagMap::setEncoderSettings(const std::string& encoderSettings) {
        return setStringTag(ENCODERSETTINGS(), encoderSettings);
    }



    SharedConstStringAudioTag AudioTagMap::getGenrePointer() const {
        return getStringTagPointer(GENRE());
    }

    SharedStringAudioTag AudioTagMap::getGenrePointer() {
        return getStringTagPointer(GENRE());
    }

    std::optional<std::string> AudioTagMap::getGenreOptional() const {
        return getStringTagOptional(GENRE());
    }

    std::string AudioTagMap::getGenre() const {
        return getStringTag(GENRE());
    }

    bool AudioTagMap::setGenre(const std::string& genre) {
        return setStringTag(GENRE(), genre);
    }



    SharedConstStringAudioTag AudioTagMap::getInitialKeyPointer() const {
        return getStringTagPointer(INITIALKEY());
    }

    SharedStringAudioTag AudioTagMap::getInitialKeyPointer() {
        return getStringTagPointer(INITIALKEY());
    }

    std::optional<std::string> AudioTagMap::getInitialKeyOptional() const {
        return getStringTagOptional(INITIALKEY());
    }

    std::string AudioTagMap::getInitialKey() const {
        return getStringTag(INITIALKEY());
    }

    bool AudioTagMap::setInitialKey(const std::string& initialKey) {
        return setStringTag(INITIALKEY(), initialKey);
    }



    SharedConstStringAudioTag AudioTagMap::getLyricistPointer() const {
        return getStringTagPointer(LYRICIST());
    }

    SharedStringAudioTag AudioTagMap::getLyricistPointer() {
        return getStringTagPointer(LYRICIST());
    }

    std::optional<std::string> AudioTagMap::getLyricistOptional() const {
        return getStringTagOptional(LYRICIST());
    }

    std::string AudioTagMap::getLyricist() const {
        return getStringTag(LYRICIST());
    }

    bool AudioTagMap::setLyricist(const std::string& lyricist) {
        return setStringTag(LYRICIST(), lyricist);
    }



    SharedConstStringAudioTag AudioTagMap::getMixDJPointer() const {
        return getStringTagPointer(MIXDJ());
    }

    SharedStringAudioTag AudioTagMap::getMixDJPointer() {
        return getStringTagPointer(MIXDJ());
    }

    std::optional<std::string> AudioTagMap::getMixDJOptional() const {
        return getStringTagOptional(MIXDJ());
    }

    std::string AudioTagMap::getMixDJ() const {
        return getStringTag(MIXDJ());
    }

    bool AudioTagMap::setMixDJ(const std::string& mixDJ) {
        return setStringTag(MIXDJ(), mixDJ);
    }



    SharedConstStringAudioTag AudioTagMap::getMixEngineerPointer() const {
        return getStringTagPointer(MIXENGINEER());
    }

    SharedStringAudioTag AudioTagMap::getMixEngineerPointer() {
        return getStringTagPointer(MIXENGINEER());
    }

    std::optional<std::string> AudioTagMap::getMixEngineerOptional() const {
        return getStringTagOptional(MIXENGINEER());
    }

    std::string AudioTagMap::getMixEngineer() const {
        return getStringTag(MIXENGINEER());
    }

    bool AudioTagMap::setMixEngineer(const std::string& mixEngineer) {
        return setStringTag(MIXENGINEER(), mixEngineer);
    }



    SharedConstStringAudioTag AudioTagMap::getMoodPointer() const {
        return getStringTagPointer(MOOD());
    }

    SharedStringAudioTag AudioTagMap::getMoodPointer() {
        return getStringTagPointer(MOOD());
    }

    std::optional<std::string> AudioTagMap::getMoodOptional() const {
        return getStringTagOptional(MOOD());
    }

    std::string AudioTagMap::getMood() const {
        return getStringTag(MOOD());
    }

    bool AudioTagMap::setMood(const std::string& mood) {
        return setStringTag(MOOD(), mood);
    }



    SharedConstStringAudioTag AudioTagMap::getOriginalLyricistPointer() const {
        return getStringTagPointer(ORIGINALLYRICIST());
    }

    SharedStringAudioTag AudioTagMap::getOriginalLyricistPointer() {
        return getStringTagPointer(ORIGINALLYRICIST());
    }

    std::optional<std::string> AudioTagMap::getOriginalLyricistOptional() const {
        return getStringTagOptional(ORIGINALLYRICIST());
    }

    std::string AudioTagMap::getOriginalLyricist() const {
        return getStringTag(ORIGINALLYRICIST());
    }

    bool AudioTagMap::setOriginalLyricist(const std::string& originalLyricist) {
        return setStringTag(ORIGINALLYRICIST(), originalLyricist);
    }



    SharedConstStringAudioTag AudioTagMap::getOriginalAlbumPointer() const {
        return getStringTagPointer(ORIGINALALBUM());
    }

    SharedStringAudioTag AudioTagMap::getOriginalAlbumPointer() {
        return getStringTagPointer(ORIGINALALBUM());
    }

    std::optional<std::string> AudioTagMap::getOriginalAlbumOptional() const {
        return getStringTagOptional(ORIGINALALBUM());
    }

    std::string AudioTagMap::getOriginalAlbum() const {
        return getStringTag(ORIGINALALBUM());
    }

    bool AudioTagMap::setOriginalAlbum(const std::string& originalAlbum) {
        return setStringTag(ORIGINALALBUM(), originalAlbum);
    }



    SharedConstStringAudioTag AudioTagMap::getOriginalArtistPointer() const {
        return getStringTagPointer(ORIGINALARTIST());
    }

    SharedStringAudioTag AudioTagMap::getOriginalArtistPointer() {
        return getStringTagPointer(ORIGINALARTIST());
    }

    std::optional<std::string> AudioTagMap::getOriginalArtistOptional() const {
        return getStringTagOptional(ORIGINALARTIST());
    }

    std::string AudioTagMap::getOriginalArtist() const {
        return getStringTag(ORIGINALARTIST());
    }

    bool AudioTagMap::setOriginalArtist(const std::string& originalArtist) {
        return setStringTag(ORIGINALARTIST(), originalArtist);
    }



    SharedConstStringAudioTag AudioTagMap::getProducerPointer() const {
        return getStringTagPointer(PRODUCER());
    }

    SharedStringAudioTag AudioTagMap::getProducerPointer() {
        return getStringTagPointer(PRODUCER());
    }

    std::optional<std::string> AudioTagMap::getProducerOptional() const {
        return getStringTagOptional(PRODUCER());
    }

    std::string AudioTagMap::getProducer() const {
        return getStringTag(PRODUCER());
    }

    bool AudioTagMap::setProducer(const std::string& producer) {
        return setStringTag(PRODUCER(), producer);
    }



    SharedConstStringAudioTag AudioTagMap::getPublisherPointer() const {
        return getStringTagPointer(PUBLISHER());
    }

    SharedStringAudioTag AudioTagMap::getPublisherPointer() {
        return getStringTagPointer(PUBLISHER());
    }

    std::optional<std::string> AudioTagMap::getPublisherOptional() const {
        return getStringTagOptional(PUBLISHER());
    }

    std::string AudioTagMap::getPublisher() const {
        return getStringTag(PUBLISHER());
    }

    bool AudioTagMap::setPublisher(const std::string& publisher) {
        return setStringTag(PUBLISHER(), publisher);
    }



    SharedConstStringAudioTag AudioTagMap::getRadioStationPointer() const {
        return getStringTagPointer(RADIOSTATION());
    }

    SharedStringAudioTag AudioTagMap::getRadioStationPointer() {
        return getStringTagPointer(RADIOSTATION());
    }

    std::optional<std::string> AudioTagMap::getRadioStationOptional() const {
        return getStringTagOptional(RADIOSTATION());
    }

    std::string AudioTagMap::getRadioStation() const {
        return getStringTag(RADIOSTATION());
    }

    bool AudioTagMap::setRadioStation(const std::string& radioStation) {
        return setStringTag(RADIOSTATION(), radioStation);
    }



    SharedConstStringAudioTag AudioTagMap::getRadioStationOwnerPointer() const {
        return getStringTagPointer(RADIOSTATIONOWNER());
    }

    SharedStringAudioTag AudioTagMap::getRadioStationOwnerPointer() {
        return getStringTagPointer(RADIOSTATIONOWNER());
    }

    std::optional<std::string> AudioTagMap::getRadioStationOwnerOptional() const {
        return getStringTagOptional(RADIOSTATIONOWNER());
    }

    std::string AudioTagMap::getRadioStationOwner() const {
        return getStringTag(RADIOSTATIONOWNER());
    }

    bool AudioTagMap::setRadioStationOwner(const std::string& radioStationOwner) {
        return setStringTag(RADIOSTATIONOWNER(), radioStationOwner);
    }



    SharedConstStringAudioTag AudioTagMap::getRemixerPointer() const {
        return getStringTagPointer(REMIXER());
    }

    SharedStringAudioTag AudioTagMap::getRemixerPointer() {
        return getStringTagPointer(REMIXER());
    }

    std::optional<std::string> AudioTagMap::getRemixerOptional() const {
        return getStringTagOptional(REMIXER());
    }

    std::string AudioTagMap::getRemixer() const {
        return getStringTag(REMIXER());
    }

    bool AudioTagMap::setRemixer(const std::string& remixer) {
        return setStringTag(REMIXER(), remixer);
    }



    SharedConstStringAudioTag AudioTagMap::getSetSubtitlePointer() const {
        return getStringTagPointer(SETSUBTITLE());
    }

    SharedStringAudioTag AudioTagMap::getSetSubtitlePointer() {
        return getStringTagPointer(SETSUBTITLE());
    }

    std::optional<std::string> AudioTagMap::getSetSubtitleOptional() const {
        return getStringTagOptional(SETSUBTITLE());
    }

    std::string AudioTagMap::getSetSubtitle() const {
        return getStringTag(SETSUBTITLE());
    }

    bool AudioTagMap::setSetSubtitle(const std::string& setSubtitle) {
        return setStringTag(SETSUBTITLE(), setSubtitle);
    }



    SharedConstStringAudioTag AudioTagMap::getSubtitlePointer() const {
        return getStringTagPointer(SUBTITLE());
    }

    SharedStringAudioTag AudioTagMap::getSubtitlePointer() {
        return getStringTagPointer(SUBTITLE());
    }

    std::optional<std::string> AudioTagMap::getSubtitleOptional() const {
        return getStringTagOptional(SUBTITLE());
    }

    std::string AudioTagMap::getSubtitle() const {
        return getStringTag(SUBTITLE());
    }

    bool AudioTagMap::setSubtitle(const std::string& subtitle) {
        return setStringTag(SUBTITLE(), subtitle);
    }



    SharedConstStringAudioTag AudioTagMap::getTitlePointer() const {
        return getStringTagPointer(TITLE());
    }

    SharedStringAudioTag AudioTagMap::getTitlePointer() {
        return getStringTagPointer(TITLE());
    }

    std::optional<std::string> AudioTagMap::getTitleOptional() const {
        return getStringTagOptional(TITLE());
    }

    std::string AudioTagMap::getTitle() const {
        return getStringTag(TITLE());
    }

    bool AudioTagMap::setTitle(const std::string& title) {
        return setStringTag(TITLE(), title);
    }



    SharedConstStringAudioTag AudioTagMap::getTitleSortPointer() const {
        return getStringTagPointer(TITLESORT());
    }

    SharedStringAudioTag AudioTagMap::getTitleSortPointer() {
        return getStringTagPointer(TITLESORT());
    }

    std::optional<std::string> AudioTagMap::getTitleSortOptional() const {
        return getStringTagOptional(TITLESORT());
    }

    std::string AudioTagMap::getTitleSort() const {
        return getStringTag(TITLESORT());
    }

    bool AudioTagMap::setTitleSort(const std::string& titleSort) {
        return setStringTag(TITLESORT(), titleSort);
    }



    SharedConstStringAudioTag AudioTagMap::getWWWCommercialPointer() const {
        return getStringTagPointer(WWWCOMMERCIAL());
    }

    SharedStringAudioTag AudioTagMap::getWWWCommercialPointer() {
        return getStringTagPointer(WWWCOMMERCIAL());
    }

    std::optional<std::string> AudioTagMap::getWWWCommercialOptional() const {
        return getStringTagOptional(WWWCOMMERCIAL());
    }

    std::string AudioTagMap::getWWWCommercial() const {
        return getStringTag(WWWCOMMERCIAL());
    }

    bool AudioTagMap::setWWWCommercial(const std::string& wWWCommercial) {
        return setStringTag(WWWCOMMERCIAL(), wWWCommercial);
    }



    SharedConstStringAudioTag AudioTagMap::getWWWCopyrightPointer() const {
        return getStringTagPointer(WWWCOPYRIGHT());
    }

    SharedStringAudioTag AudioTagMap::getWWWCopyrightPointer() {
        return getStringTagPointer(WWWCOPYRIGHT());
    }

    std::optional<std::string> AudioTagMap::getWWWCopyrightOptional() const {
        return getStringTagOptional(WWWCOPYRIGHT());
    }

    std::string AudioTagMap::getWWWCopyright() const {
        return getStringTag(WWWCOPYRIGHT());
    }

    bool AudioTagMap::setWWWCopyright(const std::string& wWWCopyright) {
        return setStringTag(WWWCOPYRIGHT(), wWWCopyright);
    }



    SharedConstStringAudioTag AudioTagMap::getWWWFilePointer() const {
        return getStringTagPointer(WWWFILE());
    }

    SharedStringAudioTag AudioTagMap::getWWWFilePointer() {
        return getStringTagPointer(WWWFILE());
    }

    std::optional<std::string> AudioTagMap::getWWWFileOptional() const {
        return getStringTagOptional(WWWFILE());
    }

    std::string AudioTagMap::getWWWFile() const {
        return getStringTag(WWWFILE());
    }

    bool AudioTagMap::setWWWFile(const std::string& wWWFile) {
        return setStringTag(WWWFILE(), wWWFile);
    }



    SharedConstStringAudioTag AudioTagMap::getWWWArtistPointer() const {
        return getStringTagPointer(WWWARTIST());
    }

    SharedStringAudioTag AudioTagMap::getWWWArtistPointer() {
        return getStringTagPointer(WWWARTIST());
    }

    std::optional<std::string> AudioTagMap::getWWWArtistOptional() const {
        return getStringTagOptional(WWWARTIST());
    }

    std::string AudioTagMap::getWWWArtist() const {
        return getStringTag(WWWARTIST());
    }

    bool AudioTagMap::setWWWArtist(const std::string& wWWArtist) {
        return setStringTag(WWWARTIST(), wWWArtist);
    }



    SharedConstStringAudioTag AudioTagMap::getWWWFileSourcePointer() const {
        return getStringTagPointer(WWWFILESOURCE());
    }

    SharedStringAudioTag AudioTagMap::getWWWFileSourcePointer() {
        return getStringTagPointer(WWWFILESOURCE());
    }

    std::optional<std::string> AudioTagMap::getWWWFileSourceOptional() const {
        return getStringTagOptional(WWWFILESOURCE());
    }

    std::string AudioTagMap::getWWWFileSource() const {
        return getStringTag(WWWFILESOURCE());
    }

    bool AudioTagMap::setWWWFileSource(const std::string& wWWFileSource) {
        return setStringTag(WWWFILESOURCE(), wWWFileSource);
    }



    SharedConstStringAudioTag AudioTagMap::getWWWPaymentPointer() const {
        return getStringTagPointer(WWWPAYMENT());
    }

    SharedStringAudioTag AudioTagMap::getWWWPaymentPointer() {
        return getStringTagPointer(WWWPAYMENT());
    }

    std::optional<std::string> AudioTagMap::getWWWPaymentOptional() const {
        return getStringTagOptional(WWWPAYMENT());
    }

    std::string AudioTagMap::getWWWPayment() const {
        return getStringTag(WWWPAYMENT());
    }

    bool AudioTagMap::setWWWPayment(const std::string& wWWPayment) {
        return setStringTag(WWWPAYMENT(), wWWPayment);
    }



    SharedConstStringAudioTag AudioTagMap::getWWWPodcastPointer() const {
        return getStringTagPointer(WWWPODCAST());
    }

    SharedStringAudioTag AudioTagMap::getWWWPodcastPointer() {
        return getStringTagPointer(WWWPODCAST());
    }

    std::optional<std::string> AudioTagMap::getWWWPodcastOptional() const {
        return getStringTagOptional(WWWPODCAST());
    }

    std::string AudioTagMap::getWWWPodcast() const {
        return getStringTag(WWWPODCAST());
    }

    bool AudioTagMap::setWWWPodcast(const std::string& wWWPodcast) {
        return setStringTag(WWWPODCAST(), wWWPodcast);
    }



    SharedConstStringAudioTag AudioTagMap::getWWWPublisherPointer() const {
        return getStringTagPointer(WWWPUBLISHER());
    }

    SharedStringAudioTag AudioTagMap::getWWWPublisherPointer() {
        return getStringTagPointer(WWWPUBLISHER());
    }

    std::optional<std::string> AudioTagMap::getWWWPublisherOptional() const {
        return getStringTagOptional(WWWPUBLISHER());
    }

    std::string AudioTagMap::getWWWPublisher() const {
        return getStringTag(WWWPUBLISHER());
    }

    bool AudioTagMap::setWWWPublisher(const std::string& wWWPublisher) {
        return setStringTag(WWWPUBLISHER(), wWWPublisher);
    }



    SharedConstStringAudioTag AudioTagMap::getWWWRadioPagePointer() const {
        return getStringTagPointer(WWWRADIOPAGE());
    }

    SharedStringAudioTag AudioTagMap::getWWWRadioPagePointer() {
        return getStringTagPointer(WWWRADIOPAGE());
    }

    std::optional<std::string> AudioTagMap::getWWWRadioPageOptional() const {
        return getStringTagOptional(WWWRADIOPAGE());
    }

    std::string AudioTagMap::getWWWRadioPage() const {
        return getStringTag(WWWRADIOPAGE());
    }

    bool AudioTagMap::setWWWRadioPage(const std::string& wWWRadioPage) {
        return setStringTag(WWWRADIOPAGE(), wWWRadioPage);
    }



    SharedConstNumberAudioTag AudioTagMap::getBPMPointer() const {
        return getNumberTagPointer(BPM());
    }

    SharedNumberAudioTag AudioTagMap::getBPMPointer() {
        return getNumberTagPointer(BPM());
    }

    std::optional<std::uint32_t> AudioTagMap::getBPMOptional() const {
        return getNumberTagOptional(BPM());
    }

    std::uint32_t AudioTagMap::getBPM() const {
        return getNumberTag(BPM());
    }

    bool AudioTagMap::setBPM(std::uint32_t bPM) {
        return setNumberTag(BPM(), bPM);
    }



    SharedConstNumberAudioTag AudioTagMap::getDiscNumberPointer() const {
        return getNumberTagPointer(DISCNUMBER());
    }

    SharedNumberAudioTag AudioTagMap::getDiscNumberPointer() {
        return getNumberTagPointer(DISCNUMBER());
    }

    std::optional<std::uint32_t> AudioTagMap::getDiscNumberOptional() const {
        return getNumberTagOptional(DISCNUMBER());
    }

    std::uint32_t AudioTagMap::getDiscNumber() const {
        return getNumberTag(DISCNUMBER());
    }

    bool AudioTagMap::setDiscNumber(std::uint32_t discNumber) {
        return setNumberTag(DISCNUMBER(), discNumber);
    }



    SharedConstNumberAudioTag AudioTagMap::getTotalDiscNumberPointer() const {
        return getNumberTagPointer(TOTALDISCNUMBER());
    }

    SharedNumberAudioTag AudioTagMap::getTotalDiscNumberPointer() {
        return getNumberTagPointer(TOTALDISCNUMBER());
    }

    std::optional<std::uint32_t> AudioTagMap::getTotalDiscNumberOptional() const {
        return getNumberTagOptional(TOTALDISCNUMBER());
    }

    std::uint32_t AudioTagMap::getTotalDiscNumber() const {
        return getNumberTag(TOTALDISCNUMBER());
    }

    bool AudioTagMap::setTotalDiscNumber(std::uint32_t totalDiscNumber) {
        return setNumberTag(TOTALDISCNUMBER(), totalDiscNumber);
    }



    SharedConstNumberAudioTag AudioTagMap::getTotalTrackNumberPointer() const {
        return getNumberTagPointer(TOTALTRACKNUMBER());
    }

    SharedNumberAudioTag AudioTagMap::getTotalTrackNumberPointer() {
        return getNumberTagPointer(TOTALTRACKNUMBER());
    }

    std::optional<std::uint32_t> AudioTagMap::getTotalTrackNumberOptional() const {
        return getNumberTagOptional(TOTALTRACKNUMBER());
    }

    std::uint32_t AudioTagMap::getTotalTrackNumber() const {
        return getNumberTag(TOTALTRACKNUMBER());
    }

    bool AudioTagMap::setTotalTrackNumber(std::uint32_t totalTrackNumber) {
        return setNumberTag(TOTALTRACKNUMBER(), totalTrackNumber);
    }



    SharedConstNumberAudioTag AudioTagMap::getTrackNumberPointer() const {
        return getNumberTagPointer(TRACKNUMBER());
    }

    SharedNumberAudioTag AudioTagMap::getTrackNumberPointer() {
        return getNumberTagPointer(TRACKNUMBER());
    }

    std::optional<std::uint32_t> AudioTagMap::getTrackNumberOptional() const {
        return getNumberTagOptional(TRACKNUMBER());
    }

    std::uint32_t AudioTagMap::getTrackNumber() const {
        return getNumberTag(TRACKNUMBER());
    }

    bool AudioTagMap::setTrackNumber(std::uint32_t trackNumber) {
        return setNumberTag(TRACKNUMBER(), trackNumber);
    }



    std::uint32_t AudioTagMap::getYear() const {
        return getDateTag(DATE()).getYear();
    }

    bool AudioTagMap::setYear(std::uint32_t year) {
        return setDateTag(DATE(), types::Date(year));
    }



    std::uint32_t AudioTagMap::getOriginalYear() const {
        return getDateTag(ORIGINALDATE()).getYear();
    }

    bool AudioTagMap::setOriginalYear(std::uint32_t originalYear) {
        return setDateTag(ORIGINALDATE(), types::Date(originalYear));
    }



    SharedConstDateAudioTag AudioTagMap::getDatePointer() const {
        return getDateTagPointer(DATE());
    }

    SharedDateAudioTag AudioTagMap::getDatePointer() {
        return getDateTagPointer(DATE());
    }

    std::optional<types::Date> AudioTagMap::getDateOptional() const {
        return getDateTagOptional(DATE());
    }

    types::Date AudioTagMap::getDate() const {
        return getDateTag(DATE());
    }

    bool AudioTagMap::setDate(const types::Date& date) {
        return setDateTag(DATE(), date);
    }



    SharedConstDateAudioTag AudioTagMap::getEncodingDatePointer() const {
        return getDateTagPointer(ENCODINGDATE());
    }

    SharedDateAudioTag AudioTagMap::getEncodingDatePointer() {
        return getDateTagPointer(ENCODINGDATE());
    }

    std::optional<types::Date> AudioTagMap::getEncodingDateOptional() const {
        return getDateTagOptional(ENCODINGDATE());
    }

    types::Date AudioTagMap::getEncodingDate() const {
        return getDateTag(ENCODINGDATE());
    }

    bool AudioTagMap::setEncodingDate(const types::Date& encodingDate) {
        return setDateTag(ENCODINGDATE(), encodingDate);
    }



    SharedConstDateAudioTag AudioTagMap::getOriginalDatePointer() const {
        return getDateTagPointer(ORIGINALDATE());
    }

    SharedDateAudioTag AudioTagMap::getOriginalDatePointer() {
        return getDateTagPointer(ORIGINALDATE());
    }

    std::optional<types::Date> AudioTagMap::getOriginalDateOptional() const {
        return getDateTagOptional(ORIGINALDATE());
    }

    types::Date AudioTagMap::getOriginalDate() const {
        return getDateTag(ORIGINALDATE());
    }

    bool AudioTagMap::setOriginalDate(const types::Date& originalDate) {
        return setDateTag(ORIGINALDATE(), originalDate);
    }



    SharedConstLyricsAudioTag AudioTagMap::getLyricsEngPointer() const {
        return getLyricsTagPointer(LYRICSENG());
    }

    SharedLyricsAudioTag AudioTagMap::getLyricsEngPointer() {
        return getLyricsTagPointer(LYRICSENG());
    }

    std::optional<types::Lyrics> AudioTagMap::getLyricsEngOptional() const {
        return getLyricsTagOptional(LYRICSENG());
    }

    types::Lyrics AudioTagMap::getLyricsEng() const {
        return getLyricsTag(LYRICSENG());
    }

    bool AudioTagMap::setLyricsEng(const types::Lyrics& lyricsEng) {
        return setLyricsTag(LYRICSENG(), lyricsEng);
    }



    SharedConstImageAudioTag AudioTagMap::getImageOtherPointer() const {
        return getImageTagPointer(IMAGEOTHER());
    }

    SharedImageAudioTag AudioTagMap::getImageOtherPointer() {
        return getImageTagPointer(IMAGEOTHER());
    }

    std::optional<types::Image> AudioTagMap::getImageOtherOptional() const {
        return getImageTagOptional(IMAGEOTHER());
    }

    types::Image AudioTagMap::getImageOther() const {
        return getImageTag(IMAGEOTHER());
    }

    bool AudioTagMap::setImageOther(const types::Image& imageOther) {
        return setImageTag(IMAGEOTHER(), imageOther);
    }

    bool AudioTagMap::setImageOther(types::Image&& imageOther) {
        return setImageTag(IMAGEOTHER(), std::move(imageOther));
    }



    SharedConstImageAudioTag AudioTagMap::getImageIConPointer() const {
        return getImageTagPointer(IMAGEICON());
    }

    SharedImageAudioTag AudioTagMap::getImageIConPointer() {
        return getImageTagPointer(IMAGEICON());
    }

    std::optional<types::Image> AudioTagMap::getImageIConOptional() const {
        return getImageTagOptional(IMAGEICON());
    }

    types::Image AudioTagMap::getImageICon() const {
        return getImageTag(IMAGEICON());
    }

    bool AudioTagMap::setImageICon(const types::Image& imageICon) {
        return setImageTag(IMAGEICON(), imageICon);
    }

    bool AudioTagMap::setImageICon(types::Image&& imageICon) {
        return setImageTag(IMAGEICON(), std::move(imageICon));
    }



    SharedConstImageAudioTag AudioTagMap::getImageOtherIconPointer() const {
        return getImageTagPointer(IMAGEOTHERICON());
    }

    SharedImageAudioTag AudioTagMap::getImageOtherIconPointer() {
        return getImageTagPointer(IMAGEOTHERICON());
    }

    std::optional<types::Image> AudioTagMap::getImageOtherIconOptional() const {
        return getImageTagOptional(IMAGEOTHERICON());
    }

    types::Image AudioTagMap::getImageOtherIcon() const {
        return getImageTag(IMAGEOTHERICON());
    }

    bool AudioTagMap::setImageOtherIcon(const types::Image& imageOtherIcon) {
        return setImageTag(IMAGEOTHERICON(), imageOtherIcon);
    }

    bool AudioTagMap::setImageOtherIcon(types::Image&& imageOtherIcon) {
        return setImageTag(IMAGEOTHERICON(), std::move(imageOtherIcon));
    }



    SharedConstImageAudioTag AudioTagMap::getImageCoverFrontPointer() const {
        return getImageTagPointer(IMAGECOVERFRONT());
    }

    SharedImageAudioTag AudioTagMap::getImageCoverFrontPointer() {
        return getImageTagPointer(IMAGECOVERFRONT());
    }

    std::optional<types::Image> AudioTagMap::getImageCoverFrontOptional() const {
        return getImageTagOptional(IMAGECOVERFRONT());
    }

    types::Image AudioTagMap::getImageCoverFront() const {
        return getImageTag(IMAGECOVERFRONT());
    }

    bool AudioTagMap::setImageCoverFront(const types::Image& imageCoverFront) {
        return setImageTag(IMAGECOVERFRONT(), imageCoverFront);
    }

    bool AudioTagMap::setImageCoverFront(types::Image&& imageCoverFront) {
        return setImageTag(IMAGECOVERFRONT(), std::move(imageCoverFront));
    }



    SharedConstImageAudioTag AudioTagMap::getImageCoverBackPointer() const {
        return getImageTagPointer(IMAGECOVERBACK());
    }

    SharedImageAudioTag AudioTagMap::getImageCoverBackPointer() {
        return getImageTagPointer(IMAGECOVERBACK());
    }

    std::optional<types::Image> AudioTagMap::getImageCoverBackOptional() const {
        return getImageTagOptional(IMAGECOVERBACK());
    }

    types::Image AudioTagMap::getImageCoverBack() const {
        return getImageTag(IMAGECOVERBACK());
    }

    bool AudioTagMap::setImageCoverBack(const types::Image& imageCoverBack) {
        return setImageTag(IMAGECOVERBACK(), imageCoverBack);
    }

    bool AudioTagMap::setImageCoverBack(types::Image&& imageCoverBack) {
        return setImageTag(IMAGECOVERBACK(), std::move(imageCoverBack));
    }



    SharedConstImageAudioTag AudioTagMap::getImageLeafletPointer() const {
        return getImageTagPointer(IMAGELEAFLET());
    }

    SharedImageAudioTag AudioTagMap::getImageLeafletPointer() {
        return getImageTagPointer(IMAGELEAFLET());
    }

    std::optional<types::Image> AudioTagMap::getImageLeafletOptional() const {
        return getImageTagOptional(IMAGELEAFLET());
    }

    types::Image AudioTagMap::getImageLeaflet() const {
        return getImageTag(IMAGELEAFLET());
    }

    bool AudioTagMap::setImageLeaflet(const types::Image& imageLeaflet) {
        return setImageTag(IMAGELEAFLET(), imageLeaflet);
    }

    bool AudioTagMap::setImageLeaflet(types::Image&& imageLeaflet) {
        return setImageTag(IMAGELEAFLET(), std::move(imageLeaflet));
    }



    SharedConstImageAudioTag AudioTagMap::getImageMediaPointer() const {
        return getImageTagPointer(IMAGEMEDIA());
    }

    SharedImageAudioTag AudioTagMap::getImageMediaPointer() {
        return getImageTagPointer(IMAGEMEDIA());
    }

    std::optional<types::Image> AudioTagMap::getImageMediaOptional() const {
        return getImageTagOptional(IMAGEMEDIA());
    }

    types::Image AudioTagMap::getImageMedia() const {
        return getImageTag(IMAGEMEDIA());
    }

    bool AudioTagMap::setImageMedia(const types::Image& imageMedia) {
        return setImageTag(IMAGEMEDIA(), imageMedia);
    }

    bool AudioTagMap::setImageMedia(types::Image&& imageMedia) {
        return setImageTag(IMAGEMEDIA(), std::move(imageMedia));
    }



    SharedConstImageAudioTag AudioTagMap::getImageLeadArtistPointer() const {
        return getImageTagPointer(IMAGELEADARTIST());
    }

    SharedImageAudioTag AudioTagMap::getImageLeadArtistPointer() {
        return getImageTagPointer(IMAGELEADARTIST());
    }

    std::optional<types::Image> AudioTagMap::getImageLeadArtistOptional() const {
        return getImageTagOptional(IMAGELEADARTIST());
    }

    types::Image AudioTagMap::getImageLeadArtist() const {
        return getImageTag(IMAGELEADARTIST());
    }

    bool AudioTagMap::setImageLeadArtist(const types::Image& imageLeadArtist) {
        return setImageTag(IMAGELEADARTIST(), imageLeadArtist);
    }

    bool AudioTagMap::setImageLeadArtist(types::Image&& imageLeadArtist) {
        return setImageTag(IMAGELEADARTIST(), std::move(imageLeadArtist));
    }



    SharedConstImageAudioTag AudioTagMap::getImageArtistPointer() const {
        return getImageTagPointer(IMAGEARTIST());
    }

    SharedImageAudioTag AudioTagMap::getImageArtistPointer() {
        return getImageTagPointer(IMAGEARTIST());
    }

    std::optional<types::Image> AudioTagMap::getImageArtistOptional() const {
        return getImageTagOptional(IMAGEARTIST());
    }

    types::Image AudioTagMap::getImageArtist() const {
        return getImageTag(IMAGEARTIST());
    }

    bool AudioTagMap::setImageArtist(const types::Image& imageArtist) {
        return setImageTag(IMAGEARTIST(), imageArtist);
    }

    bool AudioTagMap::setImageArtist(types::Image&& imageArtist) {
        return setImageTag(IMAGEARTIST(), std::move(imageArtist));
    }



    SharedConstImageAudioTag AudioTagMap::getImageConductorPointer() const {
        return getImageTagPointer(IMAGECONDUCTOR());
    }

    SharedImageAudioTag AudioTagMap::getImageConductorPointer() {
        return getImageTagPointer(IMAGECONDUCTOR());
    }

    std::optional<types::Image> AudioTagMap::getImageConductorOptional() const {
        return getImageTagOptional(IMAGECONDUCTOR());
    }

    types::Image AudioTagMap::getImageConductor() const {
        return getImageTag(IMAGECONDUCTOR());
    }

    bool AudioTagMap::setImageConductor(const types::Image& imageConductor) {
        return setImageTag(IMAGECONDUCTOR(), imageConductor);
    }

    bool AudioTagMap::setImageConductor(types::Image&& imageConductor) {
        return setImageTag(IMAGECONDUCTOR(), std::move(imageConductor));
    }



    SharedConstImageAudioTag AudioTagMap::getImageBandPointer() const {
        return getImageTagPointer(IMAGEBAND());
    }

    SharedImageAudioTag AudioTagMap::getImageBandPointer() {
        return getImageTagPointer(IMAGEBAND());
    }

    std::optional<types::Image> AudioTagMap::getImageBandOptional() const {
        return getImageTagOptional(IMAGEBAND());
    }

    types::Image AudioTagMap::getImageBand() const {
        return getImageTag(IMAGEBAND());
    }

    bool AudioTagMap::setImageBand(const types::Image& imageBand) {
        return setImageTag(IMAGEBAND(), imageBand);
    }

    bool AudioTagMap::setImageBand(types::Image&& imageBand) {
        return setImageTag(IMAGEBAND(), std::move(imageBand));
    }



    SharedConstImageAudioTag AudioTagMap::getImageComposerPointer() const {
        return getImageTagPointer(IMAGECOMPOSER());
    }

    SharedImageAudioTag AudioTagMap::getImageComposerPointer() {
        return getImageTagPointer(IMAGECOMPOSER());
    }

    std::optional<types::Image> AudioTagMap::getImageComposerOptional() const {
        return getImageTagOptional(IMAGECOMPOSER());
    }

    types::Image AudioTagMap::getImageComposer() const {
        return getImageTag(IMAGECOMPOSER());
    }

    bool AudioTagMap::setImageComposer(const types::Image& imageComposer) {
        return setImageTag(IMAGECOMPOSER(), imageComposer);
    }

    bool AudioTagMap::setImageComposer(types::Image&& imageComposer) {
        return setImageTag(IMAGECOMPOSER(), std::move(imageComposer));
    }



    SharedConstImageAudioTag AudioTagMap::getImageLyricistPointer() const {
        return getImageTagPointer(IMAGELYRICIST());
    }

    SharedImageAudioTag AudioTagMap::getImageLyricistPointer() {
        return getImageTagPointer(IMAGELYRICIST());
    }

    std::optional<types::Image> AudioTagMap::getImageLyricistOptional() const {
        return getImageTagOptional(IMAGELYRICIST());
    }

    types::Image AudioTagMap::getImageLyricist() const {
        return getImageTag(IMAGELYRICIST());
    }

    bool AudioTagMap::setImageLyricist(const types::Image& imageLyricist) {
        return setImageTag(IMAGELYRICIST(), imageLyricist);
    }

    bool AudioTagMap::setImageLyricist(types::Image&& imageLyricist) {
        return setImageTag(IMAGELYRICIST(), std::move(imageLyricist));
    }



    SharedConstImageAudioTag AudioTagMap::getImageRecordingLocationPointer() const {
        return getImageTagPointer(IMAGERECORDINGLOCATION());
    }

    SharedImageAudioTag AudioTagMap::getImageRecordingLocationPointer() {
        return getImageTagPointer(IMAGERECORDINGLOCATION());
    }

    std::optional<types::Image> AudioTagMap::getImageRecordingLocationOptional() const {
        return getImageTagOptional(IMAGERECORDINGLOCATION());
    }

    types::Image AudioTagMap::getImageRecordingLocation() const {
        return getImageTag(IMAGERECORDINGLOCATION());
    }

    bool AudioTagMap::setImageRecordingLocation(const types::Image& imageRecordingLocation) {
        return setImageTag(IMAGERECORDINGLOCATION(), imageRecordingLocation);
    }

    bool AudioTagMap::setImageRecordingLocation(types::Image&& imageRecordingLocation) {
        return setImageTag(IMAGERECORDINGLOCATION(), std::move(imageRecordingLocation));
    }



    SharedConstImageAudioTag AudioTagMap::getImageDuringRecordingPointer() const {
        return getImageTagPointer(IMAGEDURINGRECORDING());
    }

    SharedImageAudioTag AudioTagMap::getImageDuringRecordingPointer() {
        return getImageTagPointer(IMAGEDURINGRECORDING());
    }

    std::optional<types::Image> AudioTagMap::getImageDuringRecordingOptional() const {
        return getImageTagOptional(IMAGEDURINGRECORDING());
    }

    types::Image AudioTagMap::getImageDuringRecording() const {
        return getImageTag(IMAGEDURINGRECORDING());
    }

    bool AudioTagMap::setImageDuringRecording(const types::Image& imageDuringRecording) {
        return setImageTag(IMAGEDURINGRECORDING(), imageDuringRecording);
    }

    bool AudioTagMap::setImageDuringRecording(types::Image&& imageDuringRecording) {
        return setImageTag(IMAGEDURINGRECORDING(), std::move(imageDuringRecording));
    }



    SharedConstImageAudioTag AudioTagMap::getImageDuringPerformancePointer() const {
        return getImageTagPointer(IMAGEDURINGPERFORMANCE());
    }

    SharedImageAudioTag AudioTagMap::getImageDuringPerformancePointer() {
        return getImageTagPointer(IMAGEDURINGPERFORMANCE());
    }

    std::optional<types::Image> AudioTagMap::getImageDuringPerformanceOptional() const {
        return getImageTagOptional(IMAGEDURINGPERFORMANCE());
    }

    types::Image AudioTagMap::getImageDuringPerformance() const {
        return getImageTag(IMAGEDURINGPERFORMANCE());
    }

    bool AudioTagMap::setImageDuringPerformance(const types::Image& imageDuringPerformance) {
        return setImageTag(IMAGEDURINGPERFORMANCE(), imageDuringPerformance);
    }

    bool AudioTagMap::setImageDuringPerformance(types::Image&& imageDuringPerformance) {
        return setImageTag(IMAGEDURINGPERFORMANCE(), std::move(imageDuringPerformance));
    }



    SharedConstImageAudioTag AudioTagMap::getImageVideoCapturePointer() const {
        return getImageTagPointer(IMAGEVIDEOCAPTURE());
    }

    SharedImageAudioTag AudioTagMap::getImageVideoCapturePointer() {
        return getImageTagPointer(IMAGEVIDEOCAPTURE());
    }

    std::optional<types::Image> AudioTagMap::getImageVideoCaptureOptional() const {
        return getImageTagOptional(IMAGEVIDEOCAPTURE());
    }

    types::Image AudioTagMap::getImageVideoCapture() const {
        return getImageTag(IMAGEVIDEOCAPTURE());
    }

    bool AudioTagMap::setImageVideoCapture(const types::Image& imageVideoCapture) {
        return setImageTag(IMAGEVIDEOCAPTURE(), imageVideoCapture);
    }

    bool AudioTagMap::setImageVideoCapture(types::Image&& imageVideoCapture) {
        return setImageTag(IMAGEVIDEOCAPTURE(), std::move(imageVideoCapture));
    }



    SharedConstImageAudioTag AudioTagMap::getImageABrightColouredFishPointer() const {
        return getImageTagPointer(IMAGEABRIGHTCOLOUREDFISH());
    }

    SharedImageAudioTag AudioTagMap::getImageABrightColouredFishPointer() {
        return getImageTagPointer(IMAGEABRIGHTCOLOUREDFISH());
    }

    std::optional<types::Image> AudioTagMap::getImageABrightColouredFishOptional() const {
        return getImageTagOptional(IMAGEABRIGHTCOLOUREDFISH());
    }

    types::Image AudioTagMap::getImageABrightColouredFish() const {
        return getImageTag(IMAGEABRIGHTCOLOUREDFISH());
    }

    bool AudioTagMap::setImageABrightColouredFish(const types::Image& imageABrightColouredFish) {
        return setImageTag(IMAGEABRIGHTCOLOUREDFISH(), imageABrightColouredFish);
    }

    bool AudioTagMap::setImageABrightColouredFish(types::Image&& imageABrightColouredFish) {
        return setImageTag(IMAGEABRIGHTCOLOUREDFISH(), std::move(imageABrightColouredFish));
    }



    SharedConstImageAudioTag AudioTagMap::getImageIllustrationPointer() const {
        return getImageTagPointer(IMAGEILLUSTRATION());
    }

    SharedImageAudioTag AudioTagMap::getImageIllustrationPointer() {
        return getImageTagPointer(IMAGEILLUSTRATION());
    }

    std::optional<types::Image> AudioTagMap::getImageIllustrationOptional() const {
        return getImageTagOptional(IMAGEILLUSTRATION());
    }

    types::Image AudioTagMap::getImageIllustration() const {
        return getImageTag(IMAGEILLUSTRATION());
    }

    bool AudioTagMap::setImageIllustration(const types::Image& imageIllustration) {
        return setImageTag(IMAGEILLUSTRATION(), imageIllustration);
    }

    bool AudioTagMap::setImageIllustration(types::Image&& imageIllustration) {
        return setImageTag(IMAGEILLUSTRATION(), std::move(imageIllustration));
    }



    SharedConstImageAudioTag AudioTagMap::getImageBandLogoPointer() const {
        return getImageTagPointer(IMAGEBANDLOGO());
    }

    SharedImageAudioTag AudioTagMap::getImageBandLogoPointer() {
        return getImageTagPointer(IMAGEBANDLOGO());
    }

    std::optional<types::Image> AudioTagMap::getImageBandLogoOptional() const {
        return getImageTagOptional(IMAGEBANDLOGO());
    }

    types::Image AudioTagMap::getImageBandLogo() const {
        return getImageTag(IMAGEBANDLOGO());
    }

    bool AudioTagMap::setImageBandLogo(const types::Image& imageBandLogo) {
        return setImageTag(IMAGEBANDLOGO(), imageBandLogo);
    }

    bool AudioTagMap::setImageBandLogo(types::Image&& imageBandLogo) {
        return setImageTag(IMAGEBANDLOGO(), std::move(imageBandLogo));
    }



    SharedConstImageAudioTag AudioTagMap::getImagePublisherLogoPointer() const {
        return getImageTagPointer(IMAGEPUBLISHERLOGO());
    }

    SharedImageAudioTag AudioTagMap::getImagePublisherLogoPointer() {
        return getImageTagPointer(IMAGEPUBLISHERLOGO());
    }

    std::optional<types::Image> AudioTagMap::getImagePublisherLogoOptional() const {
        return getImageTagOptional(IMAGEPUBLISHERLOGO());
    }

    types::Image AudioTagMap::getImagePublisherLogo() const {
        return getImageTag(IMAGEPUBLISHERLOGO());
    }

    bool AudioTagMap::setImagePublisherLogo(const types::Image& imagePublisherLogo) {
        return setImageTag(IMAGEPUBLISHERLOGO(), imagePublisherLogo);
    }

    bool AudioTagMap::setImagePublisherLogo(types::Image&& imagePublisherLogo) {
        return setImageTag(IMAGEPUBLISHERLOGO(), std::move(imagePublisherLogo));
    }



    SharedConstISRCAudioTag AudioTagMap::getISRCPointer() const {
        return getISRCTagPointer(ISRC());
    }

    SharedISRCAudioTag AudioTagMap::getISRCPointer() {
        return getISRCTagPointer(ISRC());
    }

    std::optional<types::ISRC> AudioTagMap::getISRCOptional() const {
        return getISRCTagOptional(ISRC());
    }

    types::ISRC AudioTagMap::getISRC() const {
        return getISRCTag(ISRC());
    }

    bool AudioTagMap::setISRC(const types::ISRC& iSRC) {
        return setISRCTag(ISRC(), iSRC);
    }



    SharedConstBarcodeAudioTag AudioTagMap::getBarcodePointer() const {
        return getBarcodeTagPointer(BARCODE());
    }

    SharedBarcodeAudioTag AudioTagMap::getBarcodePointer() {
        return getBarcodeTagPointer(BARCODE());
    }

    std::optional<types::Barcode> AudioTagMap::getBarcodeOptional() const {
        return getBarcodeTagOptional(BARCODE());
    }

    types::Barcode AudioTagMap::getBarcode() const {
        return getBarcodeTag(BARCODE());
    }

    bool AudioTagMap::setBarcode(const types::Barcode& barcode) {
        return setBarcodeTag(BARCODE(), barcode);
    }







    const AudioTagMap::SetType AudioTagMap::TAG_NAMES = {
        ALBUM(),
        ALBUMARTIST(),
        ALBUMARTISTSORT(),
        ALBUMSORT(),
        ARRANGER(),
        ARTIST(),
        ARTISTSORT(),

        BARCODE(),

        BPM(),
        COMMENT(),
        COMPOSER(),
        COMPOSERSORT(),
        CONDUCTOR(),
        CONTENTGROUP(),
        COPYRIGHT(),
        DATE(),
        ENGINEER(),
        ENCODEDBY(),
        ENCODERSETTINGS(),
        ENCODINGDATE(),
        DISCNUMBER(),
        GENRE(),

        IMAGEOTHER(),
        IMAGEICON(),
        IMAGECOVERFRONT(),
        IMAGECOVERBACK(),
        IMAGELEAFLET(),
        IMAGEMEDIA(),
        IMAGEARTIST(),
        IMAGECONDUCTOR(),
        IMAGEBAND(),
        IMAGECOMPOSER(),
        IMAGELEADARTIST(),
        IMAGELYRICIST(),
        IMAGERECORDINGLOCATION(),
        IMAGEDURINGRECORDING(),
        IMAGEDURINGPERFORMANCE(),
        IMAGEVIDEOCAPTURE(),
        IMAGEABRIGHTCOLOUREDFISH(),
        IMAGEILLUSTRATION(),
        IMAGEBANDLOGO(),
        IMAGEPUBLISHERLOGO(),

        INITIALKEY(),
        ISRC(),
        LYRICIST(),
        MIXDJ(),
        MIXENGINEER(),
        MOOD(),
        ORIGINALALBUM(),
        ORIGINALARTIST(),
        ORIGINALDATE(),
        ORIGINALLYRICIST(),
        PRODUCER(),
        PUBLISHER(),
        RADIOSTATION(),
        RADIOSTATIONOWNER(),
        REMIXER(),
        SETSUBTITLE(),
        SUBTITLE(),
        TITLE(),
        TITLESORT(),
        TOTALDISCNUMBER(),
        TOTALTRACKNUMBER(),
        TRACKNUMBER(),

        WWWCOMMERCIAL(),
        WWWCOPYRIGHT(),
        WWWFILE(),
        WWWARTIST(),
        WWWFILESOURCE(),
        WWWPAYMENT(),
        WWWPODCAST(),
        WWWRADIOPAGE(),
        WWWPUBLISHER()
    };

    const AudioTagMap::SetType AudioTagMap::STRING_TAG_NAMES = {
        ALBUM(),
        ALBUMARTIST(),
        ALBUMARTISTSORT(),
        ALBUMSORT(),
        ARRANGER(),
        ARTIST(),
        ARTISTSORT(),
        COMMENT(),
        COMPOSER(),
        COMPOSERSORT(),
        CONDUCTOR(),
        CONTENTGROUP(),
        COPYRIGHT(),
        ENGINEER(),
        ENCODEDBY(),
        ENCODERSETTINGS(),
        GENRE(),
        INITIALKEY(),
        LYRICIST(),
        MIXDJ(),
        MIXENGINEER(),
        MOOD(),
        ORIGINALLYRICIST(),
        ORIGINALALBUM(),
        ORIGINALARTIST(),
        PRODUCER(),
        PUBLISHER(),
        RADIOSTATION(),
        RADIOSTATIONOWNER(),
        REMIXER(),
        SETSUBTITLE(),
        SUBTITLE(),
        TITLE(),
        TITLESORT(),
        WWWCOMMERCIAL(),
        WWWCOPYRIGHT(),
        WWWFILE(),
        WWWARTIST(),
        WWWFILESOURCE(),
        WWWPAYMENT(),
        WWWPODCAST(),
        WWWPUBLISHER(),
        WWWRADIOPAGE(),
    };

    const AudioTagMap::SetType AudioTagMap::NUMBER_TAG_NAMES = {
        BPM(),
        DISCNUMBER(),
        TOTALDISCNUMBER(),
        TOTALTRACKNUMBER(),
        TRACKNUMBER()
    };

    const AudioTagMap::SetType AudioTagMap::DATE_TAG_NAMES = {
        DATE(),
        ENCODINGDATE(),
        ORIGINALDATE()
    };

	const AudioTagMap::SetType AudioTagMap::IMAGE_TAG_NAMES = {
		IMAGEOTHER(),
		IMAGEICON(),
		IMAGEOTHERICON(),
		IMAGECOVERFRONT(),
		IMAGECOVERBACK(),
		IMAGELEAFLET(),
		IMAGEMEDIA(),
		IMAGELEADARTIST(),
		IMAGEARTIST(),
		IMAGECONDUCTOR(),
		IMAGEBAND(),
		IMAGECOMPOSER(),
		IMAGELYRICIST(),
		IMAGERECORDINGLOCATION(),
		IMAGEDURINGRECORDING(),
		IMAGEDURINGPERFORMANCE(),
		IMAGEVIDEOCAPTURE(),
		IMAGEABRIGHTCOLOUREDFISH(),
		IMAGEILLUSTRATION(),
		IMAGEBANDLOGO(),
		IMAGEPUBLISHERLOGO()
	};


    bool AudioTagMap::const_iterator::operator==(const const_iterator & other) const {
        return internalIterator == other.internalIterator;
    }

    bool AudioTagMap::const_iterator::operator!=(const const_iterator & other) const {
        return internalIterator != other.internalIterator;
    }



    AudioTagMap::const_iterator & AudioTagMap::const_iterator::operator++() {
        ++internalIterator;
        return *this;
    }

    AudioTagMap::const_iterator AudioTagMap::const_iterator::operator++(int) {
        auto old = *this;
        ++internalIterator;
        return old;
    }

    AudioTagMap::const_iterator & AudioTagMap::const_iterator::operator--() {
        --internalIterator;
        return *this;
    }

    AudioTagMap::const_iterator AudioTagMap::const_iterator::operator--(int) {
        auto old = *this;
        --internalIterator;
        return old;
    }



    const AudioTagMap::const_iterator::pointer AudioTagMap::const_iterator::operator->() const {
        return &operator*();
    }

    const AudioTagMap::const_iterator::reference AudioTagMap::const_iterator::operator*() const {
        returned = internalIterator.operator * ().second;
        return returned;
    }



    AudioTag::Type AudioTagMap::const_iterator::getType() const {
        return internalIterator->second->getType();
    }


    AudioTagMap::const_iterator::const_iterator(const internal_iterator & internalIterator)
        : internalIterator(internalIterator) {}







    AudioTagMap::iterator & AudioTagMap::iterator::operator++() {
        const_iterator::operator++();
        return *this;
    }

    AudioTagMap::iterator AudioTagMap::iterator::operator++(int) {
        auto old = *this;
        const_iterator::operator++();
        return old;
    }

    AudioTagMap::iterator & AudioTagMap::iterator::operator--() {
        const_iterator::operator--();
        return *this;
    }

    AudioTagMap::iterator AudioTagMap::iterator::operator--(int) {
        auto old = *this;
        const_iterator::operator--();
        return old;
    }

    AudioTagMap::iterator::pointer AudioTagMap::iterator::operator->() {
        return &internalIterator.operator * ().second;
    }

    AudioTagMap::iterator::reference AudioTagMap::iterator::operator*() {
        return internalIterator.operator * ().second;
    }
}
