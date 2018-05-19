#include "AudioTagMap.hpp"

namespace tag {

	const std::string AudioTagMap::ALBUM =  "ALBUM"s;
	const std::string AudioTagMap::ALBUMARTIST = "ALBUMARTIST"s;
	const std::string AudioTagMap::ARTIST = "ARTIST"s;
	const std::string AudioTagMap::BPM = "BPM"s;
	const std::string AudioTagMap::COMMENT = "COMMENT"s;
	const std::string AudioTagMap::COMPOSER = "COMPOSER"s;
	const std::string AudioTagMap::CONDUCTOR = "CONDUCTOR"s;
	const std::string AudioTagMap::DATE = "DATE"s;
	const std::string AudioTagMap::DISCNUMBER = "DISCNUMBER"s;
	const std::string AudioTagMap::GENRE = "GENRE"s;

	const std::string AudioTagMap::IMAGEOTHER = "IMAGEOTHER"s;
	const std::string AudioTagMap::IMAGEICON = "IMAGEICON"s;
	const std::string AudioTagMap::IMAGEOTHERICON = "IMAGEOTHERICON"s;
	const std::string AudioTagMap::IMAGECOVERFRONT = "IMAGECOVERFRONT"s;
	const std::string AudioTagMap::IMAGECOVERBACK = "IMAGECOVERBACK"s;
	const std::string AudioTagMap::IMAGELEAFLET = "IMAGELEAFLET"s;
	const std::string AudioTagMap::IMAGEMEDIA = "IMAGEMEDIA"s;
	const std::string AudioTagMap::IMAGEARTIST = "IMAGEARTIST"s;
	const std::string AudioTagMap::IMAGECONDUCTOR = "IMAGECONDUCTOR"s;
	const std::string AudioTagMap::IMAGEBAND = "IMAGEBAND"s;
	const std::string AudioTagMap::IMAGECOMPOSER = "IMAGECOMPOSER"s;
	const std::string AudioTagMap::IMAGELYRICIST = "IMAGELYRICIST"s;
	const std::string AudioTagMap::IMAGERECORDINGLOCATION = "IMAGERECORDINGLOCATION"s;
	const std::string AudioTagMap::IMAGEDURINGRECORDING = "IMAGEDURINGRECORDING"s;
	const std::string AudioTagMap::IMAGEDURINGPERFORMANCE = "IMAGEDURINGPERFORMANCE"s;
	const std::string AudioTagMap::IMAGEVIDEOCAPTURE = "IMAGEVIDEOCAPTURE"s;
	const std::string AudioTagMap::IMAGEABRIGHTCOLOUREDFISH = "IMAGEABRIGHTCOLOUREDFISH"s;
	const std::string AudioTagMap::IMAGEILLUSTRATION = "IMAGEILLUSTRATION"s;
	const std::string AudioTagMap::IMAGEBANDLOGO = "IMAGEBANDLOGO"s;
	const std::string AudioTagMap::IMAGEPUBLISHERLOGO = "IMAGEPUBLISHERLOGO"s;

	const std::string AudioTagMap::LYRICSENG = "LYRICSENG"s;

	const std::string AudioTagMap::LYRICYST = "LYRICYST"s;
	const std::string AudioTagMap::ORIGINALALBUM = "ORIGINALALBUM"s;
	const std::string AudioTagMap::ORIGINALARTIST = "ORIGINALARTIST"s;
	const std::string AudioTagMap::ORIGINALDATE = "ORIGINALDATE"s;
	const std::string AudioTagMap::PRODUCER = "PRODUCER"s;
	const std::string AudioTagMap::PUBLISHER = "PUBLISHER"s;
	const std::string AudioTagMap::SUBTITLE = "SUBTITLE"s;
	const std::string AudioTagMap::TITLE = "TITLE"s;
	const std::string AudioTagMap::TOTALDISCNUMBER = "TOTALDISCNUMBER"s;
	const std::string AudioTagMap::TOTALTRACKNUMBER = "TOTALTRACKNUMBER"s;
	const std::string AudioTagMap::TRACKNUMBER = "TRACKNUMBER"s;

	const std::string AudioTagMap::LYRICS = "LYRICS"s;


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




	void AudioTagMap::mergeWithOverwrite(AudioTagMap & source) {
		for (auto it = source.tagMap.begin(); it != source.tagMap.end(); ++it)
			tagMap.erase(it->first);
		tagMap.merge(source.tagMap);
	}

	void AudioTagMap::mergeWithOverwrite(AudioTagMap && source) {
		for (auto it = source.tagMap.begin(); it != source.tagMap.end(); ++it)
			tagMap.erase(it->first);
		tagMap.merge(source.tagMap);
	}





	void AudioTagMap::clear() {
		tagMap.clear();
	}




		

	bool AudioTagMap::removeTag(const std::string & name) {
		return removeTagImpl(name);
	}






	AudioTagMap::iterator AudioTagMap::getTagIterator(const std::string & name) {
		return iterator(tagMap.find(name));
	}

	AudioTagMap::const_iterator AudioTagMap::getTagIterator(const std::string & name) const {
		return iterator(const_cast<AudioTagMap*>(this)->tagMap.find(name));
	}

	SharedConstAudioTag AudioTagMap::getTag(const std::string & name) const {
		const_iterator it = getTagIterator(name);
		if (it != end())
			return *it;
		return SharedConstAudioTag();
	}

	SharedAudioTag AudioTagMap::getTag(const std::string & name) {
		iterator it = getTagIterator(name);
		if (it != end())
			return *it;
		return SharedAudioTag();
	}








	SharedStringAudioTag AudioTagMap::getStringTag(const std::string & name) {
		return getTypeTag<StringAudioTag>(name);
	}

	SharedConstStringAudioTag AudioTagMap::getStringTag(const std::string & name) const {
		return getTypeTag<StringAudioTag>(name);
	}

	bool AudioTagMap::setStringTag(const std::string & name, const std::string & text) {
		if (boost::starts_with(name, LYRICS))
			return false;
		bool defined = TAG_NAMES.find(name) != TAG_NAMES.end();
		bool stringDefined = STRING_TAG_NAMES.find(name) != STRING_TAG_NAMES.end();

		if (!stringDefined && defined)
			return false;
		SharedStringAudioTag tag = getStringTag(name);
		if (tag != nullptr)
			tag->setText(text);
		else
			tagMap.insert(std::make_pair(name, std::make_shared<StringAudioTag>(name, text)));
		return true;
	}





	SharedNumberAudioTag AudioTagMap::getNumberTag(const std::string & name) {
		return getTypeTag<NumberAudioTag>(name);
	}

	SharedConstNumberAudioTag AudioTagMap::getNumberTag(const std::string & name) const {
		return getTypeTag<NumberAudioTag>(name);
	}

	bool AudioTagMap::setNumberTag(const std::string & name, unsigned number) {
		if (boost::starts_with(name, LYRICS))
			return false;
		bool numberDefined = NUMBER_TAG_NAMES.find(name) != NUMBER_TAG_NAMES.end();
		if (!numberDefined)
			return false;
		SharedNumberAudioTag tag = getNumberTag(name);
		if (tag != nullptr)
			tag->setNumber(number);
		else
			tagMap.insert(std::make_pair(name, std::make_shared<NumberAudioTag>(name, number)));
		return true;
	}



	SharedDateAudioTag AudioTagMap::getDateTag(const std::string & name) {
		return getTypeTag<DateAudioTag>(name);
	}

	SharedConstDateAudioTag AudioTagMap::getDateTag(const std::string & name) const {
		return getTypeTag<DateAudioTag>(name);
	}

	bool AudioTagMap::setDateTag(const std::string & name, const type::Date &date) {
		if (boost::starts_with(name, LYRICS))
			return false;
		bool dateDefined = DATE_TAG_NAMES.find(name) != DATE_TAG_NAMES.end();
		if (!dateDefined)
			return false;
		SharedDateAudioTag tag = getDateTag(name);
		if (tag != nullptr)
			tag->setDate(date);
		else
			tagMap.insert(std::make_pair(name, std::make_shared<DateAudioTag>(name, date)));
		return true;
	}




	SharedLyricsAudioTag AudioTagMap::getLyricsTagByLang(std::string language) {
		boost::to_upper(language);
		return getTypeTag<LyricsAudioTag>(LYRICS + language);
	}

	SharedConstLyricsAudioTag AudioTagMap::getLyricsTagByLang(std::string language) const {
		boost::to_upper(language);
		return getTypeTag<LyricsAudioTag>(LYRICS + language);
	}

	SharedLyricsAudioTag AudioTagMap::getLyricsTag(const std::string & name) {
		return getTypeTag<LyricsAudioTag>(name);
	}

	SharedConstLyricsAudioTag AudioTagMap::getLyricsTag(const std::string & name) const {
		return getTypeTag<LyricsAudioTag>(name);
	}

	bool AudioTagMap::setLyricsTagByLang(const std::string & language, const type::Lyrics & lyrics) {
		if (language.empty())
			return false;
		std::string name = LYRICS + boost::to_upper_copy(language);
		SharedLyricsAudioTag tag = getLyricsTagByLang(name);
		if (tag != nullptr)
			tag->setLyrics(lyrics);
		else
			tagMap.insert(std::make_pair(name, std::make_shared<LyricsAudioTag>(language, lyrics)));
		return true;
	}



	SharedImageAudioTag AudioTagMap::getImageTag(const std::string & name) {
		return getTypeTag<ImageAudioTag>(name);

	}

	SharedImageAudioTag AudioTagMap::getImageTag(ImageAudioTag::ImageType imageType) {
		return getImageTag(string::toString(imageType));
	}

	SharedConstImageAudioTag AudioTagMap::getImageTag(const std::string & name) const {
		return getTypeTag<ImageAudioTag>(name);
	}

	SharedConstImageAudioTag AudioTagMap::getImageTag(ImageAudioTag::ImageType imageType) const {
		return getImageTag(string::toString(imageType));
	}

	bool AudioTagMap::setImageTag(const std::string & name, const type::Image & image) {
		if (boost::starts_with(name, LYRICS))
			return false;
		bool imageDefined = IMAGE_TAG_NAMES.find(name) != IMAGE_TAG_NAMES.end();
		if (!imageDefined)
			return false;
		SharedImageAudioTag tag = getImageTag(name);
		if (tag != nullptr)
			tag->setImage(image);
		else
			tagMap.insert(std::make_pair(name, std::make_shared<ImageAudioTag>(name, image)));
		return true;
	}

	bool AudioTagMap::setImageTag(const std::string & name, type::Image && image) {
		if (boost::starts_with(name, LYRICS))
			return false;
		bool imageDefined = IMAGE_TAG_NAMES.find(name) != IMAGE_TAG_NAMES.end();
		if (!imageDefined)
			return false;
		SharedImageAudioTag tag = getImageTag(name);
		if (tag != nullptr)
			tag->setImage(std::move(image));
		else
			tagMap.insert(std::make_pair(name, std::make_shared<ImageAudioTag>(name, std::move(image))));
		return true;
	}

	bool AudioTagMap::setImageTag(ImageAudioTag::ImageType imageType, const type::Image & image) {
		return setImageTag(string::toString(imageType), image);
	}

	bool AudioTagMap::setImageTag(ImageAudioTag::ImageType imageType, type::Image && image) {
		return setImageTag(string::toString(imageType), std::move(image));
	}







	bool AudioTagMap::setAlbum(const std::string & album) {
		return setStringTag(ALBUM, album);
	}

	bool AudioTagMap::setArtist(const std::string & artist) {
		return setStringTag(ARTIST, artist);
	}

	bool AudioTagMap::setComment(const std::string & comment) {
		return setStringTag(COMMENT, comment);
	}

	bool AudioTagMap::setGenre(const std::string & genre) {
		return setStringTag(GENRE, genre);
	}

	bool AudioTagMap::setTitle(const std::string & title) {
		return setStringTag(TITLE, title);
	}

	bool AudioTagMap::setTrackNumber(unsigned trackNumber) {
		return setNumberTag(TRACKNUMBER, trackNumber);
	}

	bool AudioTagMap::setYear(unsigned year) {
		return setDateTag(DATE, type::Date(year));
	}

	size_t AudioTagMap::size() const {
		return tagMap.size();
	}






	bool AudioTagMap::removeTagImpl(const std::string & name) {
		return tagMap.erase(name) > 0;
	}







	const AudioTagMap::SetType AudioTagMap::TAG_NAMES = {
		ALBUM,
		ALBUMARTIST,
		ARTIST,
		BPM,
		COMMENT,
		COMPOSER,
		CONDUCTOR,
		DATE,
		DISCNUMBER,
		GENRE,

		IMAGEOTHER,
		IMAGEICON,
		IMAGECOVERFRONT,
		IMAGECOVERBACK,
		IMAGELEAFLET,
		IMAGEMEDIA,
		IMAGEARTIST,
		IMAGECONDUCTOR,
		IMAGEBAND,
		IMAGECOMPOSER,
		IMAGELYRICIST,
		IMAGERECORDINGLOCATION,
		IMAGEDURINGRECORDING,
		IMAGEDURINGPERFORMANCE,
		IMAGEVIDEOCAPTURE,
		IMAGEABRIGHTCOLOUREDFISH,
		IMAGEILLUSTRATION,
		IMAGEBANDLOGO,
		IMAGEPUBLISHERLOGO,

		LYRICYST,
		ORIGINALALBUM,
		ORIGINALARTIST,
		ORIGINALDATE,
		PRODUCER,
		PUBLISHER,
		SUBTITLE,
		TITLE,
		TOTALDISCNUMBER,
		TOTALTRACKNUMBER,
		TRACKNUMBER
	};

	const AudioTagMap::SetType AudioTagMap::STRING_TAG_NAMES = {
		ALBUM,
		ALBUMARTIST,
		ARTIST,
		COMMENT,
		COMPOSER,
		CONDUCTOR,
		GENRE,
		LYRICYST,
		ORIGINALALBUM,
		ORIGINALARTIST,
		PRODUCER,
		PUBLISHER,
		SUBTITLE,
		TITLE
	};

	const AudioTagMap::SetType AudioTagMap::NUMBER_TAG_NAMES = {
		BPM,
		DISCNUMBER,
		TOTALDISCNUMBER,
		TOTALTRACKNUMBER,
		TRACKNUMBER
	};

	const AudioTagMap::SetType AudioTagMap::DATE_TAG_NAMES = {
		DATE,
		ORIGINALDATE
	};

	const AudioTagMap::SetType AudioTagMap::IMAGE_TAG_NAMES = {
		IMAGEOTHER,
		IMAGEICON,
		IMAGECOVERFRONT,
		IMAGECOVERBACK,
		IMAGELEAFLET,
		IMAGEMEDIA,
		IMAGEARTIST,
		IMAGECONDUCTOR,
		IMAGEBAND,
		IMAGECOMPOSER,
		IMAGELYRICIST,
		IMAGERECORDINGLOCATION,
		IMAGEDURINGRECORDING,
		IMAGEDURINGPERFORMANCE,
		IMAGEVIDEOCAPTURE,
		IMAGEABRIGHTCOLOUREDFISH,
		IMAGEILLUSTRATION,
		IMAGEBANDLOGO,
		IMAGEPUBLISHERLOGO
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
		returned = internalIterator.operator*().second;
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
		return &internalIterator.operator*().second;
	}

	AudioTagMap::iterator::reference AudioTagMap::iterator::operator*() {
		return internalIterator.operator*().second;
	}
}