#include "TagMap.hpp"
#include <boost/algorithm/string.hpp>


namespace audiotaglib {

    const std::string& TagMap::ALBUM() {
        static const std::string _ALBUM = "ALBUM"s;
        return _ALBUM;
    }

    const std::string& TagMap::ALBUMSORT() {
        static const std::string _ALBUMSORT = "ALBUMSORT"s;
        return _ALBUMSORT;
    }

    const std::string& TagMap::ALBUMARTIST() {
        static const std::string _ALBUMARTIST = "ALBUMARTIST"s;
        return _ALBUMARTIST;
    }

    const std::string& TagMap::ALBUMARTISTSORT() {
        static const std::string _ALBUMARTISTSORT = "ALBUMARTISTSORT"s;
        return _ALBUMARTISTSORT;
    }

    const std::string& TagMap::ARRANGER() {
        static const std::string _ARRANGER = "ARRANGER"s;
        return _ARRANGER;
    }

    const std::string& TagMap::ARTIST() {
        static const std::string _ARTIST = "ARTIST"s;
        return _ARTIST;
    }

    const std::string& TagMap::ARTISTSORT() {
        static const std::string _ARTISTSORT = "ARTISTSORT"s;
        return _ARTISTSORT;
    }

    const std::string &TagMap::BARCODE() {
        static const std::string _BARCODE = "BARCODE"s;
        return _BARCODE;
    }

    const std::string& TagMap::BPM() {
        static const std::string _BPM = "BPM"s;
        return _BPM;
    }

    const std::string& TagMap::COMMENT() {
        static const std::string _COMMENT = "COMMENT"s;
        return _COMMENT;
    }

    const std::string& TagMap::COMPOSER() {
        static const std::string _COMPOSER = "COMPOSER"s;
        return _COMPOSER;
    }

    const std::string& TagMap::COMPOSERSORT() {
        static const std::string _COMPOSERSORT = "COMPOSERSORT"s;
        return _COMPOSERSORT;
    }

    const std::string& TagMap::CONDUCTOR() {
        static const std::string _CONDUCTOR = "CONDUCTOR"s;
        return _CONDUCTOR;
    }

    const std::string & TagMap::CONTENTGROUP() {
        static const std::string _CONTENTGROUP = "CONTENTGROUP"s;
        return _CONTENTGROUP;
    }

    const std::string & TagMap::COPYRIGHT() {
        static const std::string _COPYRIGHT = "COPYRIGHT"s;
        return _COPYRIGHT;
    }

    const std::string& TagMap::DATE() {
        static const std::string _DATE = "DATE"s;
        return _DATE;
    }

    const std::string& TagMap::DISCNUMBER() {
        static const std::string _DISCNUMBER = "DISCNUMBER"s;
        return _DISCNUMBER;
    }

    const std::string &TagMap::ENGINEER() {
        static const std::string _ENGINEER = "ENGINEER"s;
        return _ENGINEER;
    }

    const std::string & TagMap::ENCODEDBY() {
        static const std::string _ENCODEDBY = "ENCODEDBY"s;
        return _ENCODEDBY;
    }

    // TODO: add vorbis mapping for ENCODER_OPTIONS
    const std::string & TagMap::ENCODERSETTINGS() {
        static const std::string _ENCODERSETTINGS = "ENCODERSETTINGS"s;
        return _ENCODERSETTINGS;
    }

    const std::string & TagMap::ENCODINGDATE() {
        static const std::string _ENCODINGDATE = "ENCODINGDATE"s;
        return _ENCODINGDATE;
    }

    const std::string& TagMap::GENRE() {
        static const std::string _GENRE = "GENRE"s;
        return _GENRE;
    }

    const std::string& TagMap::IMAGEOTHER() {
        static const std::string _IMAGEOTHER = "IMAGEOTHER"s;
        return _IMAGEOTHER;
    }

    const std::string& TagMap::IMAGEICON() {
        static const std::string _IMAGEICON = "IMAGEICON"s;
        return _IMAGEICON;
    }

    const std::string& TagMap::IMAGEOTHERICON() {
        static const std::string _IMAGEOTHERICON = "IMAGEOTHERICON"s;
        return _IMAGEOTHERICON;
    }

    const std::string& TagMap::IMAGECOVERFRONT() {
        static const std::string _IMAGECOVERFRONT = "IMAGECOVERFRONT"s;
        return _IMAGECOVERFRONT;
    }

    const std::string& TagMap::IMAGECOVERBACK() {
        static const std::string _IMAGECOVERBACK = "IMAGECOVERBACK"s;
        return _IMAGECOVERBACK;
    }

    const std::string& TagMap::IMAGELEAFLET() {
        static const std::string _IMAGELEAFLET = "IMAGELEAFLET"s;
        return _IMAGELEAFLET;
    }

    const std::string& TagMap::IMAGEMEDIA() {
        static const std::string _IMAGEMEDIA = "IMAGEMEDIA"s;
        return _IMAGEMEDIA;
    }

    const std::string& TagMap::IMAGEARTIST() {
        static const std::string _IMAGEARTIST = "IMAGEARTIST"s;
        return _IMAGEARTIST;
    }

    const std::string& TagMap::IMAGECONDUCTOR() {
        static const std::string _IMAGECONDUCTOR = "IMAGECONDUCTOR"s;
        return _IMAGECONDUCTOR;
    }

    const std::string& TagMap::IMAGEBAND() {
        static const std::string _IMAGEBAND = "IMAGEBAND"s;
        return _IMAGEBAND;
    }

    const std::string& TagMap::IMAGECOMPOSER() {
        static const std::string _IMAGECOMPOSER = "IMAGECOMPOSER"s;
        return _IMAGECOMPOSER;
    }

    const std::string& TagMap::IMAGELEADARTIST() {
        static const std::string _IMAGELEADARTIST = "IMAGELEADARTIST"s;
        return _IMAGELEADARTIST;
    }

    const std::string& TagMap::IMAGELYRICIST() {
        static const std::string _IMAGELYRICIST = "IMAGELYRICIST"s;
        return _IMAGELYRICIST;
    }

    const std::string& TagMap::IMAGERECORDINGLOCATION() {
        static const std::string _IMAGERECORDINGLOCATION = "IMAGERECORDINGLOCATION"s;
        return _IMAGERECORDINGLOCATION;
    }

    const std::string& TagMap::IMAGEDURINGRECORDING() {
        static const std::string _IMAGEDURINGRECORDING = "IMAGEDURINGRECORDING"s;
        return _IMAGEDURINGRECORDING;
    }

    const std::string& TagMap::IMAGEDURINGPERFORMANCE() {
        static const std::string _IMAGEDURINGPERFORMANCE = "IMAGEDURINGPERFORMANCE"s;
        return _IMAGEDURINGPERFORMANCE;
    }

    const std::string& TagMap::IMAGEVIDEOCAPTURE() {
        static const std::string _IMAGEVIDEOCAPTURE = "IMAGEVIDEOCAPTURE"s;
        return _IMAGEVIDEOCAPTURE;
    }

    const std::string& TagMap::IMAGEABRIGHTCOLOUREDFISH() {
        static const std::string _IMAGEABRIGHTCOLOUREDFISH = "IMAGEABRIGHTCOLOUREDFISH"s;
        return _IMAGEABRIGHTCOLOUREDFISH;
    }

    const std::string& TagMap::IMAGEILLUSTRATION() {
        static const std::string _IMAGEILLUSTRATION = "IMAGEILLUSTRATION"s;
        return _IMAGEILLUSTRATION;
    }

    const std::string& TagMap::IMAGEBANDLOGO() {
        static const std::string _IMAGEBANDLOGO = "IMAGEBANDLOGO"s;
        return _IMAGEBANDLOGO;
    }

    const std::string& TagMap::IMAGEPUBLISHERLOGO() {
        static const std::string _IMAGEPUBLISHERLOGO = "IMAGEPUBLISHERLOGO"s;
        return _IMAGEPUBLISHERLOGO;
    }

    const std::string & TagMap::INITIALKEY() {
        static const std::string _INITIALKEY = "INITIALKEY"s;
        return _INITIALKEY;
    }

    const std::string & TagMap::ISRC() {
        static const std::string _ISRC = "ISRC"s;
        return _ISRC;
    }

    const std::string& TagMap::LYRICS() {
        static const std::string _LYRICS = "LYRICS"s;
        return _LYRICS;
    }


    const std::string& TagMap::LYRICSENG() {
        static const std::string _LYRICSENG = "LYRICSENG"s;
        return _LYRICSENG;
    }


    const std::string& TagMap::LYRICIST() {
        static const std::string _LYRICIST = "LYRICIST"s;
        return _LYRICIST;
    }

    const std::string & TagMap::MOOD() {
        static const std::string _MOOD = "MOOD"s;
        return _MOOD;
    }

    const std::string & TagMap::MIXDJ() {
        static const std::string _MIXDJ = "MIXDJ"s;
        return _MIXDJ;
    }

    const std::string & TagMap::MIXENGINEER() {
        static const std::string _MIXENGINEER = "MIXENGINEER"s;
        return _MIXENGINEER;
    }

    const std::string& TagMap::ORIGINALALBUM() {
        static const std::string _ORIGINALALBUM = "ORIGINALALBUM"s;
        return _ORIGINALALBUM;
    }

    const std::string& TagMap::ORIGINALARTIST() {
        static const std::string _ORIGINALARTIST = "ORIGINALARTIST"s;
        return _ORIGINALARTIST;
    }

    const std::string& TagMap::ORIGINALDATE() {
        static const std::string _ORIGINALDATE = "ORIGINALDATE"s;
        return _ORIGINALDATE;
    }

    const std::string& TagMap::ORIGINALLYRICIST() {
        static const std::string _ORIGINALLYRICIST = "ORIGINALLYRICIST"s;
        return _ORIGINALLYRICIST;
    }

    const std::string& TagMap::PRODUCER() {
        static const std::string _PRODUCER = "PRODUCER"s;
        return _PRODUCER;
    }

    const std::string& TagMap::PUBLISHER() {
        static const std::string _PUBLISHER = "PUBLISHER"s;
        return _PUBLISHER;
    }

    const std::string & TagMap::RADIOSTATION() {
        static const std::string _RADIOSTATION = "RADIOSTATION"s;
        return _RADIOSTATION;
    }

    const std::string & TagMap::RADIOSTATIONOWNER() {
        static const std::string _RADIOSTATIONOWNER = "RADIOSTATIONOWNER"s;
        return _RADIOSTATIONOWNER;
    }

    const std::string & TagMap::REMIXER() {
        static const std::string _REMIXER = "REMIXER"s;
        return _REMIXER;
    }

    const std::string & TagMap::SETSUBTITLE() {
        static const std::string _SETSUBTITLE = "SETSUBTITLE"s;
        return _SETSUBTITLE;
    }

    const std::string& TagMap::SUBTITLE() {
        static const std::string _SUBTITLE = "SUBTITLE"s;
        return _SUBTITLE;
    }

    const std::string& TagMap::TITLE() {
        static const std::string _TITLE = "TITLE"s;
        return _TITLE;
    }

    const std::string& TagMap::TITLESORT() {
        static const std::string _TITLESORT = "TITLESORT"s;
        return _TITLESORT;
    }

    const std::string& TagMap::TOTALDISCNUMBER() {
        static const std::string _TOTALDISCNUMBER = "TOTALDISCNUMBER"s;
        return _TOTALDISCNUMBER;
    }

    const std::string& TagMap::TOTALTRACKNUMBER() {
        static const std::string _TOTALTRACKNUMBER = "TOTALTRACKNUMBER"s;
        return _TOTALTRACKNUMBER;
    }

    const std::string& TagMap::TRACKNUMBER() {
        static const std::string _TRACKNUMBER = "TRACKNUMBER"s;
        return _TRACKNUMBER;
    }

    const std::string& TagMap::WWWCOMMERCIAL() {
        static const std::string _WWWCOMMERCIAL = "WWWCOMMERCIAL"s;
        return _WWWCOMMERCIAL;
    }

    const std::string& TagMap::WWWCOPYRIGHT() {
        static const std::string _WWWCOPYRIGHT = "WWWCOPYRIGHT"s;
        return _WWWCOPYRIGHT;
    }

    const std::string& TagMap::WWWFILE() {
        static const std::string _WWWFILE = "WWWFILE"s;
        return _WWWFILE;
    }

    const std::string& TagMap::WWWARTIST() {
        static const std::string _WWWARTIST = "WWWARTIST"s;
        return _WWWARTIST;
    }

    const std::string& TagMap::WWWFILESOURCE() {
        static const std::string _WWWFILESOURCE = "WWWFILESOURCE"s;
        return _WWWFILESOURCE;
    }

    const std::string& TagMap::WWWPAYMENT() {
        static const std::string _WWWPAYMENT = "WWWPAYMENT"s;
        return _WWWPAYMENT;
    }

    const std::string& TagMap::WWWPODCAST() {
        static const std::string _WWWPODCAST = "WWWPODCAST"s;
        return _WWWPODCAST;
    }

    const std::string& TagMap::WWWPUBLISHER() {
        static const std::string _WWWPUBLISHER = "WWWPUBLISHER"s;
        return _WWWPUBLISHER;
    }

    const std::string& TagMap::WWWRADIOPAGE() {
        static const std::string _WWWRADIOPAGE = "WWWRADIOPAGE"s;
        return _WWWRADIOPAGE;
    }






    TagMap::iterator TagMap::begin() {
        return iterator(tagMap.begin());
    }
    TagMap::const_iterator TagMap::begin() const {
        return cbegin();
    }
    TagMap::const_iterator TagMap::cbegin() const {
        return const_iterator(const_cast<TagMap*>(this)->tagMap.begin());
    }




    TagMap::iterator TagMap::end() {
        return iterator(tagMap.end());
    }

    TagMap::const_iterator TagMap::end() const {
        return cend();
    }

    TagMap::const_iterator TagMap::cend() const {
        return const_iterator(const_cast<TagMap*>(this)->tagMap.begin());
    }

    void TagMap::merge(TagMap & source) {
        tagMap.merge(source.tagMap);

    }

    void TagMap::merge(TagMap && source) {
        tagMap.merge(source.tagMap);
    }




    void TagMap::mergeWithOverwrite(TagMap & source) {
        for (auto &item : source.tagMap)
            tagMap.erase(item.first);
        tagMap.merge(source.tagMap);
    }

    void TagMap::mergeWithOverwrite(TagMap && source) {
        for (auto &item : source.tagMap)
            tagMap.erase(item.first);
        tagMap.merge(source.tagMap);
    }





    void TagMap::clear() {
        tagMap.clear();
    }

    std::size_t TagMap::getSize() const noexcept {
        return tagMap.size();
    }

    bool TagMap::isEmpty() const noexcept {
        return tagMap.empty();
    }

    bool TagMap::containsTag(const std::string_view &name) const {
        return tagMap.find(name) != tagMap.end();
    }

    bool TagMap::removeTag(const std::string &name) {
        return tagMap.erase(name) > 0;
    }

    std::size_t TagMap::removeEmpty() {
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





    TagMap::iterator TagMap::getTagIterator(const std::string_view & name) {
        return iterator(tagMap.find(name));
    }

    TagMap::const_iterator TagMap::getTagIterator(const std::string_view & name) const {
        return iterator(const_cast<TagMap*>(this)->tagMap.find(name));
    }

    SharedConstAudioTag TagMap::getTagPointer(const std::string_view &name) const {
        const_iterator it = getTagIterator(name);
        if (it != end())
            return *it;
        return SharedConstAudioTag();
    }

    SharedAudioTag TagMap::getTagPointer(const std::string_view &name) {
        iterator it = getTagIterator(name);
        if (it != end())
            return *it;
        return SharedAudioTag();
    }








    SharedStringAudioTag TagMap::getStringTagPointer(const std::string_view &name) {
        return getTypeTagPointer<StringTag>(name);
    }

    SharedConstStringAudioTag TagMap::getStringTagPointer(const std::string_view &name) const {
        return getTypeTagPointer<StringTag>(name);
    }

    std::optional<std::string> TagMap::getStringTagOptional(const std::string_view &name) const {
        auto tag = getStringTagPointer(name);
        if (tag == nullptr)
            return std::nullopt;
        return tag->getText();
    }

    std::string TagMap::getStringTag(const std::string_view &name) const {
        auto tag = getStringTagPointer(name);
        if (tag == nullptr)
            return std::string();
        return tag->getText();
    }

    bool TagMap::setStringTag(const std::string_view & name, const std::string & text) {
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
            tagMap.insert(std::make_pair(std::string(name), std::make_shared<StringTag>(std::string(name), text)));
        return true;
    }





    SharedNumberAudioTag TagMap::getNumberTagPointer(const std::string_view &name) {
        return getTypeTagPointer<NumberTag>(name);
    }

    SharedConstNumberAudioTag TagMap::getNumberTagPointer(const std::string_view &name) const {
        return getTypeTagPointer<NumberTag>(name);
    }

    std::optional<std::uint32_t> TagMap::getNumberTagOptional(const std::string_view &name) const {
        auto tag = getNumberTagPointer(name);
        if (tag == nullptr)
            return std::nullopt;
        return tag->getNumber();
    }

    std::uint32_t TagMap::getNumberTag(const std::string_view &name) const {
        auto tag = getNumberTagPointer(name);
        if (tag == nullptr)
            return std::uint32_t(-1);
        return tag->getNumber();
    }

    bool TagMap::setNumberTag(const std::string_view & name, std::uint32_t number) {
        if (boost::starts_with(name, LYRICS()))
            return false;
        bool numberDefined = NUMBER_TAG_NAMES.find(name) != NUMBER_TAG_NAMES.end();
        if (!numberDefined)
            return false;
        SharedNumberAudioTag tag = getNumberTagPointer(name);
        if (tag != nullptr)
            tag->setNumber(number);
        else
            tagMap.insert(std::make_pair(std::string(name), std::make_shared<NumberTag>(std::string(name), number)));
        return true;
    }



    SharedDateAudioTag TagMap::getDateTagPointer(const std::string_view &name) {
        return getTypeTagPointer<DateTag>(name);
    }

    SharedConstDateAudioTag TagMap::getDateTagPointer(const std::string_view &name) const {
        return getTypeTagPointer<DateTag>(name);
    }

    std::optional<types::Date> TagMap::getDateTagOptional(const std::string_view &name) const {
        auto tag = getDateTagPointer(name);
        if (tag == nullptr)
            return std::nullopt;
        return tag->getDate();
    }

    types::Date TagMap::getDateTag(const std::string_view &name) const {
        auto tag = getDateTagPointer(name);
        if (tag == nullptr)
            return types::Date();
        return tag->getDate();
    }

    bool TagMap::setDateTag(const std::string_view & name, const types::Date &date) {
        if (boost::starts_with(name, LYRICS()))
            return false;
        bool dateDefined = DATE_TAG_NAMES.find(name) != DATE_TAG_NAMES.end();
        if (!dateDefined)
            return false;
        SharedDateAudioTag tag = getDateTagPointer(name);
        if (tag != nullptr)
            tag->setDate(date);
        else
            tagMap.insert(std::make_pair(std::string(name), std::make_shared<DateTag>(std::string(name), date)));
        return true;
    }




    SharedLyricsAudioTag TagMap::getLyricsTagPointerByLang(std::string language) {
        boost::to_upper(language);
        return getTypeTagPointer<LyricsTag>(LYRICS() + language);
    }

    SharedConstLyricsAudioTag TagMap::getLyricsTagPointerByLang(std::string language) const {
        boost::to_upper(language);
        return getTypeTagPointer<LyricsTag>(LYRICS() + language);
    }

    SharedLyricsAudioTag TagMap::getLyricsTagPointer(const std::string_view &name) {
        return getTypeTagPointer<LyricsTag>(name);
    }

    SharedConstLyricsAudioTag TagMap::getLyricsTagPointer(const std::string_view &name) const {
        return getTypeTagPointer<LyricsTag>(name);
    }

    std::optional<types::Lyrics> TagMap::getLyricsTagOptionalByLang(std::string language) const {
        auto tag = getLyricsTagPointerByLang(std::move(language));
        if (tag == nullptr)
            return std::nullopt;
        return tag->getLyrics();
    }

    std::optional<types::Lyrics> TagMap::getLyricsTagOptional(const std::string_view &name) const {
        auto tag = getLyricsTagPointer(name);
        if (tag == nullptr)
            return std::nullopt;
        return tag->getLyrics();
    }

    types::Lyrics TagMap::getLyricsTagByLang(std::string language) const {
        auto tag = getLyricsTagPointerByLang(std::move(language));
        if (tag == nullptr)
            return types::Lyrics();
        return tag->getLyrics();
    }

    types::Lyrics TagMap::getLyricsTag(const std::string_view &name) const {
        auto tag = getLyricsTagPointer(name);
        if (tag == nullptr)
            return types::Lyrics();
        return tag->getLyrics();    }

    bool TagMap::setLyricsTagByLang(const std::string & language, const types::Lyrics & lyrics) {
        if (language.empty())
            return false;
        std::string name = LYRICS() + boost::to_upper_copy(language);
        SharedLyricsAudioTag tag = getLyricsTagPointerByLang(name);
        if (tag != nullptr)
            tag->setLyrics(lyrics);
        else
            tagMap.insert(std::make_pair(name, std::make_shared<LyricsTag>(language, lyrics)));
        return true;
    }

    bool TagMap::setLyricsTag(const std::string_view & name, const types::Lyrics & lyrics) {
        if (!boost::starts_with(LYRICS(), name))
            return false;
        if (name == LYRICS())
            return false;
        SharedLyricsAudioTag tag = getLyricsTagPointer(name);
        if (tag != nullptr) {
            tag->setLyrics(lyrics);
        } else {
            std::string language = std::string(name.substr(LYRICS().size()));
            tagMap.insert(std::make_pair(std::string(name), std::make_shared<LyricsTag>(language, lyrics)));
        }
        return true;
    }



    SharedImageAudioTag TagMap::getImageTagPointer(const std::string_view &name) {
        return getTypeTagPointer<ImageTag>(name);

    }

    SharedImageAudioTag TagMap::getImageTagPointer(ImageTag::ImageType imageType) {
        return getImageTagPointer(string::toString(imageType));
    }

    SharedConstImageAudioTag TagMap::getImageTagPointer(const std::string_view &name) const {
        return getTypeTagPointer<ImageTag>(name);
    }

    SharedConstImageAudioTag TagMap::getImageTagPointer(ImageTag::ImageType imageType) const {
        return getImageTagPointer(string::toString(imageType));
    }

    std::optional<types::Image> TagMap::getImageTagOptional(const std::string_view &name) const {
        auto tag = getImageTagPointer(name);
        if (tag == nullptr)
            return std::nullopt;
        return tag->getImage();
    }

    std::optional<types::Image> TagMap::getImageTagOptional(ImageTag::ImageType imageType) const {
        auto tag = getImageTagPointer(imageType);
        if (tag == nullptr)
            return std::nullopt;
        return tag->getImage();
    }

    types::Image TagMap::getImageTag(const std::string_view &name) const {
        auto tag = getImageTagPointer(name);
        if (tag == nullptr)
            return types::Image();
        return tag->getImage();
    }

    types::Image TagMap::getImageTag(ImageTag::ImageType imageType) const {
        auto tag = getImageTagPointer(imageType);
        if (tag == nullptr)
            return types::Image();
        return tag->getImage();
    }

    bool TagMap::setImageTag(const std::string_view & name, const types::Image & image) {
        if (boost::starts_with(name, LYRICS()))
            return false;
        bool imageDefined = IMAGE_TAG_NAMES.find(name) != IMAGE_TAG_NAMES.end();
        if (!imageDefined)
            return false;
        SharedImageAudioTag tag = getImageTagPointer(name);
        if (tag != nullptr)
            tag->setImage(image);
        else
            tagMap.insert(std::make_pair(std::string(name), std::make_shared<ImageTag>(std::string(name), image)));
        return true;
    }

    bool TagMap::setImageTag(const std::string_view & name, types::Image && image) {
        if (boost::starts_with(name, LYRICS()))
            return false;
        bool imageDefined = IMAGE_TAG_NAMES.find(name) != IMAGE_TAG_NAMES.end();
        if (!imageDefined)
            return false;
        SharedImageAudioTag tag = getImageTagPointer(name);
        if (tag != nullptr)
            tag->setImage(std::move(image));
        else
            tagMap.insert(std::make_pair(std::string(name), std::make_shared<ImageTag>(std::string(name), std::move(image))));
        return true;
    }

    bool TagMap::setImageTag(ImageTag::ImageType imageType, const types::Image & image) {
        return setImageTag(string::toString(imageType), image);
    }

    bool TagMap::setImageTag(ImageTag::ImageType imageType, types::Image && image) {
        return setImageTag(string::toString(imageType), std::move(image));
    }



    SharedConstISRCAudioTag TagMap::getISRCTagPointer(const std::string_view &name) const {
        return getTypeTagPointer<ISRCTag>(name);

    }

    SharedISRCAudioTag TagMap::getISRCTagPointer(const std::string_view &name) {
        return getTypeTagPointer<ISRCTag>(name);
    }

    std::optional<types::ISRC> TagMap::getISRCTagOptional(const std::string_view &name) const {
        auto tag = getISRCTagPointer(name);
        if (tag == nullptr)
            return std::nullopt;
        return tag->getISRC();
    }

    types::ISRC TagMap::getISRCTag(const std::string_view &name) const {
        auto tag = getISRCTagPointer(name);
        if (tag == nullptr)
            return types::ISRC();
        return tag->getISRC();
    }

    bool TagMap::setISRCTag(const std::string_view &name, const types::ISRC & isrc) {
        if (name != ISRC())
            return false;
        SharedISRCAudioTag tag = getISRCTagPointer(name);
        if (tag != nullptr) {
            tag->setISRC(isrc);
            return true;
        } else
            return tagMap.insert(std::make_pair(
                                     ISRC(), std::make_shared<ISRCTag>(isrc)
                                 )).second;
    }



    SharedConstBarcodeAudioTag TagMap::getBarcodeTagPointer(const std::string_view &name) const {
        return getTypeTagPointer<BarcodeTag>(name);

    }

    SharedBarcodeAudioTag TagMap::getBarcodeTagPointer(const std::string_view &name) {
        return getTypeTagPointer<BarcodeTag>(name);
    }

    std::optional<types::Barcode> TagMap::getBarcodeTagOptional(const std::string_view &name) const {
        auto tag = getBarcodeTagPointer(name);
        if (tag == nullptr)
            return std::nullopt;
        return tag->getBarcode();
    }

    types::Barcode TagMap::getBarcodeTag(const std::string_view &name) const {
        auto tag = getBarcodeTagPointer(name);
        if (tag == nullptr)
            return types::Barcode();
        return tag->getBarcode();
    }

    bool TagMap::setBarcodeTag(const std::string_view &name, const types::Barcode & barcode) {
        if (name != BARCODE())
            return false;
        SharedBarcodeAudioTag tag = getBarcodeTagPointer(name);
        if (tag != nullptr) {
            tag->setBarcode(barcode);
            return true;
        } else
            return tagMap.insert(std::make_pair(
                    BARCODE(), std::make_shared<BarcodeTag>(barcode)
            )).second;
    }











    SharedConstStringAudioTag TagMap::getAlbumPointer() const {
        return getStringTagPointer(ALBUM());
    }

    SharedStringAudioTag TagMap::getAlbumPointer() {
        return getStringTagPointer(ALBUM());
    }

    std::optional<std::string> TagMap::getAlbumOptional() const {
        return getStringTagOptional(ALBUM());
    }

    std::string TagMap::getAlbum() const {
        return getStringTag(ALBUM());
    }

    bool TagMap::setAlbum(const std::string& album) {
        return setStringTag(ALBUM(), album);
    }



    SharedConstStringAudioTag TagMap::getAlbumArtistPointer() const {
        return getStringTagPointer(ALBUMARTIST());
    }

    SharedStringAudioTag TagMap::getAlbumArtistPointer() {
        return getStringTagPointer(ALBUMARTIST());
    }

    std::optional<std::string> TagMap::getAlbumArtistOptional() const {
        return getStringTagOptional(ALBUMARTIST());
    }

    std::string TagMap::getAlbumArtist() const {
        return getStringTag(ALBUMARTIST());
    }

    bool TagMap::setAlbumArtist(const std::string& albumArtist) {
        return setStringTag(ALBUMARTIST(), albumArtist);
    }



    SharedConstStringAudioTag TagMap::getAlbumArtistSortPointer() const {
        return getStringTagPointer(ALBUMARTISTSORT());
    }

    SharedStringAudioTag TagMap::getAlbumArtistSortPointer() {
        return getStringTagPointer(ALBUMARTISTSORT());
    }

    std::optional<std::string> TagMap::getAlbumArtistSortOptional() const {
        return getStringTagOptional(ALBUMARTISTSORT());
    }

    std::string TagMap::getAlbumArtistSort() const {
        return getStringTag(ALBUMARTISTSORT());
    }

    bool TagMap::setAlbumArtistSort(const std::string& albumArtistSort) {
        return setStringTag(ALBUMARTISTSORT(), albumArtistSort);
    }



    SharedConstStringAudioTag TagMap::getAlbumSortPointer() const {
        return getStringTagPointer(ALBUMSORT());
    }

    SharedStringAudioTag TagMap::getAlbumSortPointer() {
        return getStringTagPointer(ALBUMSORT());
    }

    std::optional<std::string> TagMap::getAlbumSortOptional() const {
        return getStringTagOptional(ALBUMSORT());
    }

    std::string TagMap::getAlbumSort() const {
        return getStringTag(ALBUMSORT());
    }

    bool TagMap::setAlbumSort(const std::string& albumSort) {
        return setStringTag(ALBUMSORT(), albumSort);
    }



    SharedConstStringAudioTag TagMap::getArrangerPointer() const {
        return getStringTagPointer(ARRANGER());
    }

    SharedStringAudioTag TagMap::getArrangerPointer() {
        return getStringTagPointer(ARRANGER());
    }

    std::optional<std::string> TagMap::getArrangerOptional() const {
        return getStringTagOptional(ARRANGER());
    }

    std::string TagMap::getArranger() const {
        return getStringTag(ARRANGER());
    }

    bool TagMap::setArranger(const std::string& arranger) {
        return setStringTag(ARRANGER(), arranger);
    }



    SharedConstStringAudioTag TagMap::getArtistPointer() const {
        return getStringTagPointer(ARTIST());
    }

    SharedStringAudioTag TagMap::getArtistPointer() {
        return getStringTagPointer(ARTIST());
    }

    std::optional<std::string> TagMap::getArtistOptional() const {
        return getStringTagOptional(ARTIST());
    }

    std::string TagMap::getArtist() const {
        return getStringTag(ARTIST());
    }

    bool TagMap::setArtist(const std::string& artist) {
        return setStringTag(ARTIST(), artist);
    }



    SharedConstStringAudioTag TagMap::getArtistSortPointer() const {
        return getStringTagPointer(ARTISTSORT());
    }

    SharedStringAudioTag TagMap::getArtistSortPointer() {
        return getStringTagPointer(ARTISTSORT());
    }

    std::optional<std::string> TagMap::getArtistSortOptional() const {
        return getStringTagOptional(ARTISTSORT());
    }

    std::string TagMap::getArtistSort() const {
        return getStringTag(ARTISTSORT());
    }

    bool TagMap::setArtistSort(const std::string& artistSort) {
        return setStringTag(ARTISTSORT(), artistSort);
    }



    SharedConstStringAudioTag TagMap::getCommentPointer() const {
        return getStringTagPointer(COMMENT());
    }

    SharedStringAudioTag TagMap::getCommentPointer() {
        return getStringTagPointer(COMMENT());
    }

    std::optional<std::string> TagMap::getCommentOptional() const {
        return getStringTagOptional(COMMENT());
    }

    std::string TagMap::getComment() const {
        return getStringTag(COMMENT());
    }

    bool TagMap::setComment(const std::string& comment) {
        return setStringTag(COMMENT(), comment);
    }



    SharedConstStringAudioTag TagMap::getComposerPointer() const {
        return getStringTagPointer(COMPOSER());
    }

    SharedStringAudioTag TagMap::getComposerPointer() {
        return getStringTagPointer(COMPOSER());
    }

    std::optional<std::string> TagMap::getComposerOptional() const {
        return getStringTagOptional(COMPOSER());
    }

    std::string TagMap::getComposer() const {
        return getStringTag(COMPOSER());
    }

    bool TagMap::setComposer(const std::string& composer) {
        return setStringTag(COMPOSER(), composer);
    }



    SharedConstStringAudioTag TagMap::getComposerSortPointer() const {
        return getStringTagPointer(COMPOSERSORT());
    }

    SharedStringAudioTag TagMap::getComposerSortPointer() {
        return getStringTagPointer(COMPOSERSORT());
    }

    std::optional<std::string> TagMap::getComposerSortOptional() const {
        return getStringTagOptional(COMPOSERSORT());
    }

    std::string TagMap::getComposerSort() const {
        return getStringTag(COMPOSERSORT());
    }

    bool TagMap::setComposerSort(const std::string& composerSort) {
        return setStringTag(COMPOSERSORT(), composerSort);
    }



    SharedConstStringAudioTag TagMap::getConductorPointer() const {
        return getStringTagPointer(CONDUCTOR());
    }

    SharedStringAudioTag TagMap::getConductorPointer() {
        return getStringTagPointer(CONDUCTOR());
    }

    std::optional<std::string> TagMap::getConductorOptional() const {
        return getStringTagOptional(CONDUCTOR());
    }

    std::string TagMap::getConductor() const {
        return getStringTag(CONDUCTOR());
    }

    bool TagMap::setConductor(const std::string& conductor) {
        return setStringTag(CONDUCTOR(), conductor);
    }



    SharedConstStringAudioTag TagMap::getContentGroupPointer() const {
        return getStringTagPointer(CONTENTGROUP());
    }

    SharedStringAudioTag TagMap::getContentGroupPointer() {
        return getStringTagPointer(CONTENTGROUP());
    }

    std::optional<std::string> TagMap::getContentGroupOptional() const {
        return getStringTagOptional(CONTENTGROUP());
    }

    std::string TagMap::getContentGroup() const {
        return getStringTag(CONTENTGROUP());
    }

    bool TagMap::setContentGroup(const std::string& contentGroup) {
        return setStringTag(CONTENTGROUP(), contentGroup);
    }



    SharedConstStringAudioTag TagMap::getCopyrightPointer() const {
        return getStringTagPointer(COPYRIGHT());
    }

    SharedStringAudioTag TagMap::getCopyrightPointer() {
        return getStringTagPointer(COPYRIGHT());
    }

    std::optional<std::string> TagMap::getCopyrightOptional() const {
        return getStringTagOptional(COPYRIGHT());
    }

    std::string TagMap::getCopyright() const {
        return getStringTag(COPYRIGHT());
    }

    bool TagMap::setCopyright(const std::string& copyright) {
        return setStringTag(COPYRIGHT(), copyright);
    }



    SharedConstStringAudioTag TagMap::getEngineerPointer() const {
        return getStringTagPointer(ENGINEER());
    }

    SharedStringAudioTag TagMap::getEngineerPointer() {
        return getStringTagPointer(ENGINEER());
    }

    std::optional<std::string> TagMap::getEngineerOptional() const {
        return getStringTagOptional(ENGINEER());
    }

    std::string TagMap::getEngineer() const {
        return getStringTag(ENGINEER());
    }

    bool TagMap::setEngineer(const std::string& engineer) {
        return setStringTag(ENGINEER(), engineer);
    }



    SharedConstStringAudioTag TagMap::getEncodedBYPointer() const {
        return getStringTagPointer(ENCODEDBY());
    }

    SharedStringAudioTag TagMap::getEncodedBYPointer() {
        return getStringTagPointer(ENCODEDBY());
    }

    std::optional<std::string> TagMap::getEncodedBYOptional() const {
        return getStringTagOptional(ENCODEDBY());
    }

    std::string TagMap::getEncodedBY() const {
        return getStringTag(ENCODEDBY());
    }

    bool TagMap::setEncodedBY(const std::string& encodedBY) {
        return setStringTag(ENCODEDBY(), encodedBY);
    }



    SharedConstStringAudioTag TagMap::getEncoderSettingsPointer() const {
        return getStringTagPointer(ENCODERSETTINGS());
    }

    SharedStringAudioTag TagMap::getEncoderSettingsPointer() {
        return getStringTagPointer(ENCODERSETTINGS());
    }

    std::optional<std::string> TagMap::getEncoderSettingsOptional() const {
        return getStringTagOptional(ENCODERSETTINGS());
    }

    std::string TagMap::getEncoderSettings() const {
        return getStringTag(ENCODERSETTINGS());
    }

    bool TagMap::setEncoderSettings(const std::string& encoderSettings) {
        return setStringTag(ENCODERSETTINGS(), encoderSettings);
    }



    SharedConstStringAudioTag TagMap::getGenrePointer() const {
        return getStringTagPointer(GENRE());
    }

    SharedStringAudioTag TagMap::getGenrePointer() {
        return getStringTagPointer(GENRE());
    }

    std::optional<std::string> TagMap::getGenreOptional() const {
        return getStringTagOptional(GENRE());
    }

    std::string TagMap::getGenre() const {
        return getStringTag(GENRE());
    }

    bool TagMap::setGenre(const std::string& genre) {
        return setStringTag(GENRE(), genre);
    }



    SharedConstStringAudioTag TagMap::getInitialKeyPointer() const {
        return getStringTagPointer(INITIALKEY());
    }

    SharedStringAudioTag TagMap::getInitialKeyPointer() {
        return getStringTagPointer(INITIALKEY());
    }

    std::optional<std::string> TagMap::getInitialKeyOptional() const {
        return getStringTagOptional(INITIALKEY());
    }

    std::string TagMap::getInitialKey() const {
        return getStringTag(INITIALKEY());
    }

    bool TagMap::setInitialKey(const std::string& initialKey) {
        return setStringTag(INITIALKEY(), initialKey);
    }



    SharedConstStringAudioTag TagMap::getLyricistPointer() const {
        return getStringTagPointer(LYRICIST());
    }

    SharedStringAudioTag TagMap::getLyricistPointer() {
        return getStringTagPointer(LYRICIST());
    }

    std::optional<std::string> TagMap::getLyricistOptional() const {
        return getStringTagOptional(LYRICIST());
    }

    std::string TagMap::getLyricist() const {
        return getStringTag(LYRICIST());
    }

    bool TagMap::setLyricist(const std::string& lyricist) {
        return setStringTag(LYRICIST(), lyricist);
    }



    SharedConstStringAudioTag TagMap::getMixDJPointer() const {
        return getStringTagPointer(MIXDJ());
    }

    SharedStringAudioTag TagMap::getMixDJPointer() {
        return getStringTagPointer(MIXDJ());
    }

    std::optional<std::string> TagMap::getMixDJOptional() const {
        return getStringTagOptional(MIXDJ());
    }

    std::string TagMap::getMixDJ() const {
        return getStringTag(MIXDJ());
    }

    bool TagMap::setMixDJ(const std::string& mixDJ) {
        return setStringTag(MIXDJ(), mixDJ);
    }



    SharedConstStringAudioTag TagMap::getMixEngineerPointer() const {
        return getStringTagPointer(MIXENGINEER());
    }

    SharedStringAudioTag TagMap::getMixEngineerPointer() {
        return getStringTagPointer(MIXENGINEER());
    }

    std::optional<std::string> TagMap::getMixEngineerOptional() const {
        return getStringTagOptional(MIXENGINEER());
    }

    std::string TagMap::getMixEngineer() const {
        return getStringTag(MIXENGINEER());
    }

    bool TagMap::setMixEngineer(const std::string& mixEngineer) {
        return setStringTag(MIXENGINEER(), mixEngineer);
    }



    SharedConstStringAudioTag TagMap::getMoodPointer() const {
        return getStringTagPointer(MOOD());
    }

    SharedStringAudioTag TagMap::getMoodPointer() {
        return getStringTagPointer(MOOD());
    }

    std::optional<std::string> TagMap::getMoodOptional() const {
        return getStringTagOptional(MOOD());
    }

    std::string TagMap::getMood() const {
        return getStringTag(MOOD());
    }

    bool TagMap::setMood(const std::string& mood) {
        return setStringTag(MOOD(), mood);
    }



    SharedConstStringAudioTag TagMap::getOriginalLyricistPointer() const {
        return getStringTagPointer(ORIGINALLYRICIST());
    }

    SharedStringAudioTag TagMap::getOriginalLyricistPointer() {
        return getStringTagPointer(ORIGINALLYRICIST());
    }

    std::optional<std::string> TagMap::getOriginalLyricistOptional() const {
        return getStringTagOptional(ORIGINALLYRICIST());
    }

    std::string TagMap::getOriginalLyricist() const {
        return getStringTag(ORIGINALLYRICIST());
    }

    bool TagMap::setOriginalLyricist(const std::string& originalLyricist) {
        return setStringTag(ORIGINALLYRICIST(), originalLyricist);
    }



    SharedConstStringAudioTag TagMap::getOriginalAlbumPointer() const {
        return getStringTagPointer(ORIGINALALBUM());
    }

    SharedStringAudioTag TagMap::getOriginalAlbumPointer() {
        return getStringTagPointer(ORIGINALALBUM());
    }

    std::optional<std::string> TagMap::getOriginalAlbumOptional() const {
        return getStringTagOptional(ORIGINALALBUM());
    }

    std::string TagMap::getOriginalAlbum() const {
        return getStringTag(ORIGINALALBUM());
    }

    bool TagMap::setOriginalAlbum(const std::string& originalAlbum) {
        return setStringTag(ORIGINALALBUM(), originalAlbum);
    }



    SharedConstStringAudioTag TagMap::getOriginalArtistPointer() const {
        return getStringTagPointer(ORIGINALARTIST());
    }

    SharedStringAudioTag TagMap::getOriginalArtistPointer() {
        return getStringTagPointer(ORIGINALARTIST());
    }

    std::optional<std::string> TagMap::getOriginalArtistOptional() const {
        return getStringTagOptional(ORIGINALARTIST());
    }

    std::string TagMap::getOriginalArtist() const {
        return getStringTag(ORIGINALARTIST());
    }

    bool TagMap::setOriginalArtist(const std::string& originalArtist) {
        return setStringTag(ORIGINALARTIST(), originalArtist);
    }



    SharedConstStringAudioTag TagMap::getProducerPointer() const {
        return getStringTagPointer(PRODUCER());
    }

    SharedStringAudioTag TagMap::getProducerPointer() {
        return getStringTagPointer(PRODUCER());
    }

    std::optional<std::string> TagMap::getProducerOptional() const {
        return getStringTagOptional(PRODUCER());
    }

    std::string TagMap::getProducer() const {
        return getStringTag(PRODUCER());
    }

    bool TagMap::setProducer(const std::string& producer) {
        return setStringTag(PRODUCER(), producer);
    }



    SharedConstStringAudioTag TagMap::getPublisherPointer() const {
        return getStringTagPointer(PUBLISHER());
    }

    SharedStringAudioTag TagMap::getPublisherPointer() {
        return getStringTagPointer(PUBLISHER());
    }

    std::optional<std::string> TagMap::getPublisherOptional() const {
        return getStringTagOptional(PUBLISHER());
    }

    std::string TagMap::getPublisher() const {
        return getStringTag(PUBLISHER());
    }

    bool TagMap::setPublisher(const std::string& publisher) {
        return setStringTag(PUBLISHER(), publisher);
    }



    SharedConstStringAudioTag TagMap::getRadioStationPointer() const {
        return getStringTagPointer(RADIOSTATION());
    }

    SharedStringAudioTag TagMap::getRadioStationPointer() {
        return getStringTagPointer(RADIOSTATION());
    }

    std::optional<std::string> TagMap::getRadioStationOptional() const {
        return getStringTagOptional(RADIOSTATION());
    }

    std::string TagMap::getRadioStation() const {
        return getStringTag(RADIOSTATION());
    }

    bool TagMap::setRadioStation(const std::string& radioStation) {
        return setStringTag(RADIOSTATION(), radioStation);
    }



    SharedConstStringAudioTag TagMap::getRadioStationOwnerPointer() const {
        return getStringTagPointer(RADIOSTATIONOWNER());
    }

    SharedStringAudioTag TagMap::getRadioStationOwnerPointer() {
        return getStringTagPointer(RADIOSTATIONOWNER());
    }

    std::optional<std::string> TagMap::getRadioStationOwnerOptional() const {
        return getStringTagOptional(RADIOSTATIONOWNER());
    }

    std::string TagMap::getRadioStationOwner() const {
        return getStringTag(RADIOSTATIONOWNER());
    }

    bool TagMap::setRadioStationOwner(const std::string& radioStationOwner) {
        return setStringTag(RADIOSTATIONOWNER(), radioStationOwner);
    }



    SharedConstStringAudioTag TagMap::getRemixerPointer() const {
        return getStringTagPointer(REMIXER());
    }

    SharedStringAudioTag TagMap::getRemixerPointer() {
        return getStringTagPointer(REMIXER());
    }

    std::optional<std::string> TagMap::getRemixerOptional() const {
        return getStringTagOptional(REMIXER());
    }

    std::string TagMap::getRemixer() const {
        return getStringTag(REMIXER());
    }

    bool TagMap::setRemixer(const std::string& remixer) {
        return setStringTag(REMIXER(), remixer);
    }



    SharedConstStringAudioTag TagMap::getSetSubtitlePointer() const {
        return getStringTagPointer(SETSUBTITLE());
    }

    SharedStringAudioTag TagMap::getSetSubtitlePointer() {
        return getStringTagPointer(SETSUBTITLE());
    }

    std::optional<std::string> TagMap::getSetSubtitleOptional() const {
        return getStringTagOptional(SETSUBTITLE());
    }

    std::string TagMap::getSetSubtitle() const {
        return getStringTag(SETSUBTITLE());
    }

    bool TagMap::setSetSubtitle(const std::string& setSubtitle) {
        return setStringTag(SETSUBTITLE(), setSubtitle);
    }



    SharedConstStringAudioTag TagMap::getSubtitlePointer() const {
        return getStringTagPointer(SUBTITLE());
    }

    SharedStringAudioTag TagMap::getSubtitlePointer() {
        return getStringTagPointer(SUBTITLE());
    }

    std::optional<std::string> TagMap::getSubtitleOptional() const {
        return getStringTagOptional(SUBTITLE());
    }

    std::string TagMap::getSubtitle() const {
        return getStringTag(SUBTITLE());
    }

    bool TagMap::setSubtitle(const std::string& subtitle) {
        return setStringTag(SUBTITLE(), subtitle);
    }



    SharedConstStringAudioTag TagMap::getTitlePointer() const {
        return getStringTagPointer(TITLE());
    }

    SharedStringAudioTag TagMap::getTitlePointer() {
        return getStringTagPointer(TITLE());
    }

    std::optional<std::string> TagMap::getTitleOptional() const {
        return getStringTagOptional(TITLE());
    }

    std::string TagMap::getTitle() const {
        return getStringTag(TITLE());
    }

    bool TagMap::setTitle(const std::string& title) {
        return setStringTag(TITLE(), title);
    }



    SharedConstStringAudioTag TagMap::getTitleSortPointer() const {
        return getStringTagPointer(TITLESORT());
    }

    SharedStringAudioTag TagMap::getTitleSortPointer() {
        return getStringTagPointer(TITLESORT());
    }

    std::optional<std::string> TagMap::getTitleSortOptional() const {
        return getStringTagOptional(TITLESORT());
    }

    std::string TagMap::getTitleSort() const {
        return getStringTag(TITLESORT());
    }

    bool TagMap::setTitleSort(const std::string& titleSort) {
        return setStringTag(TITLESORT(), titleSort);
    }



    SharedConstStringAudioTag TagMap::getWWWCommercialPointer() const {
        return getStringTagPointer(WWWCOMMERCIAL());
    }

    SharedStringAudioTag TagMap::getWWWCommercialPointer() {
        return getStringTagPointer(WWWCOMMERCIAL());
    }

    std::optional<std::string> TagMap::getWWWCommercialOptional() const {
        return getStringTagOptional(WWWCOMMERCIAL());
    }

    std::string TagMap::getWWWCommercial() const {
        return getStringTag(WWWCOMMERCIAL());
    }

    bool TagMap::setWWWCommercial(const std::string& wWWCommercial) {
        return setStringTag(WWWCOMMERCIAL(), wWWCommercial);
    }



    SharedConstStringAudioTag TagMap::getWWWCopyrightPointer() const {
        return getStringTagPointer(WWWCOPYRIGHT());
    }

    SharedStringAudioTag TagMap::getWWWCopyrightPointer() {
        return getStringTagPointer(WWWCOPYRIGHT());
    }

    std::optional<std::string> TagMap::getWWWCopyrightOptional() const {
        return getStringTagOptional(WWWCOPYRIGHT());
    }

    std::string TagMap::getWWWCopyright() const {
        return getStringTag(WWWCOPYRIGHT());
    }

    bool TagMap::setWWWCopyright(const std::string& wWWCopyright) {
        return setStringTag(WWWCOPYRIGHT(), wWWCopyright);
    }



    SharedConstStringAudioTag TagMap::getWWWFilePointer() const {
        return getStringTagPointer(WWWFILE());
    }

    SharedStringAudioTag TagMap::getWWWFilePointer() {
        return getStringTagPointer(WWWFILE());
    }

    std::optional<std::string> TagMap::getWWWFileOptional() const {
        return getStringTagOptional(WWWFILE());
    }

    std::string TagMap::getWWWFile() const {
        return getStringTag(WWWFILE());
    }

    bool TagMap::setWWWFile(const std::string& wWWFile) {
        return setStringTag(WWWFILE(), wWWFile);
    }



    SharedConstStringAudioTag TagMap::getWWWArtistPointer() const {
        return getStringTagPointer(WWWARTIST());
    }

    SharedStringAudioTag TagMap::getWWWArtistPointer() {
        return getStringTagPointer(WWWARTIST());
    }

    std::optional<std::string> TagMap::getWWWArtistOptional() const {
        return getStringTagOptional(WWWARTIST());
    }

    std::string TagMap::getWWWArtist() const {
        return getStringTag(WWWARTIST());
    }

    bool TagMap::setWWWArtist(const std::string& wWWArtist) {
        return setStringTag(WWWARTIST(), wWWArtist);
    }



    SharedConstStringAudioTag TagMap::getWWWFileSourcePointer() const {
        return getStringTagPointer(WWWFILESOURCE());
    }

    SharedStringAudioTag TagMap::getWWWFileSourcePointer() {
        return getStringTagPointer(WWWFILESOURCE());
    }

    std::optional<std::string> TagMap::getWWWFileSourceOptional() const {
        return getStringTagOptional(WWWFILESOURCE());
    }

    std::string TagMap::getWWWFileSource() const {
        return getStringTag(WWWFILESOURCE());
    }

    bool TagMap::setWWWFileSource(const std::string& wWWFileSource) {
        return setStringTag(WWWFILESOURCE(), wWWFileSource);
    }



    SharedConstStringAudioTag TagMap::getWWWPaymentPointer() const {
        return getStringTagPointer(WWWPAYMENT());
    }

    SharedStringAudioTag TagMap::getWWWPaymentPointer() {
        return getStringTagPointer(WWWPAYMENT());
    }

    std::optional<std::string> TagMap::getWWWPaymentOptional() const {
        return getStringTagOptional(WWWPAYMENT());
    }

    std::string TagMap::getWWWPayment() const {
        return getStringTag(WWWPAYMENT());
    }

    bool TagMap::setWWWPayment(const std::string& wWWPayment) {
        return setStringTag(WWWPAYMENT(), wWWPayment);
    }



    SharedConstStringAudioTag TagMap::getWWWPodcastPointer() const {
        return getStringTagPointer(WWWPODCAST());
    }

    SharedStringAudioTag TagMap::getWWWPodcastPointer() {
        return getStringTagPointer(WWWPODCAST());
    }

    std::optional<std::string> TagMap::getWWWPodcastOptional() const {
        return getStringTagOptional(WWWPODCAST());
    }

    std::string TagMap::getWWWPodcast() const {
        return getStringTag(WWWPODCAST());
    }

    bool TagMap::setWWWPodcast(const std::string& wWWPodcast) {
        return setStringTag(WWWPODCAST(), wWWPodcast);
    }



    SharedConstStringAudioTag TagMap::getWWWPublisherPointer() const {
        return getStringTagPointer(WWWPUBLISHER());
    }

    SharedStringAudioTag TagMap::getWWWPublisherPointer() {
        return getStringTagPointer(WWWPUBLISHER());
    }

    std::optional<std::string> TagMap::getWWWPublisherOptional() const {
        return getStringTagOptional(WWWPUBLISHER());
    }

    std::string TagMap::getWWWPublisher() const {
        return getStringTag(WWWPUBLISHER());
    }

    bool TagMap::setWWWPublisher(const std::string& wWWPublisher) {
        return setStringTag(WWWPUBLISHER(), wWWPublisher);
    }



    SharedConstStringAudioTag TagMap::getWWWRadioPagePointer() const {
        return getStringTagPointer(WWWRADIOPAGE());
    }

    SharedStringAudioTag TagMap::getWWWRadioPagePointer() {
        return getStringTagPointer(WWWRADIOPAGE());
    }

    std::optional<std::string> TagMap::getWWWRadioPageOptional() const {
        return getStringTagOptional(WWWRADIOPAGE());
    }

    std::string TagMap::getWWWRadioPage() const {
        return getStringTag(WWWRADIOPAGE());
    }

    bool TagMap::setWWWRadioPage(const std::string& wWWRadioPage) {
        return setStringTag(WWWRADIOPAGE(), wWWRadioPage);
    }



    SharedConstNumberAudioTag TagMap::getBPMPointer() const {
        return getNumberTagPointer(BPM());
    }

    SharedNumberAudioTag TagMap::getBPMPointer() {
        return getNumberTagPointer(BPM());
    }

    std::optional<std::uint32_t> TagMap::getBPMOptional() const {
        return getNumberTagOptional(BPM());
    }

    std::uint32_t TagMap::getBPM() const {
        return getNumberTag(BPM());
    }

    bool TagMap::setBPM(std::uint32_t bPM) {
        return setNumberTag(BPM(), bPM);
    }



    SharedConstNumberAudioTag TagMap::getDiscNumberPointer() const {
        return getNumberTagPointer(DISCNUMBER());
    }

    SharedNumberAudioTag TagMap::getDiscNumberPointer() {
        return getNumberTagPointer(DISCNUMBER());
    }

    std::optional<std::uint32_t> TagMap::getDiscNumberOptional() const {
        return getNumberTagOptional(DISCNUMBER());
    }

    std::uint32_t TagMap::getDiscNumber() const {
        return getNumberTag(DISCNUMBER());
    }

    bool TagMap::setDiscNumber(std::uint32_t discNumber) {
        return setNumberTag(DISCNUMBER(), discNumber);
    }



    SharedConstNumberAudioTag TagMap::getTotalDiscNumberPointer() const {
        return getNumberTagPointer(TOTALDISCNUMBER());
    }

    SharedNumberAudioTag TagMap::getTotalDiscNumberPointer() {
        return getNumberTagPointer(TOTALDISCNUMBER());
    }

    std::optional<std::uint32_t> TagMap::getTotalDiscNumberOptional() const {
        return getNumberTagOptional(TOTALDISCNUMBER());
    }

    std::uint32_t TagMap::getTotalDiscNumber() const {
        return getNumberTag(TOTALDISCNUMBER());
    }

    bool TagMap::setTotalDiscNumber(std::uint32_t totalDiscNumber) {
        return setNumberTag(TOTALDISCNUMBER(), totalDiscNumber);
    }



    SharedConstNumberAudioTag TagMap::getTotalTrackNumberPointer() const {
        return getNumberTagPointer(TOTALTRACKNUMBER());
    }

    SharedNumberAudioTag TagMap::getTotalTrackNumberPointer() {
        return getNumberTagPointer(TOTALTRACKNUMBER());
    }

    std::optional<std::uint32_t> TagMap::getTotalTrackNumberOptional() const {
        return getNumberTagOptional(TOTALTRACKNUMBER());
    }

    std::uint32_t TagMap::getTotalTrackNumber() const {
        return getNumberTag(TOTALTRACKNUMBER());
    }

    bool TagMap::setTotalTrackNumber(std::uint32_t totalTrackNumber) {
        return setNumberTag(TOTALTRACKNUMBER(), totalTrackNumber);
    }



    SharedConstNumberAudioTag TagMap::getTrackNumberPointer() const {
        return getNumberTagPointer(TRACKNUMBER());
    }

    SharedNumberAudioTag TagMap::getTrackNumberPointer() {
        return getNumberTagPointer(TRACKNUMBER());
    }

    std::optional<std::uint32_t> TagMap::getTrackNumberOptional() const {
        return getNumberTagOptional(TRACKNUMBER());
    }

    std::uint32_t TagMap::getTrackNumber() const {
        return getNumberTag(TRACKNUMBER());
    }

    bool TagMap::setTrackNumber(std::uint32_t trackNumber) {
        return setNumberTag(TRACKNUMBER(), trackNumber);
    }



    std::uint32_t TagMap::getYear() const {
        return getDateTag(DATE()).getYear();
    }

    bool TagMap::setYear(std::uint32_t year) {
        return setDateTag(DATE(), types::Date(year));
    }



    std::uint32_t TagMap::getOriginalYear() const {
        return getDateTag(ORIGINALDATE()).getYear();
    }

    bool TagMap::setOriginalYear(std::uint32_t originalYear) {
        return setDateTag(ORIGINALDATE(), types::Date(originalYear));
    }



    SharedConstDateAudioTag TagMap::getDatePointer() const {
        return getDateTagPointer(DATE());
    }

    SharedDateAudioTag TagMap::getDatePointer() {
        return getDateTagPointer(DATE());
    }

    std::optional<types::Date> TagMap::getDateOptional() const {
        return getDateTagOptional(DATE());
    }

    types::Date TagMap::getDate() const {
        return getDateTag(DATE());
    }

    bool TagMap::setDate(const types::Date& date) {
        return setDateTag(DATE(), date);
    }



    SharedConstDateAudioTag TagMap::getEncodingDatePointer() const {
        return getDateTagPointer(ENCODINGDATE());
    }

    SharedDateAudioTag TagMap::getEncodingDatePointer() {
        return getDateTagPointer(ENCODINGDATE());
    }

    std::optional<types::Date> TagMap::getEncodingDateOptional() const {
        return getDateTagOptional(ENCODINGDATE());
    }

    types::Date TagMap::getEncodingDate() const {
        return getDateTag(ENCODINGDATE());
    }

    bool TagMap::setEncodingDate(const types::Date& encodingDate) {
        return setDateTag(ENCODINGDATE(), encodingDate);
    }



    SharedConstDateAudioTag TagMap::getOriginalDatePointer() const {
        return getDateTagPointer(ORIGINALDATE());
    }

    SharedDateAudioTag TagMap::getOriginalDatePointer() {
        return getDateTagPointer(ORIGINALDATE());
    }

    std::optional<types::Date> TagMap::getOriginalDateOptional() const {
        return getDateTagOptional(ORIGINALDATE());
    }

    types::Date TagMap::getOriginalDate() const {
        return getDateTag(ORIGINALDATE());
    }

    bool TagMap::setOriginalDate(const types::Date& originalDate) {
        return setDateTag(ORIGINALDATE(), originalDate);
    }



    SharedConstLyricsAudioTag TagMap::getLyricsEngPointer() const {
        return getLyricsTagPointer(LYRICSENG());
    }

    SharedLyricsAudioTag TagMap::getLyricsEngPointer() {
        return getLyricsTagPointer(LYRICSENG());
    }

    std::optional<types::Lyrics> TagMap::getLyricsEngOptional() const {
        return getLyricsTagOptional(LYRICSENG());
    }

    types::Lyrics TagMap::getLyricsEng() const {
        return getLyricsTag(LYRICSENG());
    }

    bool TagMap::setLyricsEng(const types::Lyrics& lyricsEng) {
        return setLyricsTag(LYRICSENG(), lyricsEng);
    }



    SharedConstImageAudioTag TagMap::getImageOtherPointer() const {
        return getImageTagPointer(IMAGEOTHER());
    }

    SharedImageAudioTag TagMap::getImageOtherPointer() {
        return getImageTagPointer(IMAGEOTHER());
    }

    std::optional<types::Image> TagMap::getImageOtherOptional() const {
        return getImageTagOptional(IMAGEOTHER());
    }

    types::Image TagMap::getImageOther() const {
        return getImageTag(IMAGEOTHER());
    }

    bool TagMap::setImageOther(const types::Image& imageOther) {
        return setImageTag(IMAGEOTHER(), imageOther);
    }

    bool TagMap::setImageOther(types::Image&& imageOther) {
        return setImageTag(IMAGEOTHER(), std::move(imageOther));
    }



    SharedConstImageAudioTag TagMap::getImageIConPointer() const {
        return getImageTagPointer(IMAGEICON());
    }

    SharedImageAudioTag TagMap::getImageIConPointer() {
        return getImageTagPointer(IMAGEICON());
    }

    std::optional<types::Image> TagMap::getImageIConOptional() const {
        return getImageTagOptional(IMAGEICON());
    }

    types::Image TagMap::getImageICon() const {
        return getImageTag(IMAGEICON());
    }

    bool TagMap::setImageICon(const types::Image& imageICon) {
        return setImageTag(IMAGEICON(), imageICon);
    }

    bool TagMap::setImageICon(types::Image&& imageICon) {
        return setImageTag(IMAGEICON(), std::move(imageICon));
    }



    SharedConstImageAudioTag TagMap::getImageOtherIconPointer() const {
        return getImageTagPointer(IMAGEOTHERICON());
    }

    SharedImageAudioTag TagMap::getImageOtherIconPointer() {
        return getImageTagPointer(IMAGEOTHERICON());
    }

    std::optional<types::Image> TagMap::getImageOtherIconOptional() const {
        return getImageTagOptional(IMAGEOTHERICON());
    }

    types::Image TagMap::getImageOtherIcon() const {
        return getImageTag(IMAGEOTHERICON());
    }

    bool TagMap::setImageOtherIcon(const types::Image& imageOtherIcon) {
        return setImageTag(IMAGEOTHERICON(), imageOtherIcon);
    }

    bool TagMap::setImageOtherIcon(types::Image&& imageOtherIcon) {
        return setImageTag(IMAGEOTHERICON(), std::move(imageOtherIcon));
    }



    SharedConstImageAudioTag TagMap::getImageCoverFrontPointer() const {
        return getImageTagPointer(IMAGECOVERFRONT());
    }

    SharedImageAudioTag TagMap::getImageCoverFrontPointer() {
        return getImageTagPointer(IMAGECOVERFRONT());
    }

    std::optional<types::Image> TagMap::getImageCoverFrontOptional() const {
        return getImageTagOptional(IMAGECOVERFRONT());
    }

    types::Image TagMap::getImageCoverFront() const {
        return getImageTag(IMAGECOVERFRONT());
    }

    bool TagMap::setImageCoverFront(const types::Image& imageCoverFront) {
        return setImageTag(IMAGECOVERFRONT(), imageCoverFront);
    }

    bool TagMap::setImageCoverFront(types::Image&& imageCoverFront) {
        return setImageTag(IMAGECOVERFRONT(), std::move(imageCoverFront));
    }



    SharedConstImageAudioTag TagMap::getImageCoverBackPointer() const {
        return getImageTagPointer(IMAGECOVERBACK());
    }

    SharedImageAudioTag TagMap::getImageCoverBackPointer() {
        return getImageTagPointer(IMAGECOVERBACK());
    }

    std::optional<types::Image> TagMap::getImageCoverBackOptional() const {
        return getImageTagOptional(IMAGECOVERBACK());
    }

    types::Image TagMap::getImageCoverBack() const {
        return getImageTag(IMAGECOVERBACK());
    }

    bool TagMap::setImageCoverBack(const types::Image& imageCoverBack) {
        return setImageTag(IMAGECOVERBACK(), imageCoverBack);
    }

    bool TagMap::setImageCoverBack(types::Image&& imageCoverBack) {
        return setImageTag(IMAGECOVERBACK(), std::move(imageCoverBack));
    }



    SharedConstImageAudioTag TagMap::getImageLeafletPointer() const {
        return getImageTagPointer(IMAGELEAFLET());
    }

    SharedImageAudioTag TagMap::getImageLeafletPointer() {
        return getImageTagPointer(IMAGELEAFLET());
    }

    std::optional<types::Image> TagMap::getImageLeafletOptional() const {
        return getImageTagOptional(IMAGELEAFLET());
    }

    types::Image TagMap::getImageLeaflet() const {
        return getImageTag(IMAGELEAFLET());
    }

    bool TagMap::setImageLeaflet(const types::Image& imageLeaflet) {
        return setImageTag(IMAGELEAFLET(), imageLeaflet);
    }

    bool TagMap::setImageLeaflet(types::Image&& imageLeaflet) {
        return setImageTag(IMAGELEAFLET(), std::move(imageLeaflet));
    }



    SharedConstImageAudioTag TagMap::getImageMediaPointer() const {
        return getImageTagPointer(IMAGEMEDIA());
    }

    SharedImageAudioTag TagMap::getImageMediaPointer() {
        return getImageTagPointer(IMAGEMEDIA());
    }

    std::optional<types::Image> TagMap::getImageMediaOptional() const {
        return getImageTagOptional(IMAGEMEDIA());
    }

    types::Image TagMap::getImageMedia() const {
        return getImageTag(IMAGEMEDIA());
    }

    bool TagMap::setImageMedia(const types::Image& imageMedia) {
        return setImageTag(IMAGEMEDIA(), imageMedia);
    }

    bool TagMap::setImageMedia(types::Image&& imageMedia) {
        return setImageTag(IMAGEMEDIA(), std::move(imageMedia));
    }



    SharedConstImageAudioTag TagMap::getImageLeadArtistPointer() const {
        return getImageTagPointer(IMAGELEADARTIST());
    }

    SharedImageAudioTag TagMap::getImageLeadArtistPointer() {
        return getImageTagPointer(IMAGELEADARTIST());
    }

    std::optional<types::Image> TagMap::getImageLeadArtistOptional() const {
        return getImageTagOptional(IMAGELEADARTIST());
    }

    types::Image TagMap::getImageLeadArtist() const {
        return getImageTag(IMAGELEADARTIST());
    }

    bool TagMap::setImageLeadArtist(const types::Image& imageLeadArtist) {
        return setImageTag(IMAGELEADARTIST(), imageLeadArtist);
    }

    bool TagMap::setImageLeadArtist(types::Image&& imageLeadArtist) {
        return setImageTag(IMAGELEADARTIST(), std::move(imageLeadArtist));
    }



    SharedConstImageAudioTag TagMap::getImageArtistPointer() const {
        return getImageTagPointer(IMAGEARTIST());
    }

    SharedImageAudioTag TagMap::getImageArtistPointer() {
        return getImageTagPointer(IMAGEARTIST());
    }

    std::optional<types::Image> TagMap::getImageArtistOptional() const {
        return getImageTagOptional(IMAGEARTIST());
    }

    types::Image TagMap::getImageArtist() const {
        return getImageTag(IMAGEARTIST());
    }

    bool TagMap::setImageArtist(const types::Image& imageArtist) {
        return setImageTag(IMAGEARTIST(), imageArtist);
    }

    bool TagMap::setImageArtist(types::Image&& imageArtist) {
        return setImageTag(IMAGEARTIST(), std::move(imageArtist));
    }



    SharedConstImageAudioTag TagMap::getImageConductorPointer() const {
        return getImageTagPointer(IMAGECONDUCTOR());
    }

    SharedImageAudioTag TagMap::getImageConductorPointer() {
        return getImageTagPointer(IMAGECONDUCTOR());
    }

    std::optional<types::Image> TagMap::getImageConductorOptional() const {
        return getImageTagOptional(IMAGECONDUCTOR());
    }

    types::Image TagMap::getImageConductor() const {
        return getImageTag(IMAGECONDUCTOR());
    }

    bool TagMap::setImageConductor(const types::Image& imageConductor) {
        return setImageTag(IMAGECONDUCTOR(), imageConductor);
    }

    bool TagMap::setImageConductor(types::Image&& imageConductor) {
        return setImageTag(IMAGECONDUCTOR(), std::move(imageConductor));
    }



    SharedConstImageAudioTag TagMap::getImageBandPointer() const {
        return getImageTagPointer(IMAGEBAND());
    }

    SharedImageAudioTag TagMap::getImageBandPointer() {
        return getImageTagPointer(IMAGEBAND());
    }

    std::optional<types::Image> TagMap::getImageBandOptional() const {
        return getImageTagOptional(IMAGEBAND());
    }

    types::Image TagMap::getImageBand() const {
        return getImageTag(IMAGEBAND());
    }

    bool TagMap::setImageBand(const types::Image& imageBand) {
        return setImageTag(IMAGEBAND(), imageBand);
    }

    bool TagMap::setImageBand(types::Image&& imageBand) {
        return setImageTag(IMAGEBAND(), std::move(imageBand));
    }



    SharedConstImageAudioTag TagMap::getImageComposerPointer() const {
        return getImageTagPointer(IMAGECOMPOSER());
    }

    SharedImageAudioTag TagMap::getImageComposerPointer() {
        return getImageTagPointer(IMAGECOMPOSER());
    }

    std::optional<types::Image> TagMap::getImageComposerOptional() const {
        return getImageTagOptional(IMAGECOMPOSER());
    }

    types::Image TagMap::getImageComposer() const {
        return getImageTag(IMAGECOMPOSER());
    }

    bool TagMap::setImageComposer(const types::Image& imageComposer) {
        return setImageTag(IMAGECOMPOSER(), imageComposer);
    }

    bool TagMap::setImageComposer(types::Image&& imageComposer) {
        return setImageTag(IMAGECOMPOSER(), std::move(imageComposer));
    }



    SharedConstImageAudioTag TagMap::getImageLyricistPointer() const {
        return getImageTagPointer(IMAGELYRICIST());
    }

    SharedImageAudioTag TagMap::getImageLyricistPointer() {
        return getImageTagPointer(IMAGELYRICIST());
    }

    std::optional<types::Image> TagMap::getImageLyricistOptional() const {
        return getImageTagOptional(IMAGELYRICIST());
    }

    types::Image TagMap::getImageLyricist() const {
        return getImageTag(IMAGELYRICIST());
    }

    bool TagMap::setImageLyricist(const types::Image& imageLyricist) {
        return setImageTag(IMAGELYRICIST(), imageLyricist);
    }

    bool TagMap::setImageLyricist(types::Image&& imageLyricist) {
        return setImageTag(IMAGELYRICIST(), std::move(imageLyricist));
    }



    SharedConstImageAudioTag TagMap::getImageRecordingLocationPointer() const {
        return getImageTagPointer(IMAGERECORDINGLOCATION());
    }

    SharedImageAudioTag TagMap::getImageRecordingLocationPointer() {
        return getImageTagPointer(IMAGERECORDINGLOCATION());
    }

    std::optional<types::Image> TagMap::getImageRecordingLocationOptional() const {
        return getImageTagOptional(IMAGERECORDINGLOCATION());
    }

    types::Image TagMap::getImageRecordingLocation() const {
        return getImageTag(IMAGERECORDINGLOCATION());
    }

    bool TagMap::setImageRecordingLocation(const types::Image& imageRecordingLocation) {
        return setImageTag(IMAGERECORDINGLOCATION(), imageRecordingLocation);
    }

    bool TagMap::setImageRecordingLocation(types::Image&& imageRecordingLocation) {
        return setImageTag(IMAGERECORDINGLOCATION(), std::move(imageRecordingLocation));
    }



    SharedConstImageAudioTag TagMap::getImageDuringRecordingPointer() const {
        return getImageTagPointer(IMAGEDURINGRECORDING());
    }

    SharedImageAudioTag TagMap::getImageDuringRecordingPointer() {
        return getImageTagPointer(IMAGEDURINGRECORDING());
    }

    std::optional<types::Image> TagMap::getImageDuringRecordingOptional() const {
        return getImageTagOptional(IMAGEDURINGRECORDING());
    }

    types::Image TagMap::getImageDuringRecording() const {
        return getImageTag(IMAGEDURINGRECORDING());
    }

    bool TagMap::setImageDuringRecording(const types::Image& imageDuringRecording) {
        return setImageTag(IMAGEDURINGRECORDING(), imageDuringRecording);
    }

    bool TagMap::setImageDuringRecording(types::Image&& imageDuringRecording) {
        return setImageTag(IMAGEDURINGRECORDING(), std::move(imageDuringRecording));
    }



    SharedConstImageAudioTag TagMap::getImageDuringPerformancePointer() const {
        return getImageTagPointer(IMAGEDURINGPERFORMANCE());
    }

    SharedImageAudioTag TagMap::getImageDuringPerformancePointer() {
        return getImageTagPointer(IMAGEDURINGPERFORMANCE());
    }

    std::optional<types::Image> TagMap::getImageDuringPerformanceOptional() const {
        return getImageTagOptional(IMAGEDURINGPERFORMANCE());
    }

    types::Image TagMap::getImageDuringPerformance() const {
        return getImageTag(IMAGEDURINGPERFORMANCE());
    }

    bool TagMap::setImageDuringPerformance(const types::Image& imageDuringPerformance) {
        return setImageTag(IMAGEDURINGPERFORMANCE(), imageDuringPerformance);
    }

    bool TagMap::setImageDuringPerformance(types::Image&& imageDuringPerformance) {
        return setImageTag(IMAGEDURINGPERFORMANCE(), std::move(imageDuringPerformance));
    }



    SharedConstImageAudioTag TagMap::getImageVideoCapturePointer() const {
        return getImageTagPointer(IMAGEVIDEOCAPTURE());
    }

    SharedImageAudioTag TagMap::getImageVideoCapturePointer() {
        return getImageTagPointer(IMAGEVIDEOCAPTURE());
    }

    std::optional<types::Image> TagMap::getImageVideoCaptureOptional() const {
        return getImageTagOptional(IMAGEVIDEOCAPTURE());
    }

    types::Image TagMap::getImageVideoCapture() const {
        return getImageTag(IMAGEVIDEOCAPTURE());
    }

    bool TagMap::setImageVideoCapture(const types::Image& imageVideoCapture) {
        return setImageTag(IMAGEVIDEOCAPTURE(), imageVideoCapture);
    }

    bool TagMap::setImageVideoCapture(types::Image&& imageVideoCapture) {
        return setImageTag(IMAGEVIDEOCAPTURE(), std::move(imageVideoCapture));
    }



    SharedConstImageAudioTag TagMap::getImageABrightColouredFishPointer() const {
        return getImageTagPointer(IMAGEABRIGHTCOLOUREDFISH());
    }

    SharedImageAudioTag TagMap::getImageABrightColouredFishPointer() {
        return getImageTagPointer(IMAGEABRIGHTCOLOUREDFISH());
    }

    std::optional<types::Image> TagMap::getImageABrightColouredFishOptional() const {
        return getImageTagOptional(IMAGEABRIGHTCOLOUREDFISH());
    }

    types::Image TagMap::getImageABrightColouredFish() const {
        return getImageTag(IMAGEABRIGHTCOLOUREDFISH());
    }

    bool TagMap::setImageABrightColouredFish(const types::Image& imageABrightColouredFish) {
        return setImageTag(IMAGEABRIGHTCOLOUREDFISH(), imageABrightColouredFish);
    }

    bool TagMap::setImageABrightColouredFish(types::Image&& imageABrightColouredFish) {
        return setImageTag(IMAGEABRIGHTCOLOUREDFISH(), std::move(imageABrightColouredFish));
    }



    SharedConstImageAudioTag TagMap::getImageIllustrationPointer() const {
        return getImageTagPointer(IMAGEILLUSTRATION());
    }

    SharedImageAudioTag TagMap::getImageIllustrationPointer() {
        return getImageTagPointer(IMAGEILLUSTRATION());
    }

    std::optional<types::Image> TagMap::getImageIllustrationOptional() const {
        return getImageTagOptional(IMAGEILLUSTRATION());
    }

    types::Image TagMap::getImageIllustration() const {
        return getImageTag(IMAGEILLUSTRATION());
    }

    bool TagMap::setImageIllustration(const types::Image& imageIllustration) {
        return setImageTag(IMAGEILLUSTRATION(), imageIllustration);
    }

    bool TagMap::setImageIllustration(types::Image&& imageIllustration) {
        return setImageTag(IMAGEILLUSTRATION(), std::move(imageIllustration));
    }



    SharedConstImageAudioTag TagMap::getImageBandLogoPointer() const {
        return getImageTagPointer(IMAGEBANDLOGO());
    }

    SharedImageAudioTag TagMap::getImageBandLogoPointer() {
        return getImageTagPointer(IMAGEBANDLOGO());
    }

    std::optional<types::Image> TagMap::getImageBandLogoOptional() const {
        return getImageTagOptional(IMAGEBANDLOGO());
    }

    types::Image TagMap::getImageBandLogo() const {
        return getImageTag(IMAGEBANDLOGO());
    }

    bool TagMap::setImageBandLogo(const types::Image& imageBandLogo) {
        return setImageTag(IMAGEBANDLOGO(), imageBandLogo);
    }

    bool TagMap::setImageBandLogo(types::Image&& imageBandLogo) {
        return setImageTag(IMAGEBANDLOGO(), std::move(imageBandLogo));
    }



    SharedConstImageAudioTag TagMap::getImagePublisherLogoPointer() const {
        return getImageTagPointer(IMAGEPUBLISHERLOGO());
    }

    SharedImageAudioTag TagMap::getImagePublisherLogoPointer() {
        return getImageTagPointer(IMAGEPUBLISHERLOGO());
    }

    std::optional<types::Image> TagMap::getImagePublisherLogoOptional() const {
        return getImageTagOptional(IMAGEPUBLISHERLOGO());
    }

    types::Image TagMap::getImagePublisherLogo() const {
        return getImageTag(IMAGEPUBLISHERLOGO());
    }

    bool TagMap::setImagePublisherLogo(const types::Image& imagePublisherLogo) {
        return setImageTag(IMAGEPUBLISHERLOGO(), imagePublisherLogo);
    }

    bool TagMap::setImagePublisherLogo(types::Image&& imagePublisherLogo) {
        return setImageTag(IMAGEPUBLISHERLOGO(), std::move(imagePublisherLogo));
    }



    SharedConstISRCAudioTag TagMap::getISRCPointer() const {
        return getISRCTagPointer(ISRC());
    }

    SharedISRCAudioTag TagMap::getISRCPointer() {
        return getISRCTagPointer(ISRC());
    }

    std::optional<types::ISRC> TagMap::getISRCOptional() const {
        return getISRCTagOptional(ISRC());
    }

    types::ISRC TagMap::getISRC() const {
        return getISRCTag(ISRC());
    }

    bool TagMap::setISRC(const types::ISRC& iSRC) {
        return setISRCTag(ISRC(), iSRC);
    }



    SharedConstBarcodeAudioTag TagMap::getBarcodePointer() const {
        return getBarcodeTagPointer(BARCODE());
    }

    SharedBarcodeAudioTag TagMap::getBarcodePointer() {
        return getBarcodeTagPointer(BARCODE());
    }

    std::optional<types::Barcode> TagMap::getBarcodeOptional() const {
        return getBarcodeTagOptional(BARCODE());
    }

    types::Barcode TagMap::getBarcode() const {
        return getBarcodeTag(BARCODE());
    }

    bool TagMap::setBarcode(const types::Barcode& barcode) {
        return setBarcodeTag(BARCODE(), barcode);
    }







    const TagMap::SetType TagMap::TAG_NAMES = {
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

    const TagMap::SetType TagMap::STRING_TAG_NAMES = {
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

    const TagMap::SetType TagMap::NUMBER_TAG_NAMES = {
        BPM(),
        DISCNUMBER(),
        TOTALDISCNUMBER(),
        TOTALTRACKNUMBER(),
        TRACKNUMBER()
    };

    const TagMap::SetType TagMap::DATE_TAG_NAMES = {
        DATE(),
        ENCODINGDATE(),
        ORIGINALDATE()
    };

	const TagMap::SetType TagMap::IMAGE_TAG_NAMES = {
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


    bool TagMap::const_iterator::operator==(const const_iterator & other) const {
        return internalIterator == other.internalIterator;
    }

    bool TagMap::const_iterator::operator!=(const const_iterator & other) const {
        return internalIterator != other.internalIterator;
    }



    TagMap::const_iterator & TagMap::const_iterator::operator++() {
        ++internalIterator;
        return *this;
    }

    TagMap::const_iterator TagMap::const_iterator::operator++(int) {
        auto old = *this;
        ++internalIterator;
        return old;
    }

    TagMap::const_iterator & TagMap::const_iterator::operator--() {
        --internalIterator;
        return *this;
    }

    TagMap::const_iterator TagMap::const_iterator::operator--(int) {
        auto old = *this;
        --internalIterator;
        return old;
    }



    const TagMap::const_iterator::pointer TagMap::const_iterator::operator->() const {
        return &operator*();
    }

    const TagMap::const_iterator::reference TagMap::const_iterator::operator*() const {
        returned = internalIterator.operator * ().second;
        return returned;
    }



    Tag::Type TagMap::const_iterator::getType() const {
        return internalIterator->second->getType();
    }


    TagMap::const_iterator::const_iterator(const internal_iterator & internalIterator)
        : internalIterator(internalIterator) {}







    TagMap::iterator & TagMap::iterator::operator++() {
        const_iterator::operator++();
        return *this;
    }

    TagMap::iterator TagMap::iterator::operator++(int) {
        auto old = *this;
        const_iterator::operator++();
        return old;
    }

    TagMap::iterator & TagMap::iterator::operator--() {
        const_iterator::operator--();
        return *this;
    }

    TagMap::iterator TagMap::iterator::operator--(int) {
        auto old = *this;
        const_iterator::operator--();
        return old;
    }

    TagMap::iterator::pointer TagMap::iterator::operator->() {
        return &internalIterator.operator * ().second;
    }

    TagMap::iterator::reference TagMap::iterator::operator*() {
        return internalIterator.operator * ().second;
    }
}
