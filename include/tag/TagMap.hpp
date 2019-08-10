#pragma once
#include <map>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cctype>
#include <optional>
#include <tag/Tag.hpp>
using namespace std::literals;


namespace tag {
	class TagMap {
	public:
		/*  todo: make better lyrics access
            todo: add more tags
            todo: consider changing some names to get better compatibility with mp3tag
            todo: catalogue number
            todo: add performer (credit list)
            todo: compilation and podcast flags
            todo: remove aliasing
        */
		static const std::string& ALBUM();
		static const std::string& ALBUMARTIST();
		static const std::string& ALBUMARTISTSORT();
		static const std::string& ALBUMSORT();
		static const std::string& ARRANGER();
		static const std::string& ARTIST();
		static const std::string& ARTISTSORT();

		static const std::string& BARCODE();

		static const std::string& BPM();
		static const std::string& COMMENT();
		static const std::string& COMPOSER();
		static const std::string& COMPOSERSORT();
		static const std::string& CONDUCTOR();
		static const std::string& CONTENTGROUP();
		static const std::string& COPYRIGHT();
		static const std::string& DATE();
		static const std::string& DISCNUMBER();
		static const std::string& ENGINEER();
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
		static const std::string& IMAGELEADARTIST();
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
        static const std::string& MIXDJ();
        static const std::string& MIXENGINEER();
		static const std::string& MOOD();
		static const std::string& ORIGINALALBUM();
		static const std::string& ORIGINALARTIST();
		static const std::string& ORIGINALDATE();
		static const std::string& ORIGINALLYRICIST();
		static const std::string& PRODUCER();
		static const std::string& PUBLISHER();
		static const std::string& RADIOSTATION();
		static const std::string& RADIOSTATIONOWNER();
		static const std::string& REMIXER();
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
		static const std::string& WWWPAYMENT();

        static const std::string &WWWPODCAST();
		static const std::string& WWWPUBLISHER();
		static const std::string& WWWRADIOPAGE();

		class const_iterator;
		class iterator;

		iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;

		iterator end();
		const_iterator end() const;
		const_iterator cend() const;

		void merge(TagMap &source);
		void merge(TagMap &&source);
		void mergeWithOverwrite(TagMap &source);
		void mergeWithOverwrite(TagMap &&source);

		void clear();
		std::size_t getSize() const noexcept;
		bool isEmpty() const noexcept;
		bool containsTag(const std::string_view &name) const;
		bool removeTag(const std::string &name);
		std::size_t removeEmpty();


		iterator getTagIterator(const std::string_view & name);
		const_iterator getTagIterator(const std::string_view & name) const;
		SharedConstAudioTag getTagPointer(const std::string_view &name) const;
		SharedAudioTag getTagPointer(const std::string_view &name);

		SharedStringAudioTag getStringTagPointer(const std::string_view &name);
		SharedConstStringAudioTag getStringTagPointer(const std::string_view &name) const;
        std::optional<std::string> getStringTagOptional(const std::string_view &name) const;
		std::string getStringTag(const std::string_view &name) const;
		bool setStringTag(const std::string_view & name, const std::string &text);

		
		SharedNumberAudioTag getNumberTagPointer(const std::string_view &name);
		SharedConstNumberAudioTag getNumberTagPointer(const std::string_view &name) const;
        std::optional<std::uint32_t> getNumberTagOptional(const std::string_view &name) const;
        std::uint32_t getNumberTag(const std::string_view &name) const;
        bool setNumberTag(const std::string_view & name, std::uint32_t number);

		SharedDateAudioTag getDateTagPointer(const std::string_view &name);
		SharedConstDateAudioTag getDateTagPointer(const std::string_view &name) const;
        std::optional<types::Date> getDateTagOptional(const std::string_view &name) const;
        types::Date getDateTag(const std::string_view &name) const;
        bool setDateTag(const std::string_view & name, const types::Date &date);

		SharedLyricsAudioTag getLyricsTagPointerByLang(std::string language);
		SharedConstLyricsAudioTag getLyricsTagPointerByLang(std::string language) const;
		SharedLyricsAudioTag getLyricsTagPointer(const std::string_view &name);
		SharedConstLyricsAudioTag getLyricsTagPointer(const std::string_view &name) const;
        std::optional<types::Lyrics> getLyricsTagOptionalByLang(std::string language) const;
        std::optional<types::Lyrics> getLyricsTagOptional(const std::string_view &name) const;
        types::Lyrics getLyricsTagByLang(std::string language) const;
        types::Lyrics getLyricsTag(const std::string_view &name) const;
        bool setLyricsTagByLang(const std::string & language, const types::Lyrics &lyrics);
		bool setLyricsTag(const std::string_view & name, const types::Lyrics &lyrics);

		SharedImageAudioTag getImageTagPointer(const std::string_view &name);
		SharedImageAudioTag getImageTagPointer(ImageTag::ImageType imageType);
		SharedConstImageAudioTag getImageTagPointer(const std::string_view &name) const;
		SharedConstImageAudioTag getImageTagPointer(ImageTag::ImageType imageType) const;
        std::optional<types::Image> getImageTagOptional(const std::string_view &name) const;
        std::optional<types::Image> getImageTagOptional(ImageTag::ImageType imageType) const;
        types::Image getImageTag(const std::string_view &name) const;
        types::Image getImageTag(ImageTag::ImageType imageType) const;
        bool setImageTag(const std::string_view & name, const types::Image &image);
		bool setImageTag(const std::string_view & name, types::Image &&image);
		bool setImageTag(ImageTag::ImageType imageType, const types::Image &image);
		bool setImageTag(ImageTag::ImageType imageType, types::Image &&image);

		SharedConstISRCAudioTag getISRCTagPointer(const std::string_view &name) const;
		SharedISRCAudioTag getISRCTagPointer(const std::string_view &name);
        std::optional<types::ISRC> getISRCTagOptional(const std::string_view &name) const;
        types::ISRC getISRCTag(const std::string_view &name) const;
        bool setISRCTag(const std::string_view &name, const types::ISRC &isrc);

        SharedConstBarcodeAudioTag getBarcodeTagPointer(const std::string_view &name) const;
        SharedBarcodeAudioTag getBarcodeTagPointer(const std::string_view &name);
        std::optional<types::Barcode> getBarcodeTagOptional(const std::string_view &name) const;
        types::Barcode getBarcodeTag(const std::string_view &name) const;
        bool setBarcodeTag(const std::string_view &name, const types::Barcode &barcode);






        SharedConstStringAudioTag getAlbumPointer() const;
        SharedStringAudioTag getAlbumPointer();
        std::optional<std::string> getAlbumOptional() const;
        std::string getAlbum() const;
        bool setAlbum(const std::string& album);


        SharedConstStringAudioTag getAlbumArtistPointer() const;
        SharedStringAudioTag getAlbumArtistPointer();
        std::optional<std::string> getAlbumArtistOptional() const;
        std::string getAlbumArtist() const;
        bool setAlbumArtist(const std::string& albumArtist);


        SharedConstStringAudioTag getAlbumArtistSortPointer() const;
        SharedStringAudioTag getAlbumArtistSortPointer();
        std::optional<std::string> getAlbumArtistSortOptional() const;
        std::string getAlbumArtistSort() const;
        bool setAlbumArtistSort(const std::string& albumArtistSort);


        SharedConstStringAudioTag getAlbumSortPointer() const;
        SharedStringAudioTag getAlbumSortPointer();
        std::optional<std::string> getAlbumSortOptional() const;
        std::string getAlbumSort() const;
        bool setAlbumSort(const std::string& albumSort);


        SharedConstStringAudioTag getArrangerPointer() const;
        SharedStringAudioTag getArrangerPointer();
        std::optional<std::string> getArrangerOptional() const;
        std::string getArranger() const;
        bool setArranger(const std::string& arranger);


        SharedConstStringAudioTag getArtistPointer() const;
        SharedStringAudioTag getArtistPointer();
        std::optional<std::string> getArtistOptional() const;
        std::string getArtist() const;
        bool setArtist(const std::string& artist);


        SharedConstStringAudioTag getArtistSortPointer() const;
        SharedStringAudioTag getArtistSortPointer();
        std::optional<std::string> getArtistSortOptional() const;
        std::string getArtistSort() const;
        bool setArtistSort(const std::string& artistSort);


        SharedConstStringAudioTag getCommentPointer() const;
        SharedStringAudioTag getCommentPointer();
        std::optional<std::string> getCommentOptional() const;
        std::string getComment() const;
        bool setComment(const std::string& comment);


        SharedConstStringAudioTag getComposerPointer() const;
        SharedStringAudioTag getComposerPointer();
        std::optional<std::string> getComposerOptional() const;
        std::string getComposer() const;
        bool setComposer(const std::string& composer);


        SharedConstStringAudioTag getComposerSortPointer() const;
        SharedStringAudioTag getComposerSortPointer();
        std::optional<std::string> getComposerSortOptional() const;
        std::string getComposerSort() const;
        bool setComposerSort(const std::string& composerSort);


        SharedConstStringAudioTag getConductorPointer() const;
        SharedStringAudioTag getConductorPointer();
        std::optional<std::string> getConductorOptional() const;
        std::string getConductor() const;
        bool setConductor(const std::string& conductor);


        SharedConstStringAudioTag getContentGroupPointer() const;
        SharedStringAudioTag getContentGroupPointer();
        std::optional<std::string> getContentGroupOptional() const;
        std::string getContentGroup() const;
        bool setContentGroup(const std::string& contentGroup);


        SharedConstStringAudioTag getCopyrightPointer() const;
        SharedStringAudioTag getCopyrightPointer();
        std::optional<std::string> getCopyrightOptional() const;
        std::string getCopyright() const;
        bool setCopyright(const std::string& copyright);


        SharedConstStringAudioTag getEngineerPointer() const;
        SharedStringAudioTag getEngineerPointer();
        std::optional<std::string> getEngineerOptional() const;
        std::string getEngineer() const;
        bool setEngineer(const std::string& engineer);


        SharedConstStringAudioTag getEncodedBYPointer() const;
        SharedStringAudioTag getEncodedBYPointer();
        std::optional<std::string> getEncodedBYOptional() const;
        std::string getEncodedBY() const;
        bool setEncodedBY(const std::string& encodedBY);


        SharedConstStringAudioTag getEncoderSettingsPointer() const;
        SharedStringAudioTag getEncoderSettingsPointer();
        std::optional<std::string> getEncoderSettingsOptional() const;
        std::string getEncoderSettings() const;
        bool setEncoderSettings(const std::string& encoderSettings);


        SharedConstStringAudioTag getGenrePointer() const;
        SharedStringAudioTag getGenrePointer();
        std::optional<std::string> getGenreOptional() const;
        std::string getGenre() const;
        bool setGenre(const std::string& genre);


        SharedConstStringAudioTag getInitialKeyPointer() const;
        SharedStringAudioTag getInitialKeyPointer();
        std::optional<std::string> getInitialKeyOptional() const;
        std::string getInitialKey() const;
        bool setInitialKey(const std::string& initialKey);


        SharedConstStringAudioTag getLyricistPointer() const;
        SharedStringAudioTag getLyricistPointer();
        std::optional<std::string> getLyricistOptional() const;
        std::string getLyricist() const;
        bool setLyricist(const std::string& lyricist);


        SharedConstStringAudioTag getMixDJPointer() const;
        SharedStringAudioTag getMixDJPointer();
        std::optional<std::string> getMixDJOptional() const;
        std::string getMixDJ() const;
        bool setMixDJ(const std::string& mixDJ);


        SharedConstStringAudioTag getMixEngineerPointer() const;
        SharedStringAudioTag getMixEngineerPointer();
        std::optional<std::string> getMixEngineerOptional() const;
        std::string getMixEngineer() const;
        bool setMixEngineer(const std::string& mixEngineer);


        SharedConstStringAudioTag getMoodPointer() const;
        SharedStringAudioTag getMoodPointer();
        std::optional<std::string> getMoodOptional() const;
        std::string getMood() const;
        bool setMood(const std::string& mood);


        SharedConstStringAudioTag getOriginalLyricistPointer() const;
        SharedStringAudioTag getOriginalLyricistPointer();
        std::optional<std::string> getOriginalLyricistOptional() const;
        std::string getOriginalLyricist() const;
        bool setOriginalLyricist(const std::string& originalLyricist);


        SharedConstStringAudioTag getOriginalAlbumPointer() const;
        SharedStringAudioTag getOriginalAlbumPointer();
        std::optional<std::string> getOriginalAlbumOptional() const;
        std::string getOriginalAlbum() const;
        bool setOriginalAlbum(const std::string& originalAlbum);


        SharedConstStringAudioTag getOriginalArtistPointer() const;
        SharedStringAudioTag getOriginalArtistPointer();
        std::optional<std::string> getOriginalArtistOptional() const;
        std::string getOriginalArtist() const;
        bool setOriginalArtist(const std::string& originalArtist);


        SharedConstStringAudioTag getProducerPointer() const;
        SharedStringAudioTag getProducerPointer();
        std::optional<std::string> getProducerOptional() const;
        std::string getProducer() const;
        bool setProducer(const std::string& producer);


        SharedConstStringAudioTag getPublisherPointer() const;
        SharedStringAudioTag getPublisherPointer();
        std::optional<std::string> getPublisherOptional() const;
        std::string getPublisher() const;
        bool setPublisher(const std::string& publisher);


        SharedConstStringAudioTag getRadioStationPointer() const;
        SharedStringAudioTag getRadioStationPointer();
        std::optional<std::string> getRadioStationOptional() const;
        std::string getRadioStation() const;
        bool setRadioStation(const std::string& radioStation);


        SharedConstStringAudioTag getRadioStationOwnerPointer() const;
        SharedStringAudioTag getRadioStationOwnerPointer();
        std::optional<std::string> getRadioStationOwnerOptional() const;
        std::string getRadioStationOwner() const;
        bool setRadioStationOwner(const std::string& radioStationOwner);


        SharedConstStringAudioTag getRemixerPointer() const;
        SharedStringAudioTag getRemixerPointer();
        std::optional<std::string> getRemixerOptional() const;
        std::string getRemixer() const;
        bool setRemixer(const std::string& remixer);


        SharedConstStringAudioTag getSetSubtitlePointer() const;
        SharedStringAudioTag getSetSubtitlePointer();
        std::optional<std::string> getSetSubtitleOptional() const;
        std::string getSetSubtitle() const;
        bool setSetSubtitle(const std::string& setSubtitle);


        SharedConstStringAudioTag getSubtitlePointer() const;
        SharedStringAudioTag getSubtitlePointer();
        std::optional<std::string> getSubtitleOptional() const;
        std::string getSubtitle() const;
        bool setSubtitle(const std::string& subtitle);


        SharedConstStringAudioTag getTitlePointer() const;
        SharedStringAudioTag getTitlePointer();
        std::optional<std::string> getTitleOptional() const;
        std::string getTitle() const;
        bool setTitle(const std::string& title);


        SharedConstStringAudioTag getTitleSortPointer() const;
        SharedStringAudioTag getTitleSortPointer();
        std::optional<std::string> getTitleSortOptional() const;
        std::string getTitleSort() const;
        bool setTitleSort(const std::string& titleSort);


        SharedConstStringAudioTag getWWWCommercialPointer() const;
        SharedStringAudioTag getWWWCommercialPointer();
        std::optional<std::string> getWWWCommercialOptional() const;
        std::string getWWWCommercial() const;
        bool setWWWCommercial(const std::string& wWWCommercial);


        SharedConstStringAudioTag getWWWCopyrightPointer() const;
        SharedStringAudioTag getWWWCopyrightPointer();
        std::optional<std::string> getWWWCopyrightOptional() const;
        std::string getWWWCopyright() const;
        bool setWWWCopyright(const std::string& wWWCopyright);


        SharedConstStringAudioTag getWWWFilePointer() const;
        SharedStringAudioTag getWWWFilePointer();
        std::optional<std::string> getWWWFileOptional() const;
        std::string getWWWFile() const;
        bool setWWWFile(const std::string& wWWFile);


        SharedConstStringAudioTag getWWWArtistPointer() const;
        SharedStringAudioTag getWWWArtistPointer();
        std::optional<std::string> getWWWArtistOptional() const;
        std::string getWWWArtist() const;
        bool setWWWArtist(const std::string& wWWArtist);


        SharedConstStringAudioTag getWWWFileSourcePointer() const;
        SharedStringAudioTag getWWWFileSourcePointer();
        std::optional<std::string> getWWWFileSourceOptional() const;
        std::string getWWWFileSource() const;
        bool setWWWFileSource(const std::string& wWWFileSource);


        SharedConstStringAudioTag getWWWPaymentPointer() const;
        SharedStringAudioTag getWWWPaymentPointer();
        std::optional<std::string> getWWWPaymentOptional() const;
        std::string getWWWPayment() const;
        bool setWWWPayment(const std::string& wWWPayment);


        SharedConstStringAudioTag getWWWPodcastPointer() const;
        SharedStringAudioTag getWWWPodcastPointer();
        std::optional<std::string> getWWWPodcastOptional() const;
        std::string getWWWPodcast() const;
        bool setWWWPodcast(const std::string& wWWPodcast);


        SharedConstStringAudioTag getWWWPublisherPointer() const;
        SharedStringAudioTag getWWWPublisherPointer();
        std::optional<std::string> getWWWPublisherOptional() const;
        std::string getWWWPublisher() const;
        bool setWWWPublisher(const std::string& wWWPublisher);


        SharedConstStringAudioTag getWWWRadioPagePointer() const;
        SharedStringAudioTag getWWWRadioPagePointer();
        std::optional<std::string> getWWWRadioPageOptional() const;
        std::string getWWWRadioPage() const;
        bool setWWWRadioPage(const std::string& wWWRadioPage);


        SharedConstNumberAudioTag getBPMPointer() const;
        SharedNumberAudioTag getBPMPointer();
        std::optional<std::uint32_t> getBPMOptional() const;
        std::uint32_t getBPM() const;
        bool setBPM(std::uint32_t bPM);


        SharedConstNumberAudioTag getDiscNumberPointer() const;
        SharedNumberAudioTag getDiscNumberPointer();
        std::optional<std::uint32_t> getDiscNumberOptional() const;
        std::uint32_t getDiscNumber() const;
        bool setDiscNumber(std::uint32_t discNumber);


        SharedConstNumberAudioTag getTotalDiscNumberPointer() const;
        SharedNumberAudioTag getTotalDiscNumberPointer();
        std::optional<std::uint32_t> getTotalDiscNumberOptional() const;
        std::uint32_t getTotalDiscNumber() const;
        bool setTotalDiscNumber(std::uint32_t totalDiscNumber);


        SharedConstNumberAudioTag getTotalTrackNumberPointer() const;
        SharedNumberAudioTag getTotalTrackNumberPointer();
        std::optional<std::uint32_t> getTotalTrackNumberOptional() const;
        std::uint32_t getTotalTrackNumber() const;
        bool setTotalTrackNumber(std::uint32_t totalTrackNumber);


        SharedConstNumberAudioTag getTrackNumberPointer() const;
        SharedNumberAudioTag getTrackNumberPointer();
        std::optional<std::uint32_t> getTrackNumberOptional() const;
        std::uint32_t getTrackNumber() const;
        bool setTrackNumber(std::uint32_t trackNumber);


		std::uint32_t getYear() const;
		bool setYear(std::uint32_t year);


		std::uint32_t getOriginalYear() const;
		bool setOriginalYear(std::uint32_t originalYear);


        SharedConstDateAudioTag getDatePointer() const;
        SharedDateAudioTag getDatePointer();
        std::optional<types::Date> getDateOptional() const;
        types::Date getDate() const;
        bool setDate(const types::Date& date);


        SharedConstDateAudioTag getEncodingDatePointer() const;
        SharedDateAudioTag getEncodingDatePointer();
        std::optional<types::Date> getEncodingDateOptional() const;
        types::Date getEncodingDate() const;
        bool setEncodingDate(const types::Date& encodingDate);


        SharedConstDateAudioTag getOriginalDatePointer() const;
        SharedDateAudioTag getOriginalDatePointer();
        std::optional<types::Date> getOriginalDateOptional() const;
        types::Date getOriginalDate() const;
        bool setOriginalDate(const types::Date& originalDate);


        SharedConstLyricsAudioTag getLyricsEngPointer() const;
        SharedLyricsAudioTag getLyricsEngPointer();
        std::optional<types::Lyrics> getLyricsEngOptional() const;
        types::Lyrics getLyricsEng() const;
        bool setLyricsEng(const types::Lyrics& lyricsEng);


        SharedConstImageAudioTag getImageOtherPointer() const;
        SharedImageAudioTag getImageOtherPointer();
        std::optional<types::Image> getImageOtherOptional() const;
        types::Image getImageOther() const;
        bool setImageOther(const types::Image& imageOther);
        bool setImageOther(types::Image&& imageOther);


        SharedConstImageAudioTag getImageIConPointer() const;
        SharedImageAudioTag getImageIConPointer();
        std::optional<types::Image> getImageIConOptional() const;
        types::Image getImageICon() const;
        bool setImageICon(const types::Image& imageICon);
        bool setImageICon(types::Image&& imageICon);


        SharedConstImageAudioTag getImageOtherIconPointer() const;
        SharedImageAudioTag getImageOtherIconPointer();
        std::optional<types::Image> getImageOtherIconOptional() const;
        types::Image getImageOtherIcon() const;
        bool setImageOtherIcon(const types::Image& imageOtherIcon);
        bool setImageOtherIcon(types::Image&& imageOtherIcon);


        SharedConstImageAudioTag getImageCoverFrontPointer() const;
        SharedImageAudioTag getImageCoverFrontPointer();
        std::optional<types::Image> getImageCoverFrontOptional() const;
        types::Image getImageCoverFront() const;
        bool setImageCoverFront(const types::Image& imageCoverFront);
        bool setImageCoverFront(types::Image&& imageCoverFront);


        SharedConstImageAudioTag getImageCoverBackPointer() const;
        SharedImageAudioTag getImageCoverBackPointer();
        std::optional<types::Image> getImageCoverBackOptional() const;
        types::Image getImageCoverBack() const;
        bool setImageCoverBack(const types::Image& imageCoverBack);
        bool setImageCoverBack(types::Image&& imageCoverBack);


        SharedConstImageAudioTag getImageLeafletPointer() const;
        SharedImageAudioTag getImageLeafletPointer();
        std::optional<types::Image> getImageLeafletOptional() const;
        types::Image getImageLeaflet() const;
        bool setImageLeaflet(const types::Image& imageLeaflet);
        bool setImageLeaflet(types::Image&& imageLeaflet);


        SharedConstImageAudioTag getImageMediaPointer() const;
        SharedImageAudioTag getImageMediaPointer();
        std::optional<types::Image> getImageMediaOptional() const;
        types::Image getImageMedia() const;
        bool setImageMedia(const types::Image& imageMedia);
        bool setImageMedia(types::Image&& imageMedia);


        SharedConstImageAudioTag getImageLeadArtistPointer() const;
        SharedImageAudioTag getImageLeadArtistPointer();
        std::optional<types::Image> getImageLeadArtistOptional() const;
        types::Image getImageLeadArtist() const;
        bool setImageLeadArtist(const types::Image& imageLeadArtist);
        bool setImageLeadArtist(types::Image&& imageLeadArtist);


        SharedConstImageAudioTag getImageArtistPointer() const;
        SharedImageAudioTag getImageArtistPointer();
        std::optional<types::Image> getImageArtistOptional() const;
        types::Image getImageArtist() const;
        bool setImageArtist(const types::Image& imageArtist);
        bool setImageArtist(types::Image&& imageArtist);


        SharedConstImageAudioTag getImageConductorPointer() const;
        SharedImageAudioTag getImageConductorPointer();
        std::optional<types::Image> getImageConductorOptional() const;
        types::Image getImageConductor() const;
        bool setImageConductor(const types::Image& imageConductor);
        bool setImageConductor(types::Image&& imageConductor);


        SharedConstImageAudioTag getImageBandPointer() const;
        SharedImageAudioTag getImageBandPointer();
        std::optional<types::Image> getImageBandOptional() const;
        types::Image getImageBand() const;
        bool setImageBand(const types::Image& imageBand);
        bool setImageBand(types::Image&& imageBand);


        SharedConstImageAudioTag getImageComposerPointer() const;
        SharedImageAudioTag getImageComposerPointer();
        std::optional<types::Image> getImageComposerOptional() const;
        types::Image getImageComposer() const;
        bool setImageComposer(const types::Image& imageComposer);
        bool setImageComposer(types::Image&& imageComposer);


        SharedConstImageAudioTag getImageLyricistPointer() const;
        SharedImageAudioTag getImageLyricistPointer();
        std::optional<types::Image> getImageLyricistOptional() const;
        types::Image getImageLyricist() const;
        bool setImageLyricist(const types::Image& imageLyricist);
        bool setImageLyricist(types::Image&& imageLyricist);


        SharedConstImageAudioTag getImageRecordingLocationPointer() const;
        SharedImageAudioTag getImageRecordingLocationPointer();
        std::optional<types::Image> getImageRecordingLocationOptional() const;
        types::Image getImageRecordingLocation() const;
        bool setImageRecordingLocation(const types::Image& imageRecordingLocation);
        bool setImageRecordingLocation(types::Image&& imageRecordingLocation);


        SharedConstImageAudioTag getImageDuringRecordingPointer() const;
        SharedImageAudioTag getImageDuringRecordingPointer();
        std::optional<types::Image> getImageDuringRecordingOptional() const;
        types::Image getImageDuringRecording() const;
        bool setImageDuringRecording(const types::Image& imageDuringRecording);
        bool setImageDuringRecording(types::Image&& imageDuringRecording);


        SharedConstImageAudioTag getImageDuringPerformancePointer() const;
        SharedImageAudioTag getImageDuringPerformancePointer();
        std::optional<types::Image> getImageDuringPerformanceOptional() const;
        types::Image getImageDuringPerformance() const;
        bool setImageDuringPerformance(const types::Image& imageDuringPerformance);
        bool setImageDuringPerformance(types::Image&& imageDuringPerformance);


        SharedConstImageAudioTag getImageVideoCapturePointer() const;
        SharedImageAudioTag getImageVideoCapturePointer();
        std::optional<types::Image> getImageVideoCaptureOptional() const;
        types::Image getImageVideoCapture() const;
        bool setImageVideoCapture(const types::Image& imageVideoCapture);
        bool setImageVideoCapture(types::Image&& imageVideoCapture);


        SharedConstImageAudioTag getImageABrightColouredFishPointer() const;
        SharedImageAudioTag getImageABrightColouredFishPointer();
        std::optional<types::Image> getImageABrightColouredFishOptional() const;
        types::Image getImageABrightColouredFish() const;
        bool setImageABrightColouredFish(const types::Image& imageABrightColouredFish);
        bool setImageABrightColouredFish(types::Image&& imageABrightColouredFish);


        SharedConstImageAudioTag getImageIllustrationPointer() const;
        SharedImageAudioTag getImageIllustrationPointer();
        std::optional<types::Image> getImageIllustrationOptional() const;
        types::Image getImageIllustration() const;
        bool setImageIllustration(const types::Image& imageIllustration);
        bool setImageIllustration(types::Image&& imageIllustration);


        SharedConstImageAudioTag getImageBandLogoPointer() const;
        SharedImageAudioTag getImageBandLogoPointer();
        std::optional<types::Image> getImageBandLogoOptional() const;
        types::Image getImageBandLogo() const;
        bool setImageBandLogo(const types::Image& imageBandLogo);
        bool setImageBandLogo(types::Image&& imageBandLogo);


        SharedConstImageAudioTag getImagePublisherLogoPointer() const;
        SharedImageAudioTag getImagePublisherLogoPointer();
        std::optional<types::Image> getImagePublisherLogoOptional() const;
        types::Image getImagePublisherLogo() const;
        bool setImagePublisherLogo(const types::Image& imagePublisherLogo);
        bool setImagePublisherLogo(types::Image&& imagePublisherLogo);


        SharedConstISRCAudioTag getISRCPointer() const;
        SharedISRCAudioTag getISRCPointer();
        std::optional<types::ISRC> getISRCOptional() const;
        types::ISRC getISRC() const;
        bool setISRC(const types::ISRC& iSRC);


        SharedConstBarcodeAudioTag getBarcodePointer() const;
        SharedBarcodeAudioTag getBarcodePointer();
        std::optional<types::Barcode> getBarcodeOptional() const;
        types::Barcode getBarcode() const;
        bool setBarcode(const types::Barcode& barcode);

	private:
		template < class Type >
		std::shared_ptr<Type> getTypeTagPointer(const std::string_view &name) {
			SharedAudioTag audioTag = getTagPointer(name);
			if (audioTag != nullptr)
				return std::dynamic_pointer_cast<Type>(audioTag);
			return std::shared_ptr<Type>();
		}

		template < class Type >
		std::shared_ptr<const Type> getTypeTagPointer(const std::string_view &name) const {
				SharedConstAudioTag audioTag = getTagPointer(name);
				if (audioTag != nullptr)
					return std::dynamic_pointer_cast<const Type>(audioTag);
				return std::shared_ptr<const Type>();
		}


		using MapType = std::map<std::string, SharedAudioTag, std::less<>>;
		using SetType = std::unordered_set<std::string_view>;

		MapType tagMap;
		static const SetType TAG_NAMES;
		static const SetType STRING_TAG_NAMES;
		static const SetType NUMBER_TAG_NAMES;
		static const SetType DATE_TAG_NAMES;
		static const SetType IMAGE_TAG_NAMES;
	};








	class TagMap::const_iterator {
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
		Tag::Type getType() const;

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
	class TagMap::iterator : public const_iterator {
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