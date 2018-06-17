#pragma once

#include <map>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cctype>
#include <boost/algorithm/string.hpp>
#include "AudioTag.hpp"
using namespace std::literals;



namespace tag {
	class AudioTagMap {
	public:
		//todo: make better lyrics access
		static const std::string& ALBUM();
		static const std::string& ALBUMARTIST();
		static const std::string& ALBUMSORT();
		static const std::string& ARTIST();
		static const std::string& ARTISTSORT();
		static const std::string& BPM();
		static const std::string& COMMENT();
		static const std::string& COMPOSER();
		static const std::string& CONDUCTOR();
		static const std::string& CONTENTGROUP();
		static const std::string& COPYRIGHT();
		static const std::string& DATE();
		static const std::string& DISCNUMBER();
		static const std::string& ENCODEDBY();
		static const std::string& ENCODERSETTINGS();
		static const std::string& ENCODINGDATE();
		static const std::string& GENRE();

		static const std::string& IMAGEOTHER();
		static const std::string& IMAGEICON();
		static const std::string& IMAGEOTHERICON();
		static const std::string& IMAGECOVERFRONT();
		static const std::string& IMAGECOVERBACK();
		static const std::string& IMAGELEAFLET();
		static const std::string& IMAGEMEDIA();
		static const std::string& IMAGEARTIST();
		static const std::string& IMAGECONDUCTOR();
		static const std::string& IMAGEBAND();
		static const std::string& IMAGECOMPOSER();
		static const std::string& IMAGELYRICIST();
		static const std::string& IMAGERECORDINGLOCATION();
		static const std::string& IMAGEDURINGRECORDING();
		static const std::string& IMAGEDURINGPERFORMANCE();
		static const std::string& IMAGEVIDEOCAPTURE();
		static const std::string& IMAGEABRIGHTCOLOUREDFISH();
		static const std::string& IMAGEILLUSTRATION();
		static const std::string& IMAGEBANDLOGO();
		static const std::string& IMAGEPUBLISHERLOGO();
		
		static const std::string& INITIALKEY();
	
		static const std::string& LYRICS();

		static const std::string& LYRICSENG();

		static const std::string& LYRICIST();
		static const std::string& MOOD();
		static const std::string& ORIGINALALBUM();
		static const std::string& ORIGINALARTIST();
		static const std::string& ORIGINALDATE();
		static const std::string& ORIGINALLYRICIST();
		static const std::string& PRODUCER();
		static const std::string& PUBLISHER();
		static const std::string& RADIOSTATION();
		static const std::string& RADIOSTATIONOWNER();
		static const std::string& SETSUBTITLE();
		static const std::string& SUBTITLE();
		static const std::string& TITLE();
		static const std::string& TITLESORT();
		static const std::string& TOTALDISCNUMBER();
		static const std::string& TOTALTRACKNUMBER();
		static const std::string& TRACKNUMBER();

		static const std::string& WWWCOMMERCIAL();
		static const std::string& WWWCOPYRIGHT();
		static const std::string& WWWFILE();
		static const std::string& WWWARTIST();
		static const std::string& WWWFILESOURCE();
		static const std::string& WWWRADIOPAGE();
		static const std::string& WWWPUBLISHER();

		class const_iterator;
		class iterator;

		iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;

		iterator end();
		const_iterator end() const;
		const_iterator cend() const;

		void merge(AudioTagMap &source);
		void merge(AudioTagMap &&source);
		void mergeWithOverwrite(AudioTagMap &source);
		void mergeWithOverwrite(AudioTagMap &&source);

		void clear();
		std::size_t size() const noexcept;

		bool removeTag(const std::string & name);


		iterator getTagIterator(const std::string_view & name);
		const_iterator getTagIterator(const std::string_view & name) const;
		SharedConstAudioTag getTag(const std::string_view & name) const;
		SharedAudioTag getTag(const std::string_view & name);

		SharedStringAudioTag getStringTag(const std::string_view & name);
		SharedConstStringAudioTag getStringTag(const std::string_view & name) const;
		bool setStringTag(const std::string_view & name, const std::string &text);

		
		SharedNumberAudioTag getNumberTag(const std::string_view & name);
		SharedConstNumberAudioTag getNumberTag(const std::string_view & name) const;
		bool setNumberTag(const std::string_view & name, unsigned number);

		SharedDateAudioTag getDateTag(const std::string_view & name);
		SharedConstDateAudioTag getDateTag(const std::string_view & name) const;
		bool setDateTag(const std::string_view & name, const type::Date &date);

		SharedLyricsAudioTag getLyricsTagByLang(std::string language);
		SharedConstLyricsAudioTag getLyricsTagByLang(std::string language) const;
		SharedLyricsAudioTag getLyricsTag(const std::string_view & name);
		SharedConstLyricsAudioTag getLyricsTag(const std::string_view & name) const;
		bool setLyricsTagByLang(const std::string & language, const type::Lyrics &lyrics);


		SharedImageAudioTag getImageTag(const std::string_view & name);
		SharedImageAudioTag getImageTag(ImageAudioTag::ImageType imageType);
		SharedConstImageAudioTag getImageTag(const std::string_view & name) const;
		SharedConstImageAudioTag getImageTag(ImageAudioTag::ImageType imageType) const;
		bool setImageTag(const std::string_view & name, const type::Image &image);
		bool setImageTag(const std::string_view & name, type::Image &&image);
		bool setImageTag(ImageAudioTag::ImageType imageType, const type::Image &image);
		bool setImageTag(ImageAudioTag::ImageType imageType, type::Image &&image);











		SharedConstStringAudioTag getAlbum() const;
		SharedStringAudioTag getAlbum();
		bool setAlbum(const std::string & album);



		SharedConstStringAudioTag getAlbumArtist() const;
		SharedStringAudioTag getAlbumArtist();
		bool setAlbumArtist(const std::string & albumArtist);



		SharedConstStringAudioTag getAlbumSort() const;
		SharedStringAudioTag getAlbumSort();
		bool setAlbumSort(const std::string & albumSort);



		SharedConstStringAudioTag getArtist() const;
		SharedStringAudioTag getArtist();
		bool setArtist(const std::string & artist);



		SharedConstStringAudioTag getArtistSort() const;
		SharedStringAudioTag getArtistSort();
		bool setArtistSort(const std::string & artistSort);



		SharedConstStringAudioTag getComment() const;
		SharedStringAudioTag getComment();
		bool setComment(const std::string & comment);



		SharedConstStringAudioTag getComposer() const;
		SharedStringAudioTag getComposer();
		bool setComposer(const std::string & composer);



		SharedConstStringAudioTag getConductor() const;
		SharedStringAudioTag getConductor();
		bool setConductor(const std::string & conductor);



		SharedConstStringAudioTag getContentGroup() const;
		SharedStringAudioTag getContentGroup();
		bool setContentGroup(const std::string & contentGroup);



		SharedConstStringAudioTag getCopyright() const;
		SharedStringAudioTag getCopyright();
		bool setCopyright(const std::string & copyright);



		SharedConstStringAudioTag getEncodedBy() const;
		SharedStringAudioTag getEncodedBy();
		bool setEncodedBy(const std::string & encodedBy);



		SharedConstStringAudioTag getEncoderSettings() const;
		SharedStringAudioTag getEncoderSettings();
		bool setEncoderSettings(const std::string & encoderSettings);



		SharedConstDateAudioTag getEncodingDate() const;
		SharedDateAudioTag getEncodingDate();
		bool setEncodingDate(const type::Date & encodingDate);



		SharedConstStringAudioTag getGenre() const;
		SharedStringAudioTag getGenre();
		bool setGenre(const std::string & genre);



		SharedConstStringAudioTag getInitialKey() const;
		SharedStringAudioTag getInitialKey();
		bool setInitialKey(const std::string & initialKey);



		SharedConstStringAudioTag getLyricist() const;
		SharedStringAudioTag getLyricist();
		bool setLyricist(const std::string & lyricist);



		SharedConstStringAudioTag getMood() const;
		SharedStringAudioTag getMood();
		bool setMood(const std::string & mood);



		SharedConstStringAudioTag getOriginalAlbum() const;
		SharedStringAudioTag getOriginalAlbum();
		bool setOriginalAlbum(const std::string & originalAlbum);



		SharedConstStringAudioTag getOriginalArtist() const;
		SharedStringAudioTag getOriginalArtist();
		bool setOriginalArtist(const std::string & originalArtist);



		SharedConstStringAudioTag getOriginalLyricist() const;
		SharedStringAudioTag getOriginalLyricist();
		bool setOriginalLyricist(const std::string & originalLyricist);



		SharedConstStringAudioTag getProducer() const;
		SharedStringAudioTag getProducer();
		bool setProducer(const std::string & producer);



		SharedConstStringAudioTag getPublisher() const;
		SharedStringAudioTag getPublisher();
		bool setPublisher(const std::string & publisher);



		SharedConstStringAudioTag getRadioStation() const;
		SharedStringAudioTag getRadioStation();
		bool setRadioStation(const std::string & radioStation);



		SharedConstStringAudioTag getRadioStationOwner() const;
		SharedStringAudioTag getRadioStationOwner();
		bool setRadioStationOwner(const std::string & radioStationOwner);



		SharedConstStringAudioTag getSetSubtitle() const;
		SharedStringAudioTag getSetSubtitle();
		bool setSetSubtitle(const std::string & setSubtitle);



		SharedConstStringAudioTag getSubtitle() const;
		SharedStringAudioTag getSubtitle();
		bool setSubtitle(const std::string & subtitle);



		SharedConstStringAudioTag getTitle() const;
		SharedStringAudioTag getTitle();
		bool setTitle(const std::string & title);



		SharedConstStringAudioTag getTitleSort() const;
		SharedStringAudioTag getTitleSort();
		bool setTitleSort(const std::string & titleSort);











		SharedConstNumberAudioTag getBpm() const;
		SharedNumberAudioTag getBpm();
		bool setBpm(unsigned bpm);



		SharedConstNumberAudioTag getDiscNumber() const;
		SharedNumberAudioTag getDiscNumber();
		bool setDiscNumber(unsigned discNumber);



		SharedConstNumberAudioTag getTotalDiscNumber() const;
		SharedNumberAudioTag getTotalDiscNumber();
		bool setTotalDiscNumber(unsigned totalDiscNumber);



		SharedConstNumberAudioTag getTotalTrackNumber() const;
		SharedNumberAudioTag getTotalTrackNumber();
		bool setTotalTrackNumber(unsigned totalTrackNumber);



		SharedConstNumberAudioTag getTrackNumber() const;
		SharedNumberAudioTag getTrackNumber();
		bool setTrackNumber(unsigned trackNumber);















		SharedConstDateAudioTag getDate() const;
		SharedDateAudioTag getDate();
		bool setDate(const type::Date & date);



		SharedConstDateAudioTag getOriginalDate() const;
		SharedDateAudioTag getOriginalDate();
		bool setOriginalDate(const type::Date & originalDate);














		SharedConstImageAudioTag getImageOther() const;
		SharedImageAudioTag getImageOther();
		bool setImageOther(const type::Image & imageOther);
		bool setImageOther(type::Image && imageOther);



		SharedConstImageAudioTag getImageIcon() const;
		SharedImageAudioTag getImageIcon();
		bool setImageIcon(const type::Image & imageIcon);
		bool setImageIcon(type::Image && imageIcon);



		SharedConstImageAudioTag getImageCoverFront() const;
		SharedImageAudioTag getImageCoverFront();
		bool setImageCoverFront(const type::Image & imageCoverFront);
		bool setImageCoverFront(type::Image && imageCoverFront);



		SharedConstImageAudioTag getImageCoverBack() const;
		SharedImageAudioTag getImageCoverBack();
		bool setImageCoverBack(const type::Image & imageCoverBack);
		bool setImageCoverBack(type::Image && imageCoverBack);



		SharedConstImageAudioTag getImageLeaflet() const;
		SharedImageAudioTag getImageLeaflet();
		bool setImageLeaflet(const type::Image & imageLeaflet);
		bool setImageLeaflet(type::Image && imageLeaflet);



		SharedConstImageAudioTag getImageMedia() const;
		SharedImageAudioTag getImageMedia();
		bool setImageMedia(const type::Image & imageMedia);
		bool setImageMedia(type::Image && imageMedia);



		SharedConstImageAudioTag getImageArtist() const;
		SharedImageAudioTag getImageArtist();
		bool setImageArtist(const type::Image & imageArtist);
		bool setImageArtist(type::Image && imageArtist);



		SharedConstImageAudioTag getImageConductor() const;
		SharedImageAudioTag getImageConductor();
		bool setImageConductor(const type::Image & imageConductor);
		bool setImageConductor(type::Image && imageConductor);



		SharedConstImageAudioTag getImageBand() const;
		SharedImageAudioTag getImageBand();
		bool setImageBand(const type::Image & imageBand);
		bool setImageBand(type::Image && imageBand);



		SharedConstImageAudioTag getImageComposer() const;
		SharedImageAudioTag getImageComposer();
		bool setImageComposer(const type::Image & imageComposer);
		bool setImageComposer(type::Image && imageComposer);



		SharedConstImageAudioTag getImageLyricist() const;
		SharedImageAudioTag getImageLyricist();
		bool setImageLyricist(const type::Image & imageLyricist);
		bool setImageLyricist(type::Image && imageLyricist);



		SharedConstImageAudioTag getImageRecordingLocation() const;
		SharedImageAudioTag getImageRecordingLocation();
		bool setImageRecordingLocation(const type::Image & imageRecordingLocation);
		bool setImageRecordingLocation(type::Image && imageRecordingLocation);



		SharedConstImageAudioTag getImageDuringRecording() const;
		SharedImageAudioTag getImageDuringRecording();
		bool setImageDuringRecording(const type::Image & imageDuringRecording);
		bool setImageDuringRecording(type::Image && imageDuringRecording);



		SharedConstImageAudioTag getImageDuringPerformance() const;
		SharedImageAudioTag getImageDuringPerformance();
		bool setImageDuringPerformance(const type::Image & imageDuringPerformance);
		bool setImageDuringPerformance(type::Image && imageDuringPerformance);



		SharedConstImageAudioTag getImageVideoCapture() const;
		SharedImageAudioTag getImageVideoCapture();
		bool setImageVideoCapture(const type::Image & imageVideoCapture);
		bool setImageVideoCapture(type::Image && imageVideoCapture);



		SharedConstImageAudioTag getImageABrightColouredFish() const;
		SharedImageAudioTag getImageABrightColouredFish();
		bool setImageABrightColouredFish(const type::Image & imageABrightColouredFish);
		bool setImageABrightColouredFish(type::Image && imageABrightColouredFish);



		SharedConstImageAudioTag getImageIllustration() const;
		SharedImageAudioTag getImageIllustration();
		bool setImageIllustration(const type::Image & imageIllustration);
		bool setImageIllustration(type::Image && imageIllustration);



		SharedConstImageAudioTag getImageBandLogo() const;
		SharedImageAudioTag getImageBandLogo();
		bool setImageBandLogo(const type::Image & imageBandLogo);
		bool setImageBandLogo(type::Image && imageBandLogo);



		SharedConstImageAudioTag getImagePublisherLogo() const;
		SharedImageAudioTag getImagePublisherLogo();
		bool setImagePublisherLogo(const type::Image & imagePublisherLogo);
		bool setImagePublisherLogo(type::Image && imagePublisherLogo);










		SharedConstLyricsAudioTag getLyricsEng() const;
		SharedLyricsAudioTag getLyricsEng();
		bool setLyricsEng(const type::Lyrics & lyricsEng);







		bool setYear(unsigned year);
		bool setOriginalYear(unsigned originalYear);

	private:
		template < class Type >
		std::shared_ptr<Type> getTypeTag(const std::string_view & name) {
			SharedAudioTag audioTag = getTag(name);
			if (audioTag != nullptr)
				return std::dynamic_pointer_cast<Type>(audioTag);
			return std::shared_ptr<Type>();
		}

		template < class Type >
		std::shared_ptr< const Type> getTypeTag(const std::string_view & name) const {
				SharedConstAudioTag audioTag = getTag(name);
				if (audioTag != nullptr)
					return std::dynamic_pointer_cast<const Type>(audioTag);
				return std::shared_ptr<const Type>();
		}
		bool removeTagImpl(const std::string & name);


		using MapType = std::map<std::string, SharedAudioTag, std::less<>>;
		using SetType = std::unordered_set<std::string_view>;

		MapType tagMap;
		static const SetType TAG_NAMES;
		static const SetType STRING_TAG_NAMES;
		static const SetType NUMBER_TAG_NAMES;
		static const SetType DATE_TAG_NAMES;
		static const SetType IMAGE_TAG_NAMES;
	};








	class AudioTagMap::const_iterator {
		friend class AudioTagMap;
		using internal_iterator = MapType::iterator;
	public:
		using iterator_category = internal_iterator::iterator_category;
		using value_type = SharedConstAudioTag;
		using difference_time = internal_iterator::difference_type;
		using reference = value_type & ;
		using pointer = value_type * ;

		const_iterator() = default;

		bool operator==(const const_iterator &other) const;
		bool operator!=(const const_iterator &other) const;

		const_iterator& operator++();
		const_iterator operator++(int);
		const_iterator& operator--();
		const_iterator operator--(int);

		const pointer operator->() const;
		const reference operator*() const;
		AudioTag::Type getType() const;

		template < class Type >
		std::shared_ptr<const Type> as() const {
			return std::dynamic_pointer_cast<Type>(**this);
		}
	protected:
		const_iterator(const internal_iterator &internalIterator);
		mutable internal_iterator internalIterator;
		mutable value_type returned;
	};









	//todo: add reverse_iterator
	class AudioTagMap::iterator : public const_iterator {
		friend class AudioTagMap;
	public:
		using value_type = SharedAudioTag;
		using reference = value_type & ;
		using pointer = value_type * ;

		iterator() = default;
		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);

		pointer operator->();
		reference operator*();

		template < class Type >
		std::shared_ptr<Type> as() {
			return std::dynamic_pointer_cast<Type>(**this);
		}
	protected:
		using const_iterator::const_iterator;
	};


}