#pragma once
#include <memory>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <string_view>
#include <boost/algorithm/string.hpp>
#include "Date.hpp"
#include "Image.hpp"
#include "Lyrics.hpp"

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
			Lyrics
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
		explicit DateAudioTag(const std::string &name, const type::Date &date = type::Date());
		virtual Type getType() const noexcept override;
		virtual bool isNull() const noexcept override;

		const type::Date& getDate() const noexcept;
		type::Date& getDate() noexcept;
		void setDate(const type::Date date) noexcept;
	private:
		type::Date date;
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

		explicit ImageAudioTag(ImageType imageType, const type::Image &image = type::Image());
		explicit ImageAudioTag(ImageType imageType, type::Image &&image);
		explicit ImageAudioTag(const std::string &name, const type::Image &image = type::Image());
		explicit ImageAudioTag(const std::string &name, type::Image &&image);
		virtual Type getType() const noexcept override;
		virtual bool isNull() const noexcept override;
		
		const type::Image& getImage() const;
		type::Image& getImage();
		void setImage(const type::Image &image);
		void setImage(type::Image &&image);
	private:
		type::Image image;
	};
	using SharedImageAudioTag = std::shared_ptr<ImageAudioTag>;
	using SharedConstImageAudioTag = std::shared_ptr<const ImageAudioTag>;



	class LyricsAudioTag : public AudioTag {
	public:
		LyricsAudioTag(const std::string &language, const type::Lyrics &lyrics = type::Lyrics());
		LyricsAudioTag(const std::string &language, type::Lyrics &&lyrics);


		virtual Type getType() const noexcept override;
		virtual bool isNull() const noexcept override;

		const type::Lyrics& getLyrics() const;
		type::Lyrics& getLyrics();
		void setLyrics(const type::Lyrics &lyrics);
		void setLyrics(type::Lyrics &&lyrics);
	private:
		type::Lyrics lyrics;
		static const std::string LYRICS;
	};
	using SharedLyricsAudioTag = std::shared_ptr<LyricsAudioTag>;
	using SharedConstLyricsAudioTag = std::shared_ptr<const LyricsAudioTag>;
}

namespace tag::string {
	std::string toString(AudioTag::Type type);
	std::string toString(ImageAudioTag::ImageType imageType);
}

