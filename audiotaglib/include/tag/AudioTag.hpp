#pragma once
#include <memory>
#include <unordered_map>
#include <tag/types/Date.hpp>
#include <tag/types/Image.hpp>
#include <tag/types/Lyrics.hpp>
#include <tag/types/ISRC.hpp>

using namespace std::literals;


namespace tag {

	class AudioTag {
	public:
		using SharedAudioTag = std::shared_ptr<AudioTag>;
		enum class Type {
			String,
			Number,
			Date,
			Image,
			Lyrics,
			ISRC
		};
		AudioTag(const AudioTag&) = default;
		AudioTag(AudioTag&&) = default;
		virtual ~AudioTag();
		const std::string& getName() const noexcept;

		virtual Type getType() const noexcept = 0;
		virtual bool isNull() const noexcept = 0;
	protected:
		explicit AudioTag(const std::string &name);
	private:
		AudioTag & operator=(const AudioTag&) = delete;
		AudioTag & operator=(AudioTag&&) = delete;
		std::string name;
	};
	using SharedAudioTag = std::shared_ptr<AudioTag>;
	using SharedConstAudioTag = std::shared_ptr<const AudioTag>;



	class StringAudioTag : public AudioTag {
	public:
		explicit StringAudioTag(const std::string &name, const std::string &text = std::string());
		virtual Type getType() const noexcept override;
		virtual bool isNull() const noexcept override;

		const std::string& getText() const noexcept;
		std::string& getText() noexcept;
		void setText(const std::string &text);
	private:
		std::string text;
	};
	using SharedStringAudioTag = std::shared_ptr<StringAudioTag>;
	using SharedConstStringAudioTag = std::shared_ptr<const StringAudioTag>;




	class DateAudioTag : public AudioTag {
	public:
		explicit DateAudioTag(const std::string &name, const types::Date &date = types::Date());
		virtual Type getType() const noexcept override;
		virtual bool isNull() const noexcept override;

		const types::Date& getDate() const noexcept;
		types::Date& getDate() noexcept;
		void setDate(const types::Date date) noexcept;
	private:
		types::Date date;
	};
	using SharedDateAudioTag = std::shared_ptr<DateAudioTag>;
	using SharedConstDateAudioTag = std::shared_ptr<const DateAudioTag>;



	class NumberAudioTag : public AudioTag {
	public:
		explicit NumberAudioTag(const std::string &name, unsigned number = -1);
		virtual Type getType() const noexcept override;
		virtual bool isNull() const noexcept override;

		unsigned getNumber() const noexcept;
		void setNumber(unsigned number) noexcept;
	private:
		unsigned number;
	};
	using SharedNumberAudioTag = std::shared_ptr<NumberAudioTag>;
	using SharedConstNumberAudioTag = std::shared_ptr<const NumberAudioTag>;

	class ImageAudioTag : public AudioTag {
	public:
		enum class ImageType {
			Other, Icon, OtherIcon, CoverFront,
			CoverBack, Leaflet, Media,
			Artist, Conductor, Band,
			Composer, Lyricist, RecordingLocation,
			DuringRecording, DuringPerformance,
			VideoCapture, ABrightColouredFish,
			Illustration, BandLogo, PublisherLogo
		};

		explicit ImageAudioTag(ImageType imageType, const types::Image &image = types::Image());
		explicit ImageAudioTag(ImageType imageType, types::Image &&image);
		explicit ImageAudioTag(const std::string &name, const types::Image &image = types::Image());
		explicit ImageAudioTag(const std::string &name, types::Image &&image);
		virtual Type getType() const noexcept override;
		virtual bool isNull() const noexcept override;

		const types::Image& getImage() const;
		types::Image& getImage();
		void setImage(const types::Image &image);
		void setImage(types::Image &&image);
	private:
		types::Image image;
	};
	using SharedImageAudioTag = std::shared_ptr<ImageAudioTag>;
	using SharedConstImageAudioTag = std::shared_ptr<const ImageAudioTag>;



	class LyricsAudioTag : public AudioTag {
	public:
		LyricsAudioTag(const std::string &language, const types::Lyrics &lyrics = types::Lyrics());
		LyricsAudioTag(const std::string &language, types::Lyrics &&lyrics);


		virtual Type getType() const noexcept override;
		virtual bool isNull() const noexcept override;

		const types::Lyrics& getLyrics() const;
		types::Lyrics& getLyrics();
		void setLyrics(const types::Lyrics &lyrics);
		void setLyrics(types::Lyrics &&lyrics);
	private:
		types::Lyrics lyrics;
		static const std::string LYRICS;
	};
	using SharedLyricsAudioTag = std::shared_ptr<LyricsAudioTag>;
	using SharedConstLyricsAudioTag = std::shared_ptr<const LyricsAudioTag>;




	class ISRCAudioTag : public AudioTag {
	public:
		ISRCAudioTag(const types::ISRC &isrc = types::ISRC());

		virtual Type getType() const noexcept override;
		virtual bool isNull() const noexcept override;

		const types::ISRC& getISRC() const noexcept;
		types::ISRC& getISRC() noexcept;
		void setISRC(const types::ISRC &isrc) noexcept;

	private:
		types::ISRC isrc;
	};
	using SharedISRCAudioTag = std::shared_ptr<ISRCAudioTag>;
	using SharedConstISRCAudioTag = std::shared_ptr<const ISRCAudioTag>;
}

namespace tag::string {
	std::string toString(AudioTag::Type types);
	std::string toString(ImageAudioTag::ImageType imageType);
}

