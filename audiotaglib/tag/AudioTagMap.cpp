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















	SharedConstStringAudioTag AudioTagMap::getAlbum(const std::string & name) const {
		return getStringTag(name);
	}

	SharedStringAudioTag AudioTagMap::getAlbum(const std::string & name) {
		return getStringTag(name);
	}

	bool AudioTagMap::setAlbum(const std::string & album) {
		return setStringTag(ALBUM, album);
	}




	SharedConstStringAudioTag AudioTagMap::getAlbumArtist(const std::string & name) const {
		return getStringTag(name);
	}

	SharedStringAudioTag AudioTagMap::getAlbumArtist(const std::string & name) {
		return getStringTag(name);
	}

	bool AudioTagMap::setAlbumArtist(const std::string & albumArtist) {
		return setStringTag(ALBUMARTIST, albumArtist);
	}




	SharedConstStringAudioTag AudioTagMap::getAlbumSort(const std::string & name) const {
		return getStringTag(name);
	}

	SharedStringAudioTag AudioTagMap::getAlbumSort(const std::string & name) {
		return getStringTag(name);
	}

	bool AudioTagMap::setAlbumSort(const std::string & albumSort) {
		return setStringTag(ALBUMSORT, albumSort);
	}




	SharedConstStringAudioTag AudioTagMap::getArtist(const std::string & name) const {
		return getStringTag(name);
	}

	SharedStringAudioTag AudioTagMap::getArtist(const std::string & name) {
		return getStringTag(name);
	}

	bool AudioTagMap::setArtist(const std::string & artist) {
		return setStringTag(ARTIST, artist);
	}




	SharedConstStringAudioTag AudioTagMap::getArtistSort(const std::string & name) const {
		return getStringTag(name);
	}

	SharedStringAudioTag AudioTagMap::getArtistSort(const std::string & name) {
		return getStringTag(name);
	}

	bool AudioTagMap::setArtistSort(const std::string & artistSort) {
		return setStringTag(ARTISTSORT, artistSort);
	}




	SharedConstStringAudioTag AudioTagMap::getComment(const std::string & name) const {
		return getStringTag(name);
	}

	SharedStringAudioTag AudioTagMap::getComment(const std::string & name) {
		return getStringTag(name);
	}

	bool AudioTagMap::setComment(const std::string & comment) {
		return setStringTag(COMMENT, comment);
	}




	SharedConstStringAudioTag AudioTagMap::getComposer(const std::string & name) const {
		return getStringTag(name);
	}

	SharedStringAudioTag AudioTagMap::getComposer(const std::string & name) {
		return getStringTag(name);
	}

	bool AudioTagMap::setComposer(const std::string & composer) {
		return setStringTag(COMPOSER, composer);
	}




	SharedConstStringAudioTag AudioTagMap::getConductor(const std::string & name) const {
		return getStringTag(name);
	}

	SharedStringAudioTag AudioTagMap::getConductor(const std::string & name) {
		return getStringTag(name);
	}

	bool AudioTagMap::setConductor(const std::string & conductor) {
		return setStringTag(CONDUCTOR, conductor);
	}




	SharedConstStringAudioTag AudioTagMap::getGenre(const std::string & name) const {
		return getStringTag(name);
	}

	SharedStringAudioTag AudioTagMap::getGenre(const std::string & name) {
		return getStringTag(name);
	}

	bool AudioTagMap::setGenre(const std::string & genre) {
		return setStringTag(GENRE, genre);
	}




	SharedConstStringAudioTag AudioTagMap::getLyricist(const std::string & name) const {
		return getStringTag(name);
	}

	SharedStringAudioTag AudioTagMap::getLyricist(const std::string & name) {
		return getStringTag(name);
	}

	bool AudioTagMap::setLyricist(const std::string & lyricist) {
		return setStringTag(LYRICIST, lyricist);
	}




	SharedConstStringAudioTag AudioTagMap::getOriginalAlbum(const std::string & name) const {
		return getStringTag(name);
	}

	SharedStringAudioTag AudioTagMap::getOriginalAlbum(const std::string & name) {
		return getStringTag(name);
	}

	bool AudioTagMap::setOriginalAlbum(const std::string & originalAlbum) {
		return setStringTag(ORIGINALALBUM, originalAlbum);
	}




	SharedConstStringAudioTag AudioTagMap::getOriginalArtist(const std::string & name) const {
		return getStringTag(name);
	}

	SharedStringAudioTag AudioTagMap::getOriginalArtist(const std::string & name) {
		return getStringTag(name);
	}

	bool AudioTagMap::setOriginalArtist(const std::string & originalArtist) {
		return setStringTag(ORIGINALARTIST, originalArtist);
	}




	SharedConstStringAudioTag AudioTagMap::getProducer(const std::string & name) const {
		return getStringTag(name);
	}

	SharedStringAudioTag AudioTagMap::getProducer(const std::string & name) {
		return getStringTag(name);
	}

	bool AudioTagMap::setProducer(const std::string & producer) {
		return setStringTag(PRODUCER, producer);
	}




	SharedConstStringAudioTag AudioTagMap::getPublisher(const std::string & name) const {
		return getStringTag(name);
	}

	SharedStringAudioTag AudioTagMap::getPublisher(const std::string & name) {
		return getStringTag(name);
	}

	bool AudioTagMap::setPublisher(const std::string & publisher) {
		return setStringTag(PUBLISHER, publisher);
	}




	SharedConstStringAudioTag AudioTagMap::getSubtitle(const std::string & name) const {
		return getStringTag(name);
	}

	SharedStringAudioTag AudioTagMap::getSubtitle(const std::string & name) {
		return getStringTag(name);
	}

	bool AudioTagMap::setSubtitle(const std::string & subtitle) {
		return setStringTag(SUBTITLE, subtitle);
	}




	SharedConstStringAudioTag AudioTagMap::getTitle(const std::string & name) const {
		return getStringTag(name);
	}

	SharedStringAudioTag AudioTagMap::getTitle(const std::string & name) {
		return getStringTag(name);
	}

	bool AudioTagMap::setTitle(const std::string & title) {
		return setStringTag(TITLE, title);
	}




	SharedConstStringAudioTag AudioTagMap::getTitleSort(const std::string & name) const {
		return getStringTag(name);
	}

	SharedStringAudioTag AudioTagMap::getTitleSort(const std::string & name) {
		return getStringTag(name);
	}

	bool AudioTagMap::setTitleSort(const std::string & titleSort) {
		return setStringTag(TITLESORT, titleSort);
	}



















	SharedConstNumberAudioTag AudioTagMap::getBpm(const std::string & name) const {
		return getNumberTag(name);
	}

	SharedNumberAudioTag AudioTagMap::getBpm(const std::string & name) {
		return getNumberTag(name);
	}

	bool AudioTagMap::setBpm(unsigned bpm) {
		return setNumberTag(BPM, bpm);
	}




	SharedConstNumberAudioTag AudioTagMap::getDiscNumber(const std::string & name) const {
		return getNumberTag(name);
	}

	SharedNumberAudioTag AudioTagMap::getDiscNumber(const std::string & name) {
		return getNumberTag(name);
	}

	bool AudioTagMap::setDiscNumber(unsigned discNumber) {
		return setNumberTag(DISCNUMBER, discNumber);
	}




	SharedConstNumberAudioTag AudioTagMap::getTotalDiscNumber(const std::string & name) const {
		return getNumberTag(name);
	}

	SharedNumberAudioTag AudioTagMap::getTotalDiscNumber(const std::string & name) {
		return getNumberTag(name);
	}

	bool AudioTagMap::setTotalDiscNumber(unsigned totalDiscNumber) {
		return setNumberTag(TOTALDISCNUMBER, totalDiscNumber);
	}




	SharedConstNumberAudioTag AudioTagMap::getTotalTrackNumber(const std::string & name) const {
		return getNumberTag(name);
	}

	SharedNumberAudioTag AudioTagMap::getTotalTrackNumber(const std::string & name) {
		return getNumberTag(name);
	}

	bool AudioTagMap::setTotalTrackNumber(unsigned totalTrackNumber) {
		return setNumberTag(TOTALTRACKNUMBER, totalTrackNumber);
	}




	SharedConstNumberAudioTag AudioTagMap::getTrackNumber(const std::string & name) const {
		return getNumberTag(name);
	}

	SharedNumberAudioTag AudioTagMap::getTrackNumber(const std::string & name) {
		return getNumberTag(name);
	}

	bool AudioTagMap::setTrackNumber(unsigned trackNumber) {
		return setNumberTag(TRACKNUMBER, trackNumber);
	}













	SharedConstDateAudioTag AudioTagMap::getDate(const std::string & name) const {
		return getDateTag(name);
	}

	SharedDateAudioTag AudioTagMap::getDate(const std::string & name) {
		return getDateTag(name);
	}

	bool AudioTagMap::setDate(const type::Date & date) {
		return setDateTag(DATE, date);
	}




	SharedConstDateAudioTag AudioTagMap::getOriginalDate(const std::string & name) const {
		return getDateTag(name);
	}

	SharedDateAudioTag AudioTagMap::getOriginalDate(const std::string & name) {
		return getDateTag(name);
	}

	bool AudioTagMap::setOriginalDate(const type::Date & originalDate) {
		return setDateTag(ORIGINALDATE, originalDate);
	}

















	SharedConstImageAudioTag AudioTagMap::getImageOther(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImageOther(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImageOther(const type::Image & imageOther) {
		return setImageTag(IMAGEOTHER, imageOther);
	}




	SharedConstImageAudioTag AudioTagMap::getImageIcon(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImageIcon(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImageIcon(const type::Image & imageIcon) {
		return setImageTag(IMAGEICON, imageIcon);
	}




	SharedConstImageAudioTag AudioTagMap::getImageCoverFront(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImageCoverFront(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImageCoverFront(const type::Image & imageCoverFront) {
		return setImageTag(IMAGECOVERFRONT, imageCoverFront);
	}




	SharedConstImageAudioTag AudioTagMap::getImageCoverBack(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImageCoverBack(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImageCoverBack(const type::Image & imageCoverBack) {
		return setImageTag(IMAGECOVERBACK, imageCoverBack);
	}




	SharedConstImageAudioTag AudioTagMap::getImageLeaflet(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImageLeaflet(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImageLeaflet(const type::Image & imageLeaflet) {
		return setImageTag(IMAGELEAFLET, imageLeaflet);
	}




	SharedConstImageAudioTag AudioTagMap::getImageMedia(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImageMedia(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImageMedia(const type::Image & imageMedia) {
		return setImageTag(IMAGEMEDIA, imageMedia);
	}




	SharedConstImageAudioTag AudioTagMap::getImageArtist(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImageArtist(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImageArtist(const type::Image & imageArtist) {
		return setImageTag(IMAGEARTIST, imageArtist);
	}




	SharedConstImageAudioTag AudioTagMap::getImageConductor(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImageConductor(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImageConductor(const type::Image & imageConductor) {
		return setImageTag(IMAGECONDUCTOR, imageConductor);
	}




	SharedConstImageAudioTag AudioTagMap::getImageBand(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImageBand(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImageBand(const type::Image & imageBand) {
		return setImageTag(IMAGEBAND, imageBand);
	}




	SharedConstImageAudioTag AudioTagMap::getImageComposer(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImageComposer(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImageComposer(const type::Image & imageComposer) {
		return setImageTag(IMAGECOMPOSER, imageComposer);
	}




	SharedConstImageAudioTag AudioTagMap::getImageLyricist(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImageLyricist(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImageLyricist(const type::Image & imageLyricist) {
		return setImageTag(IMAGELYRICIST, imageLyricist);
	}




	SharedConstImageAudioTag AudioTagMap::getImageRecordingLocation(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImageRecordingLocation(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImageRecordingLocation(const type::Image & imageRecordingLocation) {
		return setImageTag(IMAGERECORDINGLOCATION, imageRecordingLocation);
	}




	SharedConstImageAudioTag AudioTagMap::getImageDuringRecording(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImageDuringRecording(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImageDuringRecording(const type::Image & imageDuringRecording) {
		return setImageTag(IMAGEDURINGRECORDING, imageDuringRecording);
	}




	SharedConstImageAudioTag AudioTagMap::getImageDuringPerformance(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImageDuringPerformance(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImageDuringPerformance(const type::Image & imageDuringPerformance) {
		return setImageTag(IMAGEDURINGPERFORMANCE, imageDuringPerformance);
	}




	SharedConstImageAudioTag AudioTagMap::getImageVideoCapture(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImageVideoCapture(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImageVideoCapture(const type::Image & imageVideoCapture) {
		return setImageTag(IMAGEVIDEOCAPTURE, imageVideoCapture);
	}




	SharedConstImageAudioTag AudioTagMap::getImageABrightColouredFish(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImageABrightColouredFish(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImageABrightColouredFish(const type::Image & imageABrightColouredFish) {
		return setImageTag(IMAGEABRIGHTCOLOUREDFISH, imageABrightColouredFish);
	}




	SharedConstImageAudioTag AudioTagMap::getImageIllustration(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImageIllustration(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImageIllustration(const type::Image & imageIllustration) {
		return setImageTag(IMAGEILLUSTRATION, imageIllustration);
	}




	SharedConstImageAudioTag AudioTagMap::getImageBandLogo(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImageBandLogo(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImageBandLogo(const type::Image & imageBandLogo) {
		return setImageTag(IMAGEBANDLOGO, imageBandLogo);
	}




	SharedConstImageAudioTag AudioTagMap::getImagePublisherLogo(const std::string & name) const {
		return getImageTag(name);
	}

	SharedImageAudioTag AudioTagMap::getImagePublisherLogo(const std::string & name) {
		return getImageTag(name);
	}

	bool AudioTagMap::setImagePublisherLogo(const type::Image & imagePublisherLogo) {
		return setImageTag(IMAGEPUBLISHERLOGO, imagePublisherLogo);
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






	size_t AudioTagMap::size() const {
		return tagMap.size();
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