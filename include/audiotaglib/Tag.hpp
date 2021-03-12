#pragma once
#include <audiotaglib/types/Date.hpp>
#include <audiotaglib/types/Image.hpp>
#include <audiotaglib/types/Lyrics.hpp>
#include <audiotaglib/types/ISRC.hpp>
#include <audiotaglib/types/Barcode.hpp>
#include <memory>
#include <unordered_map>
using namespace std::literals;


namespace audiotaglib {

	class Tag {
	public:
		enum class Type {
			String,
			Number,
			Date,
			Image,
			Lyrics,
			ISRC,
			Barcode
		};
		Tag(const Tag&) = default;
		Tag(Tag&&) = default;
		virtual ~Tag() = default;

		Tag & operator=(const Tag&) = delete;
		Tag & operator=(Tag&&) = delete;

		const std::string& getName() const noexcept;

		virtual Type getType() const noexcept = 0;
		virtual bool isEmpty() const noexcept = 0;
        virtual bool equals(const Tag &other) const = 0;
        bool equals(const Tag *other) const;
	protected:
		explicit Tag(const std::string &name);
	private:
		std::string name;
	};
	using SharedAudioTag = std::shared_ptr<Tag>;
	using SharedConstAudioTag = std::shared_ptr<const Tag>;



	class StringTag : public Tag {
	public:
		explicit StringTag(const std::string &name, const std::string &text = std::string());
		virtual Type getType() const noexcept override;
		virtual bool isEmpty() const noexcept override;
        virtual bool equals(const Tag &other) const override;

		const std::string& getText() const noexcept;
		std::string& getText() noexcept;
		void setText(const std::string &text);
        bool operator==(const StringTag &other) const;
        bool operator!=(const StringTag &other) const;
	private:
		std::string text;
	};
	using SharedStringAudioTag = std::shared_ptr<StringTag>;
	using SharedConstStringAudioTag = std::shared_ptr<const StringTag>;




	class DateTag : public Tag {
	public:
		explicit DateTag(const std::string &name, const types::Date &date = types::Date());
		virtual Type getType() const noexcept override;
		virtual bool isEmpty() const noexcept override;
        virtual bool equals(const Tag &other) const override;

		const types::Date& getDate() const noexcept;
		types::Date& getDate() noexcept;
		void setDate(const types::Date &date) noexcept;
        bool operator==(const DateTag &other) const;
        bool operator!=(const DateTag &other) const;
    private:
		types::Date date;
	};
	using SharedDateAudioTag = std::shared_ptr<DateTag>;
	using SharedConstDateAudioTag = std::shared_ptr<const DateTag>;



	class NumberTag : public Tag {
	public:
		explicit NumberTag(const std::string &name, std::uint32_t number = std::uint32_t(-1));
		virtual Type getType() const noexcept override;
		virtual bool isEmpty() const noexcept override;
        virtual bool equals(const Tag &other) const override;

		std::uint32_t getNumber() const noexcept;
		void setNumber(std::uint32_t number) noexcept;
        bool operator==(const NumberTag &other) const;
        bool operator!=(const NumberTag &other) const;
    private:
		std::uint32_t number;
	};
	using SharedNumberAudioTag = std::shared_ptr<NumberTag>;
	using SharedConstNumberAudioTag = std::shared_ptr<const NumberTag>;

	class ImageTag : public Tag {
	public:
		enum class ImageType {
			Other, Icon, OtherIcon, CoverFront,
			CoverBack, Leaflet, Media,
			LeadArtist, Artist, Conductor, Band,
			Composer, Lyricist, RecordingLocation,
			DuringRecording, DuringPerformance,
			VideoCapture, ABrightColouredFish,
			Illustration, BandLogo, PublisherLogo
		};

		explicit ImageTag(ImageType imageType, const types::Image &image = types::Image());
		explicit ImageTag(ImageType imageType, types::Image &&image);
		explicit ImageTag(const std::string &name, const types::Image &image = types::Image());
		explicit ImageTag(const std::string &name, types::Image &&image);
		virtual Type getType() const noexcept override;
		virtual bool isEmpty() const noexcept override;
        virtual bool equals(const Tag &other) const override;

		const types::Image& getImage() const;
		types::Image& getImage();
		void setImage(const types::Image &image);
		void setImage(types::Image &&image);
        bool operator==(const ImageTag &other) const;
        bool operator!=(const ImageTag &other) const;
    private:
		types::Image image;
	};
	using SharedImageAudioTag = std::shared_ptr<ImageTag>;
	using SharedConstImageAudioTag = std::shared_ptr<const ImageTag>;



	class LyricsTag : public Tag {
	public:
		explicit LyricsTag(const std::string &language, const types::Lyrics &lyrics = types::Lyrics());
		explicit LyricsTag(const std::string &language, types::Lyrics &&lyrics);
		virtual Type getType() const noexcept override;
		virtual bool isEmpty() const noexcept override;
        virtual bool equals(const Tag &other) const override;

		const types::Lyrics& getLyrics() const;
		types::Lyrics& getLyrics();
		void setLyrics(const types::Lyrics &lyrics);
		void setLyrics(types::Lyrics &&lyrics);
        bool operator==(const LyricsTag &other) const;
        bool operator!=(const LyricsTag &other) const;
    private:
		types::Lyrics lyrics;
		static const std::string LYRICS;
	};
	using SharedLyricsAudioTag = std::shared_ptr<LyricsTag>;
	using SharedConstLyricsAudioTag = std::shared_ptr<const LyricsTag>;




	class ISRCTag : public Tag {
	public:
		explicit ISRCTag(const types::ISRC &isrc = types::ISRC());
		virtual Type getType() const noexcept override;
		virtual bool isEmpty() const noexcept override;
        virtual bool equals(const Tag &other) const override;

		const types::ISRC& getISRC() const noexcept;
		types::ISRC& getISRC() noexcept;
		void setISRC(const types::ISRC &isrc) noexcept;
        bool operator==(const ISRCTag &other) const;
        bool operator!=(const ISRCTag &other) const;
    private:
		types::ISRC isrc;
	};
	using SharedISRCAudioTag = std::shared_ptr<ISRCTag>;
	using SharedConstISRCAudioTag = std::shared_ptr<const ISRCTag>;



    class BarcodeTag : public Tag {
    public:
        explicit BarcodeTag(const types::Barcode &barcode = types::Barcode());
        virtual Type getType() const noexcept override;
        virtual bool isEmpty() const noexcept override;
        virtual bool equals(const Tag &other) const override;

        const types::Barcode& getBarcode() const noexcept;
        types::Barcode& getBarcode() noexcept;
        void setBarcode(const types::Barcode &barcode) noexcept;
        bool operator==(const BarcodeTag &other) const;
        bool operator!=(const BarcodeTag &other) const;
    private:
        types::Barcode barcode;
    };
    using SharedBarcodeAudioTag = std::shared_ptr<BarcodeTag>;
    using SharedConstBarcodeAudioTag = std::shared_ptr<const BarcodeTag>;
}

namespace audiotaglib::string {
	std::string toString(Tag::Type types);
	std::string toString(ImageTag::ImageType imageType);
}

