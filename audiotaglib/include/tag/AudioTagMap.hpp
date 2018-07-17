#pragma once

#include <map>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cctype>
#include <boost/algorithm/string.hpp>
#include "AudioTag.hpp"
using namespace std::literals;


//TODO: ADD ALBUMARTISTSORT
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
		static const std::string& ISRC();

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
		bool setDateTag(const std::string_view & name, const types::Date &date);

		SharedLyricsAudioTag getLyricsTagByLang(std::string language);
		SharedConstLyricsAudioTag getLyricsTagByLang(std::string language) const;
		SharedLyricsAudioTag getLyricsTag(const std::string_view & name);
		SharedConstLyricsAudioTag getLyricsTag(const std::string_view & name) const;
		bool setLyricsTagByLang(const std::string & language, const types::Lyrics &lyrics);


		SharedImageAudioTag getImageTag(const std::string_view & name);
		SharedImageAudioTag getImageTag(ImageAudioTag::ImageType imageType);
		SharedConstImageAudioTag getImageTag(const std::string_view & name) const;
		SharedConstImageAudioTag getImageTag(ImageAudioTag::ImageType imageType) const;
		bool setImageTag(const std::string_view & name, const types::Image &image);
		bool setImageTag(const std::string_view & name, types::Image &&image);
		bool setImageTag(ImageAudioTag::ImageType imageType, const types::Image &image);
		bool setImageTag(ImageAudioTag::ImageType imageType, types::Image &&image);





		SharedConstISRCAudioTag getISRCTag() const;
		SharedISRCAudioTag getISRCTag();
		bool setISRCTag(const types::ISRC &isrc);











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
		bool setEncodingDate(const types::Date & encodingDate);



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
		bool setDate(const types::Date & date);



		SharedConstDateAudioTag getOriginalDate() const;
		SharedDateAudioTag getOriginalDate();
		bool setOriginalDate(const types::Date & originalDate);














		SharedConstImageAudioTag getImageOther() const;
		SharedImageAudioTag getImageOther();
		bool setImageOther(const types::Image & imageOther);
		bool setImageOther(types::Image && imageOther);



		SharedConstImageAudioTag getImageIcon() const;
		SharedImageAudioTag getImageIcon();
		bool setImageIcon(const types::Image & imageIcon);
		bool setImageIcon(types::Image && imageIcon);



		SharedConstImageAudioTag getImageCoverFront() const;
		SharedImageAudioTag getImageCoverFront();
		bool setImageCoverFront(const types::Image & imageCoverFront);
		bool setImageCoverFront(types::Image && imageCoverFront);



		SharedConstImageAudioTag getImageCoverBack() const;
		SharedImageAudioTag getImageCoverBack();
		bool setImageCoverBack(const types::Image & imageCoverBack);
		bool setImageCoverBack(types::Image && imageCoverBack);



		SharedConstImageAudioTag getImageLeaflet() const;
		SharedImageAudioTag getImageLeaflet();
		bool setImageLeaflet(const types::Image & imageLeaflet);
		bool setImageLeaflet(types::Image && imageLeaflet);



		SharedConstImageAudioTag getImageMedia() const;
		SharedImageAudioTag getImageMedia();
		bool setImageMedia(const types::Image & imageMedia);
		bool setImageMedia(types::Image && imageMedia);



		SharedConstImageAudioTag getImageArtist() const;
		SharedImageAudioTag getImageArtist();
		bool setImageArtist(const types::Image & imageArtist);
		bool setImageArtist(types::Image && imageArtist);



		SharedConstImageAudioTag getImageConductor() const;
		SharedImageAudioTag getImageConductor();
		bool setImageConductor(const types::Image & imageConductor);
		bool setImageConductor(types::Image && imageConductor);



		SharedConstImageAudioTag getImageBand() const;
		SharedImageAudioTag getImageBand();
		bool setImageBand(const types::Image & imageBand);
		bool setImageBand(types::Image && imageBand);



		SharedConstImageAudioTag getImageComposer() const;
		SharedImageAudioTag getImageComposer();
		bool setImageComposer(const types::Image & imageComposer);
		bool setImageComposer(types::Image && imageComposer);



		SharedConstImageAudioTag getImageLyricist() const;
		SharedImageAudioTag getImageLyricist();
		bool setImageLyricist(const types::Image & imageLyricist);
		bool setImageLyricist(types::Image && imageLyricist);



		SharedConstImageAudioTag getImageRecordingLocation() const;
		SharedImageAudioTag getImageRecordingLocation();
		bool setImageRecordingLocation(const types::Image & imageRecordingLocation);
		bool setImageRecordingLocation(types::Image && imageRecordingLocation);



		SharedConstImageAudioTag getImageDuringRecording() const;
		SharedImageAudioTag getImageDuringRecording();
		bool setImageDuringRecording(const types::Image & imageDuringRecording);
		bool setImageDuringRecording(types::Image && imageDuringRecording);



		SharedConstImageAudioTag getImageDuringPerformance() const;
		SharedImageAudioTag getImageDuringPerformance();
		bool setImageDuringPerformance(const types::Image & imageDuringPerformance);
		bool setImageDuringPerformance(types::Image && imageDuringPerformance);



		SharedConstImageAudioTag getImageVideoCapture() const;
		SharedImageAudioTag getImageVideoCapture();
		bool setImageVideoCapture(const types::Image & imageVideoCapture);
		bool setImageVideoCapture(types::Image && imageVideoCapture);



		SharedConstImageAudioTag getImageABrightColouredFish() const;
		SharedImageAudioTag getImageABrightColouredFish();
		bool setImageABrightColouredFish(const types::Image & imageABrightColouredFish);
		bool setImageABrightColouredFish(types::Image && imageABrightColouredFish);



		SharedConstImageAudioTag getImageIllustration() const;
		SharedImageAudioTag getImageIllustration();
		bool setImageIllustration(const types::Image & imageIllustration);
		bool setImageIllustration(types::Image && imageIllustration);



		SharedConstImageAudioTag getImageBandLogo() const;
		SharedImageAudioTag getImageBandLogo();
		bool setImageBandLogo(const types::Image & imageBandLogo);
		bool setImageBandLogo(types::Image && imageBandLogo);



		SharedConstImageAudioTag getImagePublisherLogo() const;
		SharedImageAudioTag getImagePublisherLogo();
		bool setImagePublisherLogo(const types::Image & imagePublisherLogo);
		bool setImagePublisherLogo(types::Image && imagePublisherLogo);










		SharedConstLyricsAudioTag getLyricsEng() const;
		SharedLyricsAudioTag getLyricsEng();
		bool setLyricsEng(const types::Lyrics & lyricsEng);







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