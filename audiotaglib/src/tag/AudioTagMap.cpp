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
            tagMap.insert(std::make_pair(name, std::make_shared<LyricsAudioTag>(language, lyrics)));
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



    SharedConstISRCAudioTag AudioTagMap::getISRCTagPointer() const {
        return getTypeTagPointer<ISRCAudioTag>(ISRC());

    }

    SharedISRCAudioTag AudioTagMap::getISRCTagPointer() {
        return getTypeTagPointer<ISRCAudioTag>(ISRC());
    }

    std::optional<types::ISRC> AudioTagMap::getISRCTagOptional() const {
        auto tag = getISRCTagPointer();
        if (tag == nullptr)
            return std::nullopt;
        return tag->getISRC();
    }

    types::ISRC AudioTagMap::getISRCTag() const {
        auto tag = getISRCTagPointer();
        if (tag == nullptr)
            return types::ISRC();
        return tag->getISRC();
    }

    bool AudioTagMap::setISRCTag(const types::ISRC & isrc) {
        SharedISRCAudioTag tag = getISRCTagPointer();
        if (tag != nullptr) {
            tag->setISRC(isrc);
            return true;
        } else
            return tagMap.insert(std::make_pair(
                                     ISRC(), std::make_shared<ISRCAudioTag>(isrc)
                                 )).second;
    }



    SharedConstBarcodeAudioTag AudioTagMap::getBarcodeTagPointer() const {
        return getTypeTagPointer<BarcodeAudioTag>(BARCODE());

    }

    SharedBarcodeAudioTag AudioTagMap::getBarcodeTagPointer() {
        return getTypeTagPointer<BarcodeAudioTag>(BARCODE());
    }

    std::optional<types::Barcode> AudioTagMap::getBarcodeTagOptional() const {
        auto tag = getBarcodeTagPointer();
        if (tag == nullptr)
            return std::nullopt;
        return tag->getBarcode();
    }

    types::Barcode AudioTagMap::geBarcodeTag() const {
        auto tag = getBarcodeTagPointer();
        if (tag == nullptr)
            return types::Barcode();
        return tag->getBarcode();
    }

    bool AudioTagMap::setBarcodeTag(const types::Barcode & barcode) {
        SharedBarcodeAudioTag tag = getBarcodeTagPointer();
        if (tag != nullptr) {
            tag->setBarcode(barcode);
            return true;
        } else
            return tagMap.insert(std::make_pair(
                    BARCODE(), std::make_shared<BarcodeAudioTag>(barcode)
            )).second;
    }











    SharedConstStringAudioTag AudioTagMap::getAlbum() const {
        return getStringTagPointer(ALBUM());
    }

    SharedStringAudioTag AudioTagMap::getAlbum() {
        return getStringTagPointer(ALBUM());
    }

    bool AudioTagMap::setAlbum(const std::string & album) {
        return setStringTag(ALBUM(), album);
    }




    SharedConstStringAudioTag AudioTagMap::getAlbumArtist() const {
        return getStringTagPointer(ALBUMARTIST());
    }

    SharedStringAudioTag AudioTagMap::getAlbumArtist() {
        return getStringTagPointer(ALBUMARTIST());
    }

    bool AudioTagMap::setAlbumArtist(const std::string & albumArtist) {
        return setStringTag(ALBUMARTIST(), albumArtist);
    }




    SharedConstStringAudioTag AudioTagMap::getAlbumArtistSort() const {
        return getStringTagPointer(ALBUMARTISTSORT());
    }

    SharedStringAudioTag AudioTagMap::getAlbumArtistSort() {
        return getStringTagPointer(ALBUMARTISTSORT());
    }

    bool AudioTagMap::setAlbumArtistSort(const std::string & albumArtistSort) {
        return setStringTag(ALBUMARTISTSORT(), albumArtistSort);
    }




    SharedConstStringAudioTag AudioTagMap::getAlbumSort() const {
        return getStringTagPointer(ALBUMSORT());
    }

    SharedStringAudioTag AudioTagMap::getAlbumSort() {
        return getStringTagPointer(ALBUMSORT());
    }

    bool AudioTagMap::setAlbumSort(const std::string & albumSort) {
        return setStringTag(ALBUMSORT(), albumSort);
    }




    SharedConstStringAudioTag AudioTagMap::getArtist() const {
        return getStringTagPointer(ARTIST());
    }

    SharedStringAudioTag AudioTagMap::getArtist() {
        return getStringTagPointer(ARTIST());
    }

    bool AudioTagMap::setArtist(const std::string & artist) {
        return setStringTag(ARTIST(), artist);
    }




    SharedConstStringAudioTag AudioTagMap::getArtistSort() const {
        return getStringTagPointer(ARTISTSORT());
    }

    SharedStringAudioTag AudioTagMap::getArtistSort() {
        return getStringTagPointer(ARTISTSORT());
    }

    bool AudioTagMap::setArtistSort(const std::string & artistSort) {
        return setStringTag(ARTISTSORT(), artistSort);
    }




    SharedConstStringAudioTag AudioTagMap::getComment() const {
        return getStringTagPointer(COMMENT());
    }

    SharedStringAudioTag AudioTagMap::getComment() {
        return getStringTagPointer(COMMENT());
    }

    bool AudioTagMap::setComment(const std::string & comment) {
        return setStringTag(COMMENT(), comment);
    }




    SharedConstStringAudioTag AudioTagMap::getComposer() const {
        return getStringTagPointer(COMPOSER());
    }

    SharedStringAudioTag AudioTagMap::getComposer() {
        return getStringTagPointer(COMPOSER());
    }

    bool AudioTagMap::setComposer(const std::string & composer) {
        return setStringTag(COMPOSER(), composer);
    }




    SharedConstStringAudioTag AudioTagMap::getConductor() const {
        return getStringTagPointer(CONDUCTOR());
    }

    SharedStringAudioTag AudioTagMap::getConductor() {
        return getStringTagPointer(CONDUCTOR());
    }

    bool AudioTagMap::setConductor(const std::string & conductor) {
        return setStringTag(CONDUCTOR(), conductor);
    }




    SharedConstStringAudioTag AudioTagMap::getContentGroup() const {
        return getStringTagPointer(CONTENTGROUP());
    }

    SharedStringAudioTag AudioTagMap::getContentGroup() {
        return getStringTagPointer(CONTENTGROUP());
    }

    bool AudioTagMap::setContentGroup(const std::string & contentGroup) {
        return setStringTag(CONTENTGROUP(), contentGroup);
    }




    SharedConstStringAudioTag AudioTagMap::getCopyright() const {
        return getStringTagPointer(COPYRIGHT());
    }

    SharedStringAudioTag AudioTagMap::getCopyright() {
        return getStringTagPointer(COPYRIGHT());
    }

    bool AudioTagMap::setCopyright(const std::string & copyright) {
        return setStringTag(COPYRIGHT(), copyright);
    }




    SharedConstStringAudioTag AudioTagMap::getEncodedBy() const {
        return getStringTagPointer(ENCODEDBY());
    }

    SharedStringAudioTag AudioTagMap::getEncodedBy() {
        return getStringTagPointer(ENCODEDBY());
    }

    bool AudioTagMap::setEncodedBy(const std::string & encodedBy) {
        return setStringTag(ENCODEDBY(), encodedBy);
    }




    SharedConstStringAudioTag AudioTagMap::getEncoderSettings() const {
        return getStringTagPointer(ENCODERSETTINGS());
    }

    SharedStringAudioTag AudioTagMap::getEncoderSettings() {
        return getStringTagPointer(ENCODERSETTINGS());
    }

    bool AudioTagMap::setEncoderSettings(const std::string & encoderSettings) {
        return setStringTag(ENCODERSETTINGS(), encoderSettings);
    }




    SharedConstDateAudioTag AudioTagMap::getEncodingDate() const {
        return getDateTagPointer(ENCODINGDATE());
    }

    SharedDateAudioTag AudioTagMap::getEncodingDate() {
        return getDateTagPointer(ENCODINGDATE());
    }

    bool AudioTagMap::setEncodingDate(const types::Date & encodingDate) {
        return setDateTag(ENCODINGDATE(), encodingDate);
    }




    SharedConstStringAudioTag AudioTagMap::getGenre() const {
        return getStringTagPointer(GENRE());
    }

    SharedStringAudioTag AudioTagMap::getGenre() {
        return getStringTagPointer(GENRE());
    }

    bool AudioTagMap::setGenre(const std::string & genre) {
        return setStringTag(GENRE(), genre);
    }




    SharedConstStringAudioTag AudioTagMap::getInitialKey() const {
        return getStringTagPointer(INITIALKEY());
    }

    SharedStringAudioTag AudioTagMap::getInitialKey() {
        return getStringTagPointer(INITIALKEY());
    }

    bool AudioTagMap::setInitialKey(const std::string & initialKey) {
        return setStringTag(INITIALKEY(), initialKey);
    }




    SharedConstStringAudioTag AudioTagMap::getLyricist() const {
        return getStringTagPointer(LYRICIST());
    }

    SharedStringAudioTag AudioTagMap::getLyricist() {
        return getStringTagPointer(LYRICIST());
    }

    bool AudioTagMap::setLyricist(const std::string & lyricist) {
        return setStringTag(LYRICIST(), lyricist);
    }




    SharedConstStringAudioTag AudioTagMap::getMood() const {
        return getStringTagPointer(MOOD());
    }

    SharedStringAudioTag AudioTagMap::getMood() {
        return getStringTagPointer(MOOD());
    }

    bool AudioTagMap::setMood(const std::string & mood) {
        return setStringTag(MOOD(), mood);
    }




    SharedConstStringAudioTag AudioTagMap::getOriginalAlbum() const {
        return getStringTagPointer(ORIGINALALBUM());
    }

    SharedStringAudioTag AudioTagMap::getOriginalAlbum() {
        return getStringTagPointer(ORIGINALALBUM());
    }

    bool AudioTagMap::setOriginalAlbum(const std::string & originalAlbum) {
        return setStringTag(ORIGINALALBUM(), originalAlbum);
    }




    SharedConstStringAudioTag AudioTagMap::getOriginalArtist() const {
        return getStringTagPointer(ORIGINALARTIST());
    }

    SharedStringAudioTag AudioTagMap::getOriginalArtist() {
        return getStringTagPointer(ORIGINALARTIST());
    }

    bool AudioTagMap::setOriginalArtist(const std::string & originalArtist) {
        return setStringTag(ORIGINALARTIST(), originalArtist);
    }




    SharedConstStringAudioTag AudioTagMap::getOriginalLyricist() const {
        return getStringTagPointer(ORIGINALLYRICIST());
    }

    SharedStringAudioTag AudioTagMap::getOriginalLyricist() {
        return getStringTagPointer(ORIGINALLYRICIST());
    }

    bool AudioTagMap::setOriginalLyricist(const std::string & originalLyricist) {
        return setStringTag(ORIGINALLYRICIST(), originalLyricist);
    }




    SharedConstStringAudioTag AudioTagMap::getProducer() const {
        return getStringTagPointer(PRODUCER());
    }

    SharedStringAudioTag AudioTagMap::getProducer() {
        return getStringTagPointer(PRODUCER());
    }

    bool AudioTagMap::setProducer(const std::string & producer) {
        return setStringTag(PRODUCER(), producer);
    }




    SharedConstStringAudioTag AudioTagMap::getPublisher() const {
        return getStringTagPointer(PUBLISHER());
    }

    SharedStringAudioTag AudioTagMap::getPublisher() {
        return getStringTagPointer(PUBLISHER());
    }

    bool AudioTagMap::setPublisher(const std::string & publisher) {
        return setStringTag(PUBLISHER(), publisher);
    }




    SharedConstStringAudioTag AudioTagMap::getRadioStation() const {
        return getStringTagPointer(RADIOSTATION());
    }

    SharedStringAudioTag AudioTagMap::getRadioStation() {
        return getStringTagPointer(RADIOSTATION());
    }

    bool AudioTagMap::setRadioStation(const std::string & radioStation) {
        return setStringTag(RADIOSTATION(), radioStation);
    }




    SharedConstStringAudioTag AudioTagMap::getRadioStationOwner() const {
        return getStringTagPointer(RADIOSTATIONOWNER());
    }

    SharedStringAudioTag AudioTagMap::getRadioStationOwner() {
        return getStringTagPointer(RADIOSTATIONOWNER());
    }

    bool AudioTagMap::setRadioStationOwner(const std::string & radioStationOwner) {
        return setStringTag(RADIOSTATIONOWNER(), radioStationOwner);
    }




    SharedConstStringAudioTag AudioTagMap::getSetSubtitle() const {
        return getStringTagPointer(SETSUBTITLE());
    }

    SharedStringAudioTag AudioTagMap::getSetSubtitle() {
        return getStringTagPointer(SETSUBTITLE());
    }

    bool AudioTagMap::setSetSubtitle(const std::string & setSubtitle) {
        return setStringTag(SETSUBTITLE(), setSubtitle);
    }




    SharedConstStringAudioTag AudioTagMap::getSubtitle() const {
        return getStringTagPointer(SUBTITLE());
    }

    SharedStringAudioTag AudioTagMap::getSubtitle() {
        return getStringTagPointer(SUBTITLE());
    }

    bool AudioTagMap::setSubtitle(const std::string & subtitle) {
        return setStringTag(SUBTITLE(), subtitle);
    }




    SharedConstStringAudioTag AudioTagMap::getTitle() const {
        return getStringTagPointer(TITLE());
    }

    SharedStringAudioTag AudioTagMap::getTitle() {
        return getStringTagPointer(TITLE());
    }

    bool AudioTagMap::setTitle(const std::string & title) {
        return setStringTag(TITLE(), title);
    }




    SharedConstStringAudioTag AudioTagMap::getTitleSort() const {
        return getStringTagPointer(TITLESORT());
    }

    SharedStringAudioTag AudioTagMap::getTitleSort() {
        return getStringTagPointer(TITLESORT());
    }

    bool AudioTagMap::setTitleSort(const std::string & titleSort) {
        return setStringTag(TITLESORT(), titleSort);
    }



















    SharedConstNumberAudioTag AudioTagMap::getBpm() const {
        return getNumberTagPointer(BPM());
    }

    SharedNumberAudioTag AudioTagMap::getBpm() {
        return getNumberTagPointer(BPM());
    }

    bool AudioTagMap::setBpm(std::uint32_t bpm) {
        return setNumberTag(BPM(), bpm);
    }




    SharedConstNumberAudioTag AudioTagMap::getDiscNumber() const {
        return getNumberTagPointer(DISCNUMBER());
    }

    SharedNumberAudioTag AudioTagMap::getDiscNumber() {
        return getNumberTagPointer(DISCNUMBER());
    }

    bool AudioTagMap::setDiscNumber(std::uint32_t discNumber) {
        return setNumberTag(DISCNUMBER(), discNumber);
    }




    SharedConstNumberAudioTag AudioTagMap::getTotalDiscNumber() const {
        return getNumberTagPointer(TOTALDISCNUMBER());
    }

    SharedNumberAudioTag AudioTagMap::getTotalDiscNumber() {
        return getNumberTagPointer(TOTALDISCNUMBER());
    }

    bool AudioTagMap::setTotalDiscNumber(std::uint32_t totalDiscNumber) {
        return setNumberTag(TOTALDISCNUMBER(), totalDiscNumber);
    }




    SharedConstNumberAudioTag AudioTagMap::getTotalTrackNumber() const {
        return getNumberTagPointer(TOTALTRACKNUMBER());
    }

    SharedNumberAudioTag AudioTagMap::getTotalTrackNumber() {
        return getNumberTagPointer(TOTALTRACKNUMBER());
    }

    bool AudioTagMap::setTotalTrackNumber(std::uint32_t totalTrackNumber) {
        return setNumberTag(TOTALTRACKNUMBER(), totalTrackNumber);
    }




    SharedConstNumberAudioTag AudioTagMap::getTrackNumber() const {
        return getNumberTagPointer(TRACKNUMBER());
    }

    SharedNumberAudioTag AudioTagMap::getTrackNumber() {
        return getNumberTagPointer(TRACKNUMBER());
    }

    bool AudioTagMap::setTrackNumber(std::uint32_t trackNumber) {
        return setNumberTag(TRACKNUMBER(), trackNumber);
    }













    SharedConstDateAudioTag AudioTagMap::getDate() const {
        return getDateTagPointer(DATE());
    }

    SharedDateAudioTag AudioTagMap::getDate() {
        return getDateTagPointer(DATE());
    }

    bool AudioTagMap::setDate(const types::Date & date) {
        return setDateTag(DATE(), date);
    }




    SharedConstDateAudioTag AudioTagMap::getOriginalDate() const {
        return getDateTagPointer(ORIGINALDATE());
    }

    SharedDateAudioTag AudioTagMap::getOriginalDate() {
        return getDateTagPointer(ORIGINALDATE());
    }

    bool AudioTagMap::setOriginalDate(const types::Date & originalDate) {
        return setDateTag(ORIGINALDATE(), originalDate);
    }

















    SharedConstImageAudioTag AudioTagMap::getImageOther() const {
        return getImageTagPointer(IMAGEOTHER());
    }

    SharedImageAudioTag AudioTagMap::getImageOther() {
        return getImageTagPointer(IMAGEOTHER());
    }

    bool AudioTagMap::setImageOther(const types::Image & imageOther) {
        return setImageTag(IMAGEOTHER(), imageOther);
    }

    bool AudioTagMap::setImageOther(types::Image && imageOther) {
        return setImageTag(IMAGEOTHER(), std::move(imageOther));
    }




    SharedConstImageAudioTag AudioTagMap::getImageIcon() const {
        return getImageTagPointer(IMAGEICON());
    }

    SharedImageAudioTag AudioTagMap::getImageIcon() {
        return getImageTagPointer(IMAGEICON());
    }

    bool AudioTagMap::setImageIcon(const types::Image & imageIcon) {
        return setImageTag(IMAGEICON(), imageIcon);
    }

    bool AudioTagMap::setImageIcon(types::Image && imageIcon) {
        return setImageTag(IMAGEICON(), std::move(imageIcon));
    }




    SharedConstImageAudioTag AudioTagMap::getImageCoverFront() const {
        return getImageTagPointer(IMAGECOVERFRONT());
    }

    SharedImageAudioTag AudioTagMap::getImageCoverFront() {
        return getImageTagPointer(IMAGECOVERFRONT());
    }

    bool AudioTagMap::setImageCoverFront(const types::Image & imageCoverFront) {
        return setImageTag(IMAGECOVERFRONT(), imageCoverFront);
    }

    bool AudioTagMap::setImageCoverFront(types::Image && imageCoverFront) {
        return setImageTag(IMAGECOVERFRONT(), std::move(imageCoverFront));
    }




    SharedConstImageAudioTag AudioTagMap::getImageCoverBack() const {
        return getImageTagPointer(IMAGECOVERBACK());
    }

    SharedImageAudioTag AudioTagMap::getImageCoverBack() {
        return getImageTagPointer(IMAGECOVERBACK());
    }

    bool AudioTagMap::setImageCoverBack(const types::Image & imageCoverBack) {
        return setImageTag(IMAGECOVERBACK(), imageCoverBack);
    }

    bool AudioTagMap::setImageCoverBack(types::Image && imageCoverBack) {
        return setImageTag(IMAGECOVERBACK(), std::move(imageCoverBack));
    }




    SharedConstImageAudioTag AudioTagMap::getImageLeaflet() const {
        return getImageTagPointer(IMAGELEAFLET());
    }

    SharedImageAudioTag AudioTagMap::getImageLeaflet() {
        return getImageTagPointer(IMAGELEAFLET());
    }

    bool AudioTagMap::setImageLeaflet(const types::Image & imageLeaflet) {
        return setImageTag(IMAGELEAFLET(), imageLeaflet);
    }

    bool AudioTagMap::setImageLeaflet(types::Image && imageLeaflet) {
        return setImageTag(IMAGELEAFLET(), std::move(imageLeaflet));
    }




    SharedConstImageAudioTag AudioTagMap::getImageMedia() const {
        return getImageTagPointer(IMAGEMEDIA());
    }

    SharedImageAudioTag AudioTagMap::getImageMedia() {
        return getImageTagPointer(IMAGEMEDIA());
    }

    bool AudioTagMap::setImageMedia(const types::Image & imageMedia) {
        return setImageTag(IMAGEMEDIA(), imageMedia);
    }

    bool AudioTagMap::setImageMedia(types::Image && imageMedia) {
        return setImageTag(IMAGEMEDIA(), std::move(imageMedia));
    }




    SharedConstImageAudioTag AudioTagMap::getImageArtist() const {
        return getImageTagPointer(IMAGEARTIST());
    }

    SharedImageAudioTag AudioTagMap::getImageArtist() {
        return getImageTagPointer(IMAGEARTIST());
    }

    bool AudioTagMap::setImageArtist(const types::Image & imageArtist) {
        return setImageTag(IMAGEARTIST(), imageArtist);
    }

    bool AudioTagMap::setImageArtist(types::Image && imageArtist) {
        return setImageTag(IMAGEARTIST(), std::move(imageArtist));
    }




    SharedConstImageAudioTag AudioTagMap::getImageConductor() const {
        return getImageTagPointer(IMAGECONDUCTOR());
    }

    SharedImageAudioTag AudioTagMap::getImageConductor() {
        return getImageTagPointer(IMAGECONDUCTOR());
    }

    bool AudioTagMap::setImageConductor(const types::Image & imageConductor) {
        return setImageTag(IMAGECONDUCTOR(), imageConductor);
    }

    bool AudioTagMap::setImageConductor(types::Image && imageConductor) {
        return setImageTag(IMAGECONDUCTOR(), std::move(imageConductor));
    }




    SharedConstImageAudioTag AudioTagMap::getImageBand() const {
        return getImageTagPointer(IMAGEBAND());
    }

    SharedImageAudioTag AudioTagMap::getImageBand() {
        return getImageTagPointer(IMAGEBAND());
    }

    bool AudioTagMap::setImageBand(const types::Image & imageBand) {
        return setImageTag(IMAGEBAND(), imageBand);
    }

    bool AudioTagMap::setImageBand(types::Image && imageBand) {
        return setImageTag(IMAGEBAND(), std::move(imageBand));
    }




    SharedConstImageAudioTag AudioTagMap::getImageComposer() const {
        return getImageTagPointer(IMAGECOMPOSER());
    }

    SharedImageAudioTag AudioTagMap::getImageComposer() {
        return getImageTagPointer(IMAGECOMPOSER());
    }

    bool AudioTagMap::setImageComposer(const types::Image & imageComposer) {
        return setImageTag(IMAGECOMPOSER(), imageComposer);
    }

    bool AudioTagMap::setImageComposer(types::Image && imageComposer) {
        return setImageTag(IMAGECOMPOSER(), std::move(imageComposer));
    }




    SharedConstImageAudioTag AudioTagMap::getImageLyricist() const {
        return getImageTagPointer(IMAGELYRICIST());
    }

    SharedImageAudioTag AudioTagMap::getImageLyricist() {
        return getImageTagPointer(IMAGELYRICIST());
    }

    bool AudioTagMap::setImageLyricist(const types::Image & imageLyricist) {
        return setImageTag(IMAGELYRICIST(), imageLyricist);
    }

    bool AudioTagMap::setImageLyricist(types::Image && imageLyricist) {
        return setImageTag(IMAGELYRICIST(), std::move(imageLyricist));
    }




    SharedConstImageAudioTag AudioTagMap::getImageRecordingLocation() const {
        return getImageTagPointer(IMAGERECORDINGLOCATION());
    }

    SharedImageAudioTag AudioTagMap::getImageRecordingLocation() {
        return getImageTagPointer(IMAGERECORDINGLOCATION());
    }

    bool AudioTagMap::setImageRecordingLocation(const types::Image & imageRecordingLocation) {
        return setImageTag(IMAGERECORDINGLOCATION(), imageRecordingLocation);
    }

    bool AudioTagMap::setImageRecordingLocation(types::Image && imageRecordingLocation) {
        return setImageTag(IMAGERECORDINGLOCATION(), std::move(imageRecordingLocation));
    }




    SharedConstImageAudioTag AudioTagMap::getImageDuringRecording() const {
        return getImageTagPointer(IMAGEDURINGRECORDING());
    }

    SharedImageAudioTag AudioTagMap::getImageDuringRecording() {
        return getImageTagPointer(IMAGEDURINGRECORDING());
    }

    bool AudioTagMap::setImageDuringRecording(const types::Image & imageDuringRecording) {
        return setImageTag(IMAGEDURINGRECORDING(), imageDuringRecording);
    }

    bool AudioTagMap::setImageDuringRecording(types::Image && imageDuringRecording) {
        return setImageTag(IMAGEDURINGRECORDING(), std::move(imageDuringRecording));
    }




    SharedConstImageAudioTag AudioTagMap::getImageDuringPerformance() const {
        return getImageTagPointer(IMAGEDURINGPERFORMANCE());
    }

    SharedImageAudioTag AudioTagMap::getImageDuringPerformance() {
        return getImageTagPointer(IMAGEDURINGPERFORMANCE());
    }

    bool AudioTagMap::setImageDuringPerformance(const types::Image & imageDuringPerformance) {
        return setImageTag(IMAGEDURINGPERFORMANCE(), imageDuringPerformance);
    }

    bool AudioTagMap::setImageDuringPerformance(types::Image && imageDuringPerformance) {
        return setImageTag(IMAGEDURINGPERFORMANCE(), std::move(imageDuringPerformance));
    }




    SharedConstImageAudioTag AudioTagMap::getImageVideoCapture() const {
        return getImageTagPointer(IMAGEVIDEOCAPTURE());
    }

    SharedImageAudioTag AudioTagMap::getImageVideoCapture() {
        return getImageTagPointer(IMAGEVIDEOCAPTURE());
    }

    bool AudioTagMap::setImageVideoCapture(const types::Image & imageVideoCapture) {
        return setImageTag(IMAGEVIDEOCAPTURE(), imageVideoCapture);
    }

    bool AudioTagMap::setImageVideoCapture(types::Image && imageVideoCapture) {
        return setImageTag(IMAGEVIDEOCAPTURE(), std::move(imageVideoCapture));
    }




    SharedConstImageAudioTag AudioTagMap::getImageABrightColouredFish() const {
        return getImageTagPointer(IMAGEABRIGHTCOLOUREDFISH());
    }

    SharedImageAudioTag AudioTagMap::getImageABrightColouredFish() {
        return getImageTagPointer(IMAGEABRIGHTCOLOUREDFISH());
    }

    bool AudioTagMap::setImageABrightColouredFish(const types::Image & imageABrightColouredFish) {
        return setImageTag(IMAGEABRIGHTCOLOUREDFISH(), imageABrightColouredFish);
    }

    bool AudioTagMap::setImageABrightColouredFish(types::Image && imageABrightColouredFish) {
        return setImageTag(IMAGEABRIGHTCOLOUREDFISH(), std::move(imageABrightColouredFish));
    }




    SharedConstImageAudioTag AudioTagMap::getImageIllustration() const {
        return getImageTagPointer(IMAGEILLUSTRATION());
    }

    SharedImageAudioTag AudioTagMap::getImageIllustration() {
        return getImageTagPointer(IMAGEILLUSTRATION());
    }

    bool AudioTagMap::setImageIllustration(const types::Image & imageIllustration) {
        return setImageTag(IMAGEILLUSTRATION(), imageIllustration);
    }

    bool AudioTagMap::setImageIllustration(types::Image && imageIllustration) {
        return setImageTag(IMAGEILLUSTRATION(), std::move(imageIllustration));
    }




    SharedConstImageAudioTag AudioTagMap::getImageBandLogo() const {
        return getImageTagPointer(IMAGEBANDLOGO());
    }

    SharedImageAudioTag AudioTagMap::getImageBandLogo() {
        return getImageTagPointer(IMAGEBANDLOGO());
    }

    bool AudioTagMap::setImageBandLogo(const types::Image & imageBandLogo) {
        return setImageTag(IMAGEBANDLOGO(), imageBandLogo);
    }

    bool AudioTagMap::setImageBandLogo(types::Image && imageBandLogo) {
        return setImageTag(IMAGEBANDLOGO(), std::move(imageBandLogo));
    }




    SharedConstImageAudioTag AudioTagMap::getImagePublisherLogo() const {
        return getImageTagPointer(IMAGEPUBLISHERLOGO());
    }

    SharedImageAudioTag AudioTagMap::getImagePublisherLogo() {
        return getImageTagPointer(IMAGEPUBLISHERLOGO());
    }

    bool AudioTagMap::setImagePublisherLogo(const types::Image & imagePublisherLogo) {
        return setImageTag(IMAGEPUBLISHERLOGO(), imagePublisherLogo);
    }

    bool AudioTagMap::setImagePublisherLogo(types::Image && imagePublisherLogo) {
        return setImageTag(IMAGEPUBLISHERLOGO(), std::move(imagePublisherLogo));
    }











    SharedConstLyricsAudioTag AudioTagMap::getLyricsEng() const {
        return getLyricsTagPointer(LYRICSENG());
    }

    SharedLyricsAudioTag AudioTagMap::getLyricsEng() {
        return getLyricsTagPointer(LYRICSENG());
    }

    bool AudioTagMap::setLyricsEng(const types::Lyrics & lyricsEng) {
        return setLyricsTagByLang("eng"s, lyricsEng);
    }













    bool AudioTagMap::setYear(std::uint32_t year) {
        return setDateTag(DATE(), types::Date(year));
    }

    bool AudioTagMap::setOriginalYear(std::uint32_t originalYear) {
        return setDateTag(ORIGINALDATE(), types::Date(originalYear));
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
