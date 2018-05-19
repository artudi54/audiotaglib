#pragma once

#include <map>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cctype>
#include "AudioTag.hpp"
using namespace std::literals;



namespace tag {
	class AudioTagMap {
	public:
		static const std::string ALBUM;
		static const std::string ALBUMARTIST;
		static const std::string ARTIST;
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

		static const std::string LYRICYST;
		static const std::string ORIGINALALBUM;
		static const std::string ORIGINALARTIST;
		static const std::string ORIGINALDATE;
		static const std::string PRODUCER;
		static const std::string PUBLISHER;
		static const std::string SUBTITLE;
		static const std::string TITLE;
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


		SharedImageAudioTag getImageTag(const std::string & name);
		SharedImageAudioTag getImageTag(ImageAudioTag::ImageType imageType);
		SharedConstImageAudioTag getImageTag(const std::string & name) const;
		SharedConstImageAudioTag getImageTag(ImageAudioTag::ImageType imageType) const;
		bool setImageTag(const std::string & name, const type::Image &image);
		bool setImageTag(const std::string & name, type::Image &&image);
		bool setImageTag(ImageAudioTag::ImageType imageType, const type::Image &image);
		bool setImageTag(ImageAudioTag::ImageType imageType, type::Image &&image);



		bool setAlbum(const std::string &album);
		bool setArtist(const std::string &artist);
		bool setComment(const std::string &comment);
		bool setGenre(const std::string &genre);
		bool setTitle(const std::string &title);
		bool setTrackNumber(unsigned trackNumber);
		bool setYear(unsigned year);

		size_t size() const;
	private:
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