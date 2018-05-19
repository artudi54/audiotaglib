#pragma once

#include <map>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cctype>
#include <boost/algorithm/string.hpp>
#include "AudioTag.hpp"
using namespace std::literals;



//todo: implement string_views
namespace tag {
	class AudioTagMap {
	public:
		static const std::string ALBUM;
		static const std::string ALBUMARTIST;
		static const std::string ALBUMSORT;
		static const std::string ARTIST;
		static const std::string ARTISTSORT;
		static const std::string BPM;
		static const std::string COMMENT;
		static const std::string COMPOSER;
		static const std::string CONDUCTOR;
		static const std::string DATE;
		static const std::string DISCNUMBER;
		static const std::string GENRE;

		static const std::string IMAGEOTHER;
		static const std::string IMAGEICON;
		static const std::string IMAGEOTHERICON;
		static const std::string IMAGECOVERFRONT;
		static const std::string IMAGECOVERBACK;
		static const std::string IMAGELEAFLET;
		static const std::string IMAGEMEDIA;
		static const std::string IMAGEARTIST;
		static const std::string IMAGECONDUCTOR;
		static const std::string IMAGEBAND;
		static const std::string IMAGECOMPOSER;
		static const std::string IMAGELYRICIST;
		static const std::string IMAGERECORDINGLOCATION;
		static const std::string IMAGEDURINGRECORDING;
		static const std::string IMAGEDURINGPERFORMANCE;
		static const std::string IMAGEVIDEOCAPTURE;
		static const std::string IMAGEABRIGHTCOLOUREDFISH;
		static const std::string IMAGEILLUSTRATION;
		static const std::string IMAGEBANDLOGO;
		static const std::string IMAGEPUBLISHERLOGO;

		static const std::string LYRICSENG;

		static const std::string LYRICIST;
		static const std::string ORIGINALALBUM;
		static const std::string ORIGINALARTIST;
		static const std::string ORIGINALDATE;
		static const std::string PRODUCER;
		static const std::string PUBLISHER;
		static const std::string SUBTITLE;
		static const std::string TITLE;
		static const std::string TITLESORT;
		static const std::string TOTALDISCNUMBER;
		static const std::string TOTALTRACKNUMBER;
		static const std::string TRACKNUMBER;

		class const_iterator;
		class iterator;

		iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;

		iterator end();
		const_iterator end() const;
		const_iterator cend() const;

		void mergeWithOverwrite(AudioTagMap &source);
		void mergeWithOverwrite(AudioTagMap &&source);

		void clear();

		bool removeTag(const std::string & name);


		iterator getTagIterator(const std::string &name);
		const_iterator getTagIterator(const std::string &name) const;
		SharedConstAudioTag getTag(const std::string &name) const;
		SharedAudioTag getTag(const std::string &name);

		SharedStringAudioTag getStringTag(const std::string & name);
		SharedConstStringAudioTag getStringTag(const std::string & name) const;
		bool setStringTag(const std::string & name, const std::string &text);

		
		SharedNumberAudioTag getNumberTag(const std::string & name);
		SharedConstNumberAudioTag getNumberTag(const std::string & name) const;
		bool setNumberTag(const std::string & name, unsigned number);

		SharedDateAudioTag getDateTag(const std::string & name);
		SharedConstDateAudioTag getDateTag(const std::string & name) const;
		bool setDateTag(const std::string & name, const type::Date &date);

		SharedLyricsAudioTag getLyricsTagByLang(std::string language);
		SharedConstLyricsAudioTag getLyricsTagByLang(std::string language) const;
		SharedLyricsAudioTag getLyricsTag(const std::string & name);
		SharedConstLyricsAudioTag getLyricsTag(const std::string & name) const;
		bool setLyricsTagByLang(const std::string & language, const type::Lyrics &lyrics);


		SharedImageAudioTag getImageTag(const std::string & name);
		SharedImageAudioTag getImageTag(ImageAudioTag::ImageType imageType);
		SharedConstImageAudioTag getImageTag(const std::string & name) const;
		SharedConstImageAudioTag getImageTag(ImageAudioTag::ImageType imageType) const;
		bool setImageTag(const std::string & name, const type::Image &image);
		bool setImageTag(const std::string & name, type::Image &&image);
		bool setImageTag(ImageAudioTag::ImageType imageType, const type::Image &image);
		bool setImageTag(ImageAudioTag::ImageType imageType, type::Image &&image);











		SharedConstStringAudioTag getAlbum(const std::string & name) const;
		SharedStringAudioTag getAlbum(const std::string & name);
		bool setAlbum(const std::string & album);



		SharedConstStringAudioTag getAlbumArtist(const std::string & name) const;
		SharedStringAudioTag getAlbumArtist(const std::string & name);
		bool setAlbumArtist(const std::string & albumArtist);



		SharedConstStringAudioTag getAlbumSort(const std::string & name) const;
		SharedStringAudioTag getAlbumSort(const std::string & name);
		bool setAlbumSort(const std::string & albumSort);



		SharedConstStringAudioTag getArtist(const std::string & name) const;
		SharedStringAudioTag getArtist(const std::string & name);
		bool setArtist(const std::string & artist);



		SharedConstStringAudioTag getArtistSort(const std::string & name) const;
		SharedStringAudioTag getArtistSort(const std::string & name);
		bool setArtistSort(const std::string & artistSort);



		SharedConstStringAudioTag getComment(const std::string & name) const;
		SharedStringAudioTag getComment(const std::string & name);
		bool setComment(const std::string & comment);



		SharedConstStringAudioTag getComposer(const std::string & name) const;
		SharedStringAudioTag getComposer(const std::string & name);
		bool setComposer(const std::string & composer);



		SharedConstStringAudioTag getConductor(const std::string & name) const;
		SharedStringAudioTag getConductor(const std::string & name);
		bool setConductor(const std::string & conductor);



		SharedConstStringAudioTag getGenre(const std::string & name) const;
		SharedStringAudioTag getGenre(const std::string & name);
		bool setGenre(const std::string & genre);



		SharedConstStringAudioTag getLyricist(const std::string & name) const;
		SharedStringAudioTag getLyricist(const std::string & name);
		bool setLyricist(const std::string & lyricist);



		SharedConstStringAudioTag getOriginalAlbum(const std::string & name) const;
		SharedStringAudioTag getOriginalAlbum(const std::string & name);
		bool setOriginalAlbum(const std::string & originalAlbum);



		SharedConstStringAudioTag getOriginalArtist(const std::string & name) const;
		SharedStringAudioTag getOriginalArtist(const std::string & name);
		bool setOriginalArtist(const std::string & originalArtist);



		SharedConstStringAudioTag getProducer(const std::string & name) const;
		SharedStringAudioTag getProducer(const std::string & name);
		bool setProducer(const std::string & producer);



		SharedConstStringAudioTag getPublisher(const std::string & name) const;
		SharedStringAudioTag getPublisher(const std::string & name);
		bool setPublisher(const std::string & publisher);



		SharedConstStringAudioTag getSubtitle(const std::string & name) const;
		SharedStringAudioTag getSubtitle(const std::string & name);
		bool setSubtitle(const std::string & subtitle);



		SharedConstStringAudioTag getTitle(const std::string & name) const;
		SharedStringAudioTag getTitle(const std::string & name);
		bool setTitle(const std::string & title);



		SharedConstStringAudioTag getTitleSort(const std::string & name) const;
		SharedStringAudioTag getTitleSort(const std::string & name);
		bool setTitleSort(const std::string & titleSort);











		SharedConstNumberAudioTag getBpm(const std::string & name) const;
		SharedNumberAudioTag getBpm(const std::string & name);
		bool setBpm(unsigned bpm);



		SharedConstNumberAudioTag getDiscNumber(const std::string & name) const;
		SharedNumberAudioTag getDiscNumber(const std::string & name);
		bool setDiscNumber(unsigned discNumber);



		SharedConstNumberAudioTag getTotalDiscNumber(const std::string & name) const;
		SharedNumberAudioTag getTotalDiscNumber(const std::string & name);
		bool setTotalDiscNumber(unsigned totalDiscNumber);



		SharedConstNumberAudioTag getTotalTrackNumber(const std::string & name) const;
		SharedNumberAudioTag getTotalTrackNumber(const std::string & name);
		bool setTotalTrackNumber(unsigned totalTrackNumber);



		SharedConstNumberAudioTag getTrackNumber(const std::string & name) const;
		SharedNumberAudioTag getTrackNumber(const std::string & name);
		bool setTrackNumber(unsigned trackNumber);















		SharedConstDateAudioTag getDate(const std::string & name) const;
		SharedDateAudioTag getDate(const std::string & name);
		bool setDate(const type::Date & date);



		SharedConstDateAudioTag getOriginalDate(const std::string & name) const;
		SharedDateAudioTag getOriginalDate(const std::string & name);
		bool setOriginalDate(const type::Date & originalDate);














		SharedConstImageAudioTag getImageOther(const std::string & name) const;
		SharedImageAudioTag getImageOther(const std::string & name);
		bool setImageOther(const type::Image & imageOther);



		SharedConstImageAudioTag getImageIcon(const std::string & name) const;
		SharedImageAudioTag getImageIcon(const std::string & name);
		bool setImageIcon(const type::Image & imageIcon);



		SharedConstImageAudioTag getImageCoverFront(const std::string & name) const;
		SharedImageAudioTag getImageCoverFront(const std::string & name);
		bool setImageCoverFront(const type::Image & imageCoverFront);



		SharedConstImageAudioTag getImageCoverBack(const std::string & name) const;
		SharedImageAudioTag getImageCoverBack(const std::string & name);
		bool setImageCoverBack(const type::Image & imageCoverBack);



		SharedConstImageAudioTag getImageLeaflet(const std::string & name) const;
		SharedImageAudioTag getImageLeaflet(const std::string & name);
		bool setImageLeaflet(const type::Image & imageLeaflet);



		SharedConstImageAudioTag getImageMedia(const std::string & name) const;
		SharedImageAudioTag getImageMedia(const std::string & name);
		bool setImageMedia(const type::Image & imageMedia);



		SharedConstImageAudioTag getImageArtist(const std::string & name) const;
		SharedImageAudioTag getImageArtist(const std::string & name);
		bool setImageArtist(const type::Image & imageArtist);



		SharedConstImageAudioTag getImageConductor(const std::string & name) const;
		SharedImageAudioTag getImageConductor(const std::string & name);
		bool setImageConductor(const type::Image & imageConductor);



		SharedConstImageAudioTag getImageBand(const std::string & name) const;
		SharedImageAudioTag getImageBand(const std::string & name);
		bool setImageBand(const type::Image & imageBand);



		SharedConstImageAudioTag getImageComposer(const std::string & name) const;
		SharedImageAudioTag getImageComposer(const std::string & name);
		bool setImageComposer(const type::Image & imageComposer);



		SharedConstImageAudioTag getImageLyricist(const std::string & name) const;
		SharedImageAudioTag getImageLyricist(const std::string & name);
		bool setImageLyricist(const type::Image & imageLyricist);



		SharedConstImageAudioTag getImageRecordingLocation(const std::string & name) const;
		SharedImageAudioTag getImageRecordingLocation(const std::string & name);
		bool setImageRecordingLocation(const type::Image & imageRecordingLocation);



		SharedConstImageAudioTag getImageDuringRecording(const std::string & name) const;
		SharedImageAudioTag getImageDuringRecording(const std::string & name);
		bool setImageDuringRecording(const type::Image & imageDuringRecording);



		SharedConstImageAudioTag getImageDuringPerformance(const std::string & name) const;
		SharedImageAudioTag getImageDuringPerformance(const std::string & name);
		bool setImageDuringPerformance(const type::Image & imageDuringPerformance);



		SharedConstImageAudioTag getImageVideoCapture(const std::string & name) const;
		SharedImageAudioTag getImageVideoCapture(const std::string & name);
		bool setImageVideoCapture(const type::Image & imageVideoCapture);



		SharedConstImageAudioTag getImageABrightColouredFish(const std::string & name) const;
		SharedImageAudioTag getImageABrightColouredFish(const std::string & name);
		bool setImageABrightColouredFish(const type::Image & imageABrightColouredFish);



		SharedConstImageAudioTag getImageIllustration(const std::string & name) const;
		SharedImageAudioTag getImageIllustration(const std::string & name);
		bool setImageIllustration(const type::Image & imageIllustration);



		SharedConstImageAudioTag getImageBandLogo(const std::string & name) const;
		SharedImageAudioTag getImageBandLogo(const std::string & name);
		bool setImageBandLogo(const type::Image & imageBandLogo);



		SharedConstImageAudioTag getImagePublisherLogo(const std::string & name) const;
		SharedImageAudioTag getImagePublisherLogo(const std::string & name);
		bool setImagePublisherLogo(const type::Image & imagePublisherLogo);










		SharedConstLyricsAudioTag getLyricsEng() const;
		SharedLyricsAudioTag getLyricsEng();
		bool setLyricsEng(const type::Lyrics & lyricsEng);







		bool setYear(unsigned year);
		bool setOriginalYear(unsigned originalYear);



		size_t size() const;
	private:
		static const std::string LYRICS;
		template < class Type >
		std::shared_ptr<Type> getTypeTag(const std::string & name) {
			SharedAudioTag audioTag = getTag(name);
			if (audioTag != nullptr)
				return std::dynamic_pointer_cast<Type>(audioTag);
			return std::shared_ptr<Type>();
		}
		template < class Type >
			std::shared_ptr< const Type> getTypeTag(const std::string & name) const {
				SharedConstAudioTag audioTag = getTag(name);
				if (audioTag != nullptr)
					return std::dynamic_pointer_cast<const Type>(audioTag);
				return std::shared_ptr<const Type>();
		}
		using MapType = std::map<std::string, SharedAudioTag>;
		using SetType = std::unordered_set<std::string>;

		bool removeTagImpl(const std::string &name);

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