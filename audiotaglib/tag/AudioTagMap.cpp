#include "AudioTagMap.hpp"

namespace tag {

	const std::string AudioTagMap::ALBUM =  "ALBUM"s;
	const std::string AudioTagMap::ALBUMSORT = "ALBUMSORT"s;
	const std::string AudioTagMap::ALBUMARTIST = "ALBUMARTIST"s;
	const std::string AudioTagMap::ARTIST = "ARTIST"s;
	const std::string AudioTagMap::ARTISTSORT = "ARTISTSORT"s;
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

	const std::string AudioTagMap::LYRICS = "LYRICS"s;

	const std::string AudioTagMap::LYRICSENG = "LYRICSENG"s;

	const std::string AudioTagMap::LYRICIST = "LYRICIST"s;
	const std::string AudioTagMap::ORIGINALALBUM = "ORIGINALALBUM"s;
	const std::string AudioTagMap::ORIGINALARTIST = "ORIGINALARTIST"s;
	const std::string AudioTagMap::ORIGINALDATE = "ORIGINALDATE"s;
	const std::string AudioTagMap::PRODUCER = "PRODUCER"s;
	const std::string AudioTagMap::PUBLISHER = "PUBLISHER"s;
	const std::string AudioTagMap::SUBTITLE = "SUBTITLE"s;
	const std::string AudioTagMap::TITLE = "TITLE"s;
	const std::string AudioTagMap::TITLESORT = "TITLESORT"s;
	const std::string AudioTagMap::TOTALDISCNUMBER = "TOTALDISCNUMBER"s;
	const std::string AudioTagMap::TOTALTRACKNUMBER = "TOTALTRACKNUMBER"s;
	const std::string AudioTagMap::TRACKNUMBER = "TRACKNUMBER"s;



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


	std::size_t AudioTagMap::size() const noexcept {
		return tagMap.size();
	}



		

	bool AudioTagMap::removeTag(const std::string & name) {
		return removeTagImpl(name);
	}






	AudioTagMap::iterator AudioTagMap::getTagIterator(const std::string_view & name) {
		return iterator(tagMap.find(name));
	}

	AudioTagMap::const_iterator AudioTagMap::getTagIterator(const std::string_view & name) const {
		return iterator(const_cast<AudioTagMap*>(this)->tagMap.find(name));
	}

	SharedConstAudioTag AudioTagMap::getTag(const std::string_view & name) const {
		const_iterator it = getTagIterator(name);
		if (it != end())
			return *it;
		return SharedConstAudioTag();
	}

	SharedAudioTag AudioTagMap::getTag(const std::string_view & name) {
		iterator it = getTagIterator(name);
		if (it != end())
			return *it;
		return SharedAudioTag();
	}








	SharedStringAudioTag AudioTagMap::getStringTag(const std::string_view & name) {
		return getTypeTag<StringAudioTag>(name);
	}

	SharedConstStringAudioTag AudioTagMap::getStringTag(const std::string_view & name) const {
		return getTypeTag<StringAudioTag>(name);
	}

	bool AudioTagMap::setStringTag(const std::string_view & name, const std::string & text) {
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
			tagMap.insert(std::make_pair(std::string(name), std::make_shared<StringAudioTag>(std::string(name), text)));
		return true;
	}





	SharedNumberAudioTag AudioTagMap::getNumberTag(const std::string_view & name) {
		return getTypeTag<NumberAudioTag>(name);
	}

	SharedConstNumberAudioTag AudioTagMap::getNumberTag(const std::string_view & name) const {
		return getTypeTag<NumberAudioTag>(name);
	}

	bool AudioTagMap::setNumberTag(const std::string_view & name, unsigned number) {
		if (boost::starts_with(name, LYRICS))
			return false;
		bool numberDefined = NUMBER_TAG_NAMES.find(name) != NUMBER_TAG_NAMES.end();
		if (!numberDefined)
			return false;
		SharedNumberAudioTag tag = getNumberTag(name);
		if (tag != nullptr)
			tag->setNumber(number);
		else
			tagMap.insert(std::make_pair(std::string(name), std::make_shared<NumberAudioTag>(std::string(name), number)));
		return true;
	}



	SharedDateAudioTag AudioTagMap::getDateTag(const std::string_view & name) {
		return getTypeTag<DateAudioTag>(name);
	}

	SharedConstDateAudioTag AudioTagMap::getDateTag(const std::string_view & name) const {
		return getTypeTag<DateAudioTag>(name);
	}

	bool AudioTagMap::setDateTag(const std::string_view & name, const type::Date &date) {
		if (boost::starts_with(name, LYRICS))
			return false;
		bool dateDefined = DATE_TAG_NAMES.find(name) != DATE_TAG_NAMES.end();
		if (!dateDefined)
			return false;
		SharedDateAudioTag tag = getDateTag(name);
		if (tag != nullptr)
			tag->setDate(date);
		else
			tagMap.insert(std::make_pair(std::string(name), std::make_shared<DateAudioTag>(std::string(name), date)));
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

	SharedLyricsAudioTag AudioTagMap::getLyricsTag(const std::string_view & name) {
		return getTypeTag<LyricsAudioTag>(name);
	}

	SharedConstLyricsAudioTag AudioTagMap::getLyricsTag(const std::string_view & name) const {
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



	SharedImageAudioTag AudioTagMap::getImageTag(const std::string_view & name) {
		return getTypeTag<ImageAudioTag>(name);

	}

	SharedImageAudioTag AudioTagMap::getImageTag(ImageAudioTag::ImageType imageType) {
		return getImageTag(string::toString(imageType));
	}

	SharedConstImageAudioTag AudioTagMap::getImageTag(const std::string_view & name) const {
		return getTypeTag<ImageAudioTag>(name);
	}

	SharedConstImageAudioTag AudioTagMap::getImageTag(ImageAudioTag::ImageType imageType) const {
		return getImageTag(string::toString(imageType));
	}

	bool AudioTagMap::setImageTag(const std::string_view & name, const type::Image & image) {
		if (boost::starts_with(name, LYRICS))
			return false;
		bool imageDefined = IMAGE_TAG_NAMES.find(name) != IMAGE_TAG_NAMES.end();
		if (!imageDefined)
			return false;
		SharedImageAudioTag tag = getImageTag(name);
		if (tag != nullptr)
			tag->setImage(image);
		else
			tagMap.insert(std::make_pair(std::string(name), std::make_shared<ImageAudioTag>(std::string(name), image)));
		return true;
	}

	bool AudioTagMap::setImageTag(const std::string_view & name, type::Image && image) {
		if (boost::starts_with(name, LYRICS))
			return false;
		bool imageDefined = IMAGE_TAG_NAMES.find(name) != IMAGE_TAG_NAMES.end();
		if (!imageDefined)
			return false;
		SharedImageAudioTag tag = getImageTag(name);
		if (tag != nullptr)
			tag->setImage(std::move(image));
		else
			tagMap.insert(std::make_pair(name, std::make_shared<ImageAudioTag>(std::string(name), std::move(image))));
		return true;
	}

	bool AudioTagMap::setImageTag(ImageAudioTag::ImageType imageType, const type::Image & image) {
		return setImageTag(string::toString(imageType), image);
	}

	bool AudioTagMap::setImageTag(ImageAudioTag::ImageType imageType, type::Image && image) {
		return setImageTag(string::toString(imageType), std::move(image));
	}















	SharedConstStringAudioTag AudioTagMap::getAlbum() const {
		return getStringTag(ALBUM);
	}

	SharedStringAudioTag AudioTagMap::getAlbum() {
		return getStringTag(ALBUM);
	}

	bool AudioTagMap::setAlbum(const std::string & album) {
		return setStringTag(ALBUM, album);
	}




	SharedConstStringAudioTag AudioTagMap::getAlbumArtist() const {
		return getStringTag(ALBUMARTIST);
	}

	SharedStringAudioTag AudioTagMap::getAlbumArtist() {
		return getStringTag(ALBUMARTIST);
	}

	bool AudioTagMap::setAlbumArtist(const std::string & albumArtist) {
		return setStringTag(ALBUMARTIST, albumArtist);
	}




	SharedConstStringAudioTag AudioTagMap::getAlbumSort() const {
		return getStringTag(ALBUMSORT);
	}

	SharedStringAudioTag AudioTagMap::getAlbumSort() {
		return getStringTag(ALBUMSORT);
	}

	bool AudioTagMap::setAlbumSort(const std::string & albumSort) {
		return setStringTag(ALBUMSORT, albumSort);
	}




	SharedConstStringAudioTag AudioTagMap::getArtist() const {
		return getStringTag(ARTIST);
	}

	SharedStringAudioTag AudioTagMap::getArtist() {
		return getStringTag(ARTIST);
	}

	bool AudioTagMap::setArtist(const std::string & artist) {
		return setStringTag(ARTIST, artist);
	}




	SharedConstStringAudioTag AudioTagMap::getArtistSort() const {
		return getStringTag(ARTISTSORT);
	}

	SharedStringAudioTag AudioTagMap::getArtistSort() {
		return getStringTag(ARTISTSORT);
	}

	bool AudioTagMap::setArtistSort(const std::string & artistSort) {
		return setStringTag(ARTISTSORT, artistSort);
	}




	SharedConstStringAudioTag AudioTagMap::getComment() const {
		return getStringTag(COMMENT);
	}

	SharedStringAudioTag AudioTagMap::getComment() {
		return getStringTag(COMMENT);
	}

	bool AudioTagMap::setComment(const std::string & comment) {
		return setStringTag(COMMENT, comment);
	}




	SharedConstStringAudioTag AudioTagMap::getComposer() const {
		return getStringTag(COMPOSER);
	}

	SharedStringAudioTag AudioTagMap::getComposer() {
		return getStringTag(COMPOSER);
	}

	bool AudioTagMap::setComposer(const std::string & composer) {
		return setStringTag(COMPOSER, composer);
	}




	SharedConstStringAudioTag AudioTagMap::getConductor() const {
		return getStringTag(CONDUCTOR);
	}

	SharedStringAudioTag AudioTagMap::getConductor() {
		return getStringTag(CONDUCTOR);
	}

	bool AudioTagMap::setConductor(const std::string & conductor) {
		return setStringTag(CONDUCTOR, conductor);
	}




	SharedConstStringAudioTag AudioTagMap::getGenre() const {
		return getStringTag(GENRE);
	}

	SharedStringAudioTag AudioTagMap::getGenre() {
		return getStringTag(GENRE);
	}

	bool AudioTagMap::setGenre(const std::string & genre) {
		return setStringTag(GENRE, genre);
	}




	SharedConstStringAudioTag AudioTagMap::getLyricist() const {
		return getStringTag(LYRICIST);
	}

	SharedStringAudioTag AudioTagMap::getLyricist() {
		return getStringTag(LYRICIST);
	}

	bool AudioTagMap::setLyricist(const std::string & lyricist) {
		return setStringTag(LYRICIST, lyricist);
	}




	SharedConstStringAudioTag AudioTagMap::getOriginalAlbum() const {
		return getStringTag(ORIGINALALBUM);
	}

	SharedStringAudioTag AudioTagMap::getOriginalAlbum() {
		return getStringTag(ORIGINALALBUM);
	}

	bool AudioTagMap::setOriginalAlbum(const std::string & originalAlbum) {
		return setStringTag(ORIGINALALBUM, originalAlbum);
	}




	SharedConstStringAudioTag AudioTagMap::getOriginalArtist() const {
		return getStringTag(ORIGINALARTIST);
	}

	SharedStringAudioTag AudioTagMap::getOriginalArtist() {
		return getStringTag(ORIGINALARTIST);
	}

	bool AudioTagMap::setOriginalArtist(const std::string & originalArtist) {
		return setStringTag(ORIGINALARTIST, originalArtist);
	}




	SharedConstStringAudioTag AudioTagMap::getProducer() const {
		return getStringTag(PRODUCER);
	}

	SharedStringAudioTag AudioTagMap::getProducer() {
		return getStringTag(PRODUCER);
	}

	bool AudioTagMap::setProducer(const std::string & producer) {
		return setStringTag(PRODUCER, producer);
	}




	SharedConstStringAudioTag AudioTagMap::getPublisher() const {
		return getStringTag(PUBLISHER);
	}

	SharedStringAudioTag AudioTagMap::getPublisher() {
		return getStringTag(PUBLISHER);
	}

	bool AudioTagMap::setPublisher(const std::string & publisher) {
		return setStringTag(PUBLISHER, publisher);
	}




	SharedConstStringAudioTag AudioTagMap::getSubtitle() const {
		return getStringTag(SUBTITLE);
	}

	SharedStringAudioTag AudioTagMap::getSubtitle() {
		return getStringTag(SUBTITLE);
	}

	bool AudioTagMap::setSubtitle(const std::string & subtitle) {
		return setStringTag(SUBTITLE, subtitle);
	}




	SharedConstStringAudioTag AudioTagMap::getTitle() const {
		return getStringTag(TITLE);
	}

	SharedStringAudioTag AudioTagMap::getTitle() {
		return getStringTag(TITLE);
	}

	bool AudioTagMap::setTitle(const std::string & title) {
		return setStringTag(TITLE, title);
	}




	SharedConstStringAudioTag AudioTagMap::getTitleSort() const {
		return getStringTag(TITLESORT);
	}

	SharedStringAudioTag AudioTagMap::getTitleSort() {
		return getStringTag(TITLESORT);
	}

	bool AudioTagMap::setTitleSort(const std::string & titleSort) {
		return setStringTag(TITLESORT, titleSort);
	}



















	SharedConstNumberAudioTag AudioTagMap::getBpm() const {
		return getNumberTag(BPM);
	}

	SharedNumberAudioTag AudioTagMap::getBpm() {
		return getNumberTag(BPM);
	}

	bool AudioTagMap::setBpm(unsigned bpm) {
		return setNumberTag(BPM, bpm);
	}




	SharedConstNumberAudioTag AudioTagMap::getDiscNumber() const {
		return getNumberTag(DISCNUMBER);
	}

	SharedNumberAudioTag AudioTagMap::getDiscNumber() {
		return getNumberTag(DISCNUMBER);
	}

	bool AudioTagMap::setDiscNumber(unsigned discNumber) {
		return setNumberTag(DISCNUMBER, discNumber);
	}




	SharedConstNumberAudioTag AudioTagMap::getTotalDiscNumber() const {
		return getNumberTag(TOTALDISCNUMBER);
	}

	SharedNumberAudioTag AudioTagMap::getTotalDiscNumber() {
		return getNumberTag(TOTALDISCNUMBER);
	}

	bool AudioTagMap::setTotalDiscNumber(unsigned totalDiscNumber) {
		return setNumberTag(TOTALDISCNUMBER, totalDiscNumber);
	}




	SharedConstNumberAudioTag AudioTagMap::getTotalTrackNumber() const {
		return getNumberTag(TOTALTRACKNUMBER);
	}

	SharedNumberAudioTag AudioTagMap::getTotalTrackNumber() {
		return getNumberTag(TOTALTRACKNUMBER);
	}

	bool AudioTagMap::setTotalTrackNumber(unsigned totalTrackNumber) {
		return setNumberTag(TOTALTRACKNUMBER, totalTrackNumber);
	}




	SharedConstNumberAudioTag AudioTagMap::getTrackNumber() const {
		return getNumberTag(TRACKNUMBER);
	}

	SharedNumberAudioTag AudioTagMap::getTrackNumber() {
		return getNumberTag(TRACKNUMBER);
	}

	bool AudioTagMap::setTrackNumber(unsigned trackNumber) {
		return setNumberTag(TRACKNUMBER, trackNumber);
	}













	SharedConstDateAudioTag AudioTagMap::getDate() const {
		return getDateTag(DATE);
	}

	SharedDateAudioTag AudioTagMap::getDate() {
		return getDateTag(DATE);
	}

	bool AudioTagMap::setDate(const type::Date & date) {
		return setDateTag(DATE, date);
	}




	SharedConstDateAudioTag AudioTagMap::getOriginalDate() const {
		return getDateTag(ORIGINALDATE);
	}

	SharedDateAudioTag AudioTagMap::getOriginalDate() {
		return getDateTag(ORIGINALDATE);
	}

	bool AudioTagMap::setOriginalDate(const type::Date & originalDate) {
		return setDateTag(ORIGINALDATE, originalDate);
	}

















	SharedConstImageAudioTag AudioTagMap::getImageOther() const {
		return getImageTag(IMAGEOTHER);
	}

	SharedImageAudioTag AudioTagMap::getImageOther() {
		return getImageTag(IMAGEOTHER);
	}

	bool AudioTagMap::setImageOther(const type::Image & imageOther) {
		return setImageTag(IMAGEOTHER, imageOther);
	}

	bool AudioTagMap::setImageOther(type::Image && imageOther) {
		return setImageTag(IMAGEOTHER, std::move(imageOther));
	}




	SharedConstImageAudioTag AudioTagMap::getImageIcon() const {
		return getImageTag(IMAGEICON);
	}

	SharedImageAudioTag AudioTagMap::getImageIcon() {
		return getImageTag(IMAGEICON);
	}

	bool AudioTagMap::setImageIcon(const type::Image & imageIcon) {
		return setImageTag(IMAGEICON, imageIcon);
	}

	bool AudioTagMap::setImageIcon(type::Image && imageIcon) {
		return setImageTag(IMAGEICON, std::move(imageIcon));
	}




	SharedConstImageAudioTag AudioTagMap::getImageCoverFront() const {
		return getImageTag(IMAGECOVERFRONT);
	}

	SharedImageAudioTag AudioTagMap::getImageCoverFront() {
		return getImageTag(IMAGECOVERFRONT);
	}

	bool AudioTagMap::setImageCoverFront(const type::Image & imageCoverFront) {
		return setImageTag(IMAGECOVERFRONT, imageCoverFront);
	}

	bool AudioTagMap::setImageCoverFront(type::Image && imageCoverFront) {
		return setImageTag(IMAGECOVERFRONT, std::move(imageCoverFront));
	}




	SharedConstImageAudioTag AudioTagMap::getImageCoverBack() const {
		return getImageTag(IMAGECOVERBACK);
	}

	SharedImageAudioTag AudioTagMap::getImageCoverBack() {
		return getImageTag(IMAGECOVERBACK);
	}

	bool AudioTagMap::setImageCoverBack(const type::Image & imageCoverBack) {
		return setImageTag(IMAGECOVERBACK, imageCoverBack);
	}

	bool AudioTagMap::setImageCoverBack(type::Image && imageCoverBack) {
		return setImageTag(IMAGECOVERBACK, std::move(imageCoverBack));
	}




	SharedConstImageAudioTag AudioTagMap::getImageLeaflet() const {
		return getImageTag(IMAGELEAFLET);
	}

	SharedImageAudioTag AudioTagMap::getImageLeaflet() {
		return getImageTag(IMAGELEAFLET);
	}

	bool AudioTagMap::setImageLeaflet(const type::Image & imageLeaflet) {
		return setImageTag(IMAGELEAFLET, imageLeaflet);
	}

	bool AudioTagMap::setImageLeaflet(type::Image && imageLeaflet) {
		return setImageTag(IMAGELEAFLET, std::move(imageLeaflet));
	}




	SharedConstImageAudioTag AudioTagMap::getImageMedia() const {
		return getImageTag(IMAGEMEDIA);
	}

	SharedImageAudioTag AudioTagMap::getImageMedia() {
		return getImageTag(IMAGEMEDIA);
	}

	bool AudioTagMap::setImageMedia(const type::Image & imageMedia) {
		return setImageTag(IMAGEMEDIA, imageMedia);
	}

	bool AudioTagMap::setImageMedia(type::Image && imageMedia) {
		return setImageTag(IMAGEMEDIA, std::move(imageMedia));
	}




	SharedConstImageAudioTag AudioTagMap::getImageArtist() const {
		return getImageTag(IMAGEARTIST);
	}

	SharedImageAudioTag AudioTagMap::getImageArtist() {
		return getImageTag(IMAGEARTIST);
	}

	bool AudioTagMap::setImageArtist(const type::Image & imageArtist) {
		return setImageTag(IMAGEARTIST, imageArtist);
	}

	bool AudioTagMap::setImageArtist(type::Image && imageArtist) {
		return setImageTag(IMAGEARTIST, std::move(imageArtist));
	}




	SharedConstImageAudioTag AudioTagMap::getImageConductor() const {
		return getImageTag(IMAGECONDUCTOR);
	}

	SharedImageAudioTag AudioTagMap::getImageConductor() {
		return getImageTag(IMAGECONDUCTOR);
	}

	bool AudioTagMap::setImageConductor(const type::Image & imageConductor) {
		return setImageTag(IMAGECONDUCTOR, imageConductor);
	}

	bool AudioTagMap::setImageConductor(type::Image && imageConductor) {
		return setImageTag(IMAGECONDUCTOR, std::move(imageConductor));
	}




	SharedConstImageAudioTag AudioTagMap::getImageBand() const {
		return getImageTag(IMAGEBAND);
	}

	SharedImageAudioTag AudioTagMap::getImageBand() {
		return getImageTag(IMAGEBAND);
	}

	bool AudioTagMap::setImageBand(const type::Image & imageBand) {
		return setImageTag(IMAGEBAND, imageBand);
	}

	bool AudioTagMap::setImageBand(type::Image && imageBand) {
		return setImageTag(IMAGEBAND, std::move(imageBand));
	}




	SharedConstImageAudioTag AudioTagMap::getImageComposer() const {
		return getImageTag(IMAGECOMPOSER);
	}

	SharedImageAudioTag AudioTagMap::getImageComposer() {
		return getImageTag(IMAGECOMPOSER);
	}

	bool AudioTagMap::setImageComposer(const type::Image & imageComposer) {
		return setImageTag(IMAGECOMPOSER, imageComposer);
	}

	bool AudioTagMap::setImageComposer(type::Image && imageComposer) {
		return setImageTag(IMAGECOMPOSER, std::move(imageComposer));
	}




	SharedConstImageAudioTag AudioTagMap::getImageLyricist() const {
		return getImageTag(IMAGELYRICIST);
	}

	SharedImageAudioTag AudioTagMap::getImageLyricist() {
		return getImageTag(IMAGELYRICIST);
	}

	bool AudioTagMap::setImageLyricist(const type::Image & imageLyricist) {
		return setImageTag(IMAGELYRICIST, imageLyricist);
	}

	bool AudioTagMap::setImageLyricist(type::Image && imageLyricist) {
		return setImageTag(IMAGELYRICIST, std::move(imageLyricist));
	}




	SharedConstImageAudioTag AudioTagMap::getImageRecordingLocation() const {
		return getImageTag(IMAGERECORDINGLOCATION);
	}

	SharedImageAudioTag AudioTagMap::getImageRecordingLocation() {
		return getImageTag(IMAGERECORDINGLOCATION);
	}

	bool AudioTagMap::setImageRecordingLocation(const type::Image & imageRecordingLocation) {
		return setImageTag(IMAGERECORDINGLOCATION, imageRecordingLocation);
	}

	bool AudioTagMap::setImageRecordingLocation(type::Image && imageRecordingLocation) {
		return setImageTag(IMAGERECORDINGLOCATION, std::move(imageRecordingLocation));
	}




	SharedConstImageAudioTag AudioTagMap::getImageDuringRecording() const {
		return getImageTag(IMAGEDURINGRECORDING);
	}

	SharedImageAudioTag AudioTagMap::getImageDuringRecording() {
		return getImageTag(IMAGEDURINGRECORDING);
	}

	bool AudioTagMap::setImageDuringRecording(const type::Image & imageDuringRecording) {
		return setImageTag(IMAGEDURINGRECORDING, imageDuringRecording);
	}

	bool AudioTagMap::setImageDuringRecording(type::Image && imageDuringRecording) {
		return setImageTag(IMAGEDURINGRECORDING, std::move(imageDuringRecording));
	}




	SharedConstImageAudioTag AudioTagMap::getImageDuringPerformance() const {
		return getImageTag(IMAGEDURINGPERFORMANCE);
	}

	SharedImageAudioTag AudioTagMap::getImageDuringPerformance() {
		return getImageTag(IMAGEDURINGPERFORMANCE);
	}

	bool AudioTagMap::setImageDuringPerformance(const type::Image & imageDuringPerformance) {
		return setImageTag(IMAGEDURINGPERFORMANCE, imageDuringPerformance);
	}

	bool AudioTagMap::setImageDuringPerformance(type::Image && imageDuringPerformance) {
		return setImageTag(IMAGEDURINGPERFORMANCE, std::move(imageDuringPerformance));
	}




	SharedConstImageAudioTag AudioTagMap::getImageVideoCapture() const {
		return getImageTag(IMAGEVIDEOCAPTURE);
	}

	SharedImageAudioTag AudioTagMap::getImageVideoCapture() {
		return getImageTag(IMAGEVIDEOCAPTURE);
	}

	bool AudioTagMap::setImageVideoCapture(const type::Image & imageVideoCapture) {
		return setImageTag(IMAGEVIDEOCAPTURE, imageVideoCapture);
	}

	bool AudioTagMap::setImageVideoCapture(type::Image && imageVideoCapture) {
		return setImageTag(IMAGEVIDEOCAPTURE, std::move(imageVideoCapture));
	}




	SharedConstImageAudioTag AudioTagMap::getImageABrightColouredFish() const {
		return getImageTag(IMAGEABRIGHTCOLOUREDFISH);
	}

	SharedImageAudioTag AudioTagMap::getImageABrightColouredFish() {
		return getImageTag(IMAGEABRIGHTCOLOUREDFISH);
	}

	bool AudioTagMap::setImageABrightColouredFish(const type::Image & imageABrightColouredFish) {
		return setImageTag(IMAGEABRIGHTCOLOUREDFISH, imageABrightColouredFish);
	}

	bool AudioTagMap::setImageABrightColouredFish(type::Image && imageABrightColouredFish) {
		return setImageTag(IMAGEABRIGHTCOLOUREDFISH, std::move(imageABrightColouredFish));
	}




	SharedConstImageAudioTag AudioTagMap::getImageIllustration() const {
		return getImageTag(IMAGEILLUSTRATION);
	}

	SharedImageAudioTag AudioTagMap::getImageIllustration() {
		return getImageTag(IMAGEILLUSTRATION);
	}

	bool AudioTagMap::setImageIllustration(const type::Image & imageIllustration) {
		return setImageTag(IMAGEILLUSTRATION, imageIllustration);
	}

	bool AudioTagMap::setImageIllustration(type::Image && imageIllustration) {
		return setImageTag(IMAGEILLUSTRATION, std::move(imageIllustration));
	}




	SharedConstImageAudioTag AudioTagMap::getImageBandLogo() const {
		return getImageTag(IMAGEBANDLOGO);
	}

	SharedImageAudioTag AudioTagMap::getImageBandLogo() {
		return getImageTag(IMAGEBANDLOGO);
	}

	bool AudioTagMap::setImageBandLogo(const type::Image & imageBandLogo) {
		return setImageTag(IMAGEBANDLOGO, imageBandLogo);
	}

	bool AudioTagMap::setImageBandLogo(type::Image && imageBandLogo) {
		return setImageTag(IMAGEBANDLOGO, std::move(imageBandLogo));
	}




	SharedConstImageAudioTag AudioTagMap::getImagePublisherLogo() const {
		return getImageTag(IMAGEPUBLISHERLOGO);
	}

	SharedImageAudioTag AudioTagMap::getImagePublisherLogo() {
		return getImageTag(IMAGEPUBLISHERLOGO);
	}

	bool AudioTagMap::setImagePublisherLogo(const type::Image & imagePublisherLogo) {
		return setImageTag(IMAGEPUBLISHERLOGO, imagePublisherLogo);
	}

	bool AudioTagMap::setImagePublisherLogo(type::Image && imagePublisherLogo) {
		return setImageTag(IMAGEPUBLISHERLOGO, std::move(imagePublisherLogo));
	}











	SharedConstLyricsAudioTag AudioTagMap::getLyricsEng() const {
		return getLyricsTag(LYRICSENG);
	}

	SharedLyricsAudioTag AudioTagMap::getLyricsEng() {
		return getLyricsTag(LYRICSENG);
	}

	bool AudioTagMap::setLyricsEng(const type::Lyrics & lyricsEng) {
		return setLyricsTagByLang("eng"s, lyricsEng);
	}













	bool AudioTagMap::setYear(unsigned year) {
		return setDateTag(DATE, type::Date(year));
	}

	bool AudioTagMap::setOriginalYear(unsigned originalYear) {
		return setDateTag(ORIGINALDATE, type::Date(originalYear));
	}








	bool AudioTagMap::removeTagImpl(const std::string & name) {
		return tagMap.erase(name) > 0;
	}







	const AudioTagMap::SetType AudioTagMap::TAG_NAMES = {
		ALBUM,
		ALBUMARTIST,
		ALBUMSORT,
		ARTIST,
		ARTISTSORT,
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

		LYRICIST,
		ORIGINALALBUM,
		ORIGINALARTIST,
		ORIGINALDATE,
		PRODUCER,
		PUBLISHER,
		SUBTITLE,
		TITLE,
		TITLESORT,
		TOTALDISCNUMBER,
		TOTALTRACKNUMBER,
		TRACKNUMBER
	};

	const AudioTagMap::SetType AudioTagMap::STRING_TAG_NAMES = {
		ALBUM,
		ALBUMARTIST,
		ALBUMSORT,
		ARTIST,
		ARTISTSORT,
		COMMENT,
		COMPOSER,
		CONDUCTOR,
		GENRE,
		LYRICIST,
		ORIGINALALBUM,
		ORIGINALARTIST,
		PRODUCER,
		PUBLISHER,
		SUBTITLE,
		TITLE,
		TITLESORT,
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