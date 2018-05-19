#pragma once
#include <memory>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <string_view>
#include "Date.hpp"
#include "Image.hpp"

using namespace std::literals;

namespace tag {
	const std::vector<std::string> GENRES = {
		"Blues"s,
		"Classic Rock"s,
		"Country"s,
		"Dance"s,
		"Disco"s,
		"Funk"s,
		"Grunge"s,
		"Hip-Hop"s,
		"Jazz"s,
		"Metal"s,
		"New Age"s,
		"Oldies"s,
		"Other"s,
		"Pop"s,
		"R&B"s,
		"Rap"s,
		"Reggae"s,
		"Rock"s,
		"Techno"s,
		"Industrial"s,
		"Alternative"s,
		"Ska"s,
		"Death Metal"s,
		"Pranks"s,
		"Soundtrack"s,
		"Euro-Techno"s,
		"Ambient"s,
		"Trip-Hop"s,
		"Vocal"s,
		"Jazz+Funk"s,
		"Fusion"s,
		"Trance"s,
		"Classical"s,
		"Instrumental"s,
		"Acid"s,
		"House"s,
		"Game"s,
		"Sound Clip"s,
		"Gospel"s,
		"Noise"s,
		"Alternative Rock"s,
		"Bass"s,
		"Soul"s,
		"Punk"s,
		"Space"s,
		"Meditative"s,
		"Instrumental Pop"s,
		"Instrumental Rock"s,
		"Ethnic"s,
		"Gothic"s,
		"Darkwave"s,
		"Techno-Industrial"s,
		"Electronic"s,
		"Pop-Folk"s,
		"Eurodance"s,
		"Dream"s,
		"Southern Rock"s,
		"Comedy"s,
		"Cult"s,
		"Gangsta"s,
		"Top 40"s,
		"Christian Rap"s,
		"Pop/Funk"s,
		"Jungle"s,
		"Native US"s,
		"Cabaret"s,
		"New Wave"s,
		"Psychadelic"s,
		"Rave"s,
		"Showtunes"s,
		"Trailer"s,
		"Lo-Fi"s,
		"Tribal"s,
		"Acid Punk"s,
		"Acid Jazz"s,
		"Polka"s,
		"Retro"s,
		"Musical"s,
		"Rock & Roll"s,
		"Hard Rock"s,
		"Folk"s,
		"Folk-Rock"s,
		"National Folk"s,
		"Swing"s,
		"Fast Fusion"s,
		"Bebob"s,
		"Latin"s,
		"Revival"s,
		"Celtic"s,
		"Bluegrass"s,
		"Avantgarde"s,
		"Gothic Rock"s,
		"Progressive Rock"s,
		"Psychedelic Rock"s,
		"Symphonic Rock"s,
		"Slow Rock"s,
		"Big Band"s,
		"Chorus"s,
		"Easy Listening"s,
		"Acoustic"s,
		"Humour"s,
		"Speech"s,
		"Chanson"s,
		"Opera"s,
		"Chamber Music"s,
		"Sonata"s,
		"Symphony"s,
		"Booty Bass"s,
		"Primus"s,
		"Porn Groove"s,
		"Satire"s,
		"Slow Jam"s,
		"Club"s,
		"Tango"s,
		"Samba"s,
		"Folklore"s,
		"Ballad"s,
		"Power Ballad"s,
		"Rhythmic Soul"s,
		"Freestyle"s,
		"Duet"s,
		"Punk Rock"s,
		"Drum Solo"s,
		"Acapella"s,
		"Euro-House"s,
		"Dance Hall"s,
		"Goa"s,
		"Drum & Bass"s,
		"Club - House"s,
		"Hardcore"s,
		"Terror"s,
		"Indie"s,
		"BritPop"s,
		"Negerpunk"s,
		"Polsk Punk"s,
		"Beat"s,
		"Christian Gangsta Rap"s,
		"Heavy Metal"s,
		"Black Metal"s,
		"Crossover"s,
		"Contemporary Christian"s,
		"Christian Rock"s,
		"Merengue"s,
		"Salsa"s,
		"Thrash Metal"s,
		"Anime"s,
		"JPop"s,
		"Synthpop"s,
		"Unknown"s
	};
	const std::unordered_map<std::string, std::size_t> GENRES_INDICES = {
		std::pair<std::string, std::size_t>("Blues"s, 0),
		std::pair<std::string, std::size_t>("Classic Rock"s, 1),
		std::pair<std::string, std::size_t>("Country"s, 2),
		std::pair<std::string, std::size_t>("Dance"s, 3),
		std::pair<std::string, std::size_t>("Disco"s, 4),
		std::pair<std::string, std::size_t>("Funk"s, 5),
		std::pair<std::string, std::size_t>("Grunge"s, 6),
		std::pair<std::string, std::size_t>("Hip-Hop"s, 7),
		std::pair<std::string, std::size_t>("Jazz"s, 8),
		std::pair<std::string, std::size_t>("Metal"s, 9),
		std::pair<std::string, std::size_t>("New Age"s, 10),
		std::pair<std::string, std::size_t>("Oldies"s, 11),
		std::pair<std::string, std::size_t>("Other"s, 12),
		std::pair<std::string, std::size_t>("Pop"s, 13),
		std::pair<std::string, std::size_t>("R&B"s, 14),
		std::pair<std::string, std::size_t>("Rap"s, 15),
		std::pair<std::string, std::size_t>("Reggae"s, 16),
		std::pair<std::string, std::size_t>("Rock"s, 17),
		std::pair<std::string, std::size_t>("Techno"s, 18),
		std::pair<std::string, std::size_t>("Industrial"s, 19),
		std::pair<std::string, std::size_t>("Alternative"s, 20),
		std::pair<std::string, std::size_t>("Ska"s, 21),
		std::pair<std::string, std::size_t>("Death Metal"s, 22),
		std::pair<std::string, std::size_t>("Pranks"s, 23),
		std::pair<std::string, std::size_t>("Soundtrack"s, 24),
		std::pair<std::string, std::size_t>("Euro-Techno"s, 25),
		std::pair<std::string, std::size_t>("Ambient"s, 26),
		std::pair<std::string, std::size_t>("Trip-Hop"s, 27),
		std::pair<std::string, std::size_t>("Vocal"s, 28),
		std::pair<std::string, std::size_t>("Jazz+Funk"s, 29),
		std::pair<std::string, std::size_t>("Fusion"s, 30),
		std::pair<std::string, std::size_t>("Trance"s, 31),
		std::pair<std::string, std::size_t>("Classical"s, 32),
		std::pair<std::string, std::size_t>("Instrumental"s, 33),
		std::pair<std::string, std::size_t>("Acid"s, 34),
		std::pair<std::string, std::size_t>("House"s, 35),
		std::pair<std::string, std::size_t>("Game"s, 36),
		std::pair<std::string, std::size_t>("Sound Clip"s, 37),
		std::pair<std::string, std::size_t>("Gospel"s, 38),
		std::pair<std::string, std::size_t>("Noise"s, 39),
		std::pair<std::string, std::size_t>("Alternative Rock"s, 40),
		std::pair<std::string, std::size_t>("Bass"s, 41),
		std::pair<std::string, std::size_t>("Soul"s, 42),
		std::pair<std::string, std::size_t>("Punk"s, 43),
		std::pair<std::string, std::size_t>("Space"s, 44),
		std::pair<std::string, std::size_t>("Meditative"s, 45),
		std::pair<std::string, std::size_t>("Instrumental Pop"s, 46),
		std::pair<std::string, std::size_t>("Instrumental Rock"s, 47),
		std::pair<std::string, std::size_t>("Ethnic"s, 48),
		std::pair<std::string, std::size_t>("Gothic"s, 49),
		std::pair<std::string, std::size_t>("Darkwave"s, 50),
		std::pair<std::string, std::size_t>("Techno-Industrial"s, 51),
		std::pair<std::string, std::size_t>("Electronic"s, 52),
		std::pair<std::string, std::size_t>("Pop-Folk"s, 53),
		std::pair<std::string, std::size_t>("Eurodance"s, 54),
		std::pair<std::string, std::size_t>("Dream"s, 55),
		std::pair<std::string, std::size_t>("Southern Rock"s, 56),
		std::pair<std::string, std::size_t>("Comedy"s, 57),
		std::pair<std::string, std::size_t>("Cult"s, 58),
		std::pair<std::string, std::size_t>("Gangsta"s, 59),
		std::pair<std::string, std::size_t>("Top 40"s, 60),
		std::pair<std::string, std::size_t>("Christian Rap"s, 61),
		std::pair<std::string, std::size_t>("Pop/Funk"s, 62),
		std::pair<std::string, std::size_t>("Jungle"s, 63),
		std::pair<std::string, std::size_t>("Native US"s, 64),
		std::pair<std::string, std::size_t>("Cabaret"s, 65),
		std::pair<std::string, std::size_t>("New Wave"s, 66),
		std::pair<std::string, std::size_t>("Psychadelic"s, 67),
		std::pair<std::string, std::size_t>("Rave"s, 68),
		std::pair<std::string, std::size_t>("Showtunes"s, 69),
		std::pair<std::string, std::size_t>("Trailer"s, 70),
		std::pair<std::string, std::size_t>("Lo-Fi"s, 71),
		std::pair<std::string, std::size_t>("Tribal"s, 72),
		std::pair<std::string, std::size_t>("Acid Punk"s, 73),
		std::pair<std::string, std::size_t>("Acid Jazz"s, 74),
		std::pair<std::string, std::size_t>("Polka"s, 75),
		std::pair<std::string, std::size_t>("Retro"s, 76),
		std::pair<std::string, std::size_t>("Musical"s, 77),
		std::pair<std::string, std::size_t>("Rock & Roll"s, 78),
		std::pair<std::string, std::size_t>("Hard Rock"s, 79),
		std::pair<std::string, std::size_t>("Folk"s, 80),
		std::pair<std::string, std::size_t>("Folk-Rock"s, 81),
		std::pair<std::string, std::size_t>("National Folk"s, 82),
		std::pair<std::string, std::size_t>("Swing"s, 83),
		std::pair<std::string, std::size_t>("Fast Fusion"s, 84),
		std::pair<std::string, std::size_t>("Bebob"s, 85),
		std::pair<std::string, std::size_t>("Latin"s, 86),
		std::pair<std::string, std::size_t>("Revival"s, 87),
		std::pair<std::string, std::size_t>("Celtic"s, 88),
		std::pair<std::string, std::size_t>("Bluegrass"s, 89),
		std::pair<std::string, std::size_t>("Avantgarde"s, 90),
		std::pair<std::string, std::size_t>("Gothic Rock"s, 91),
		std::pair<std::string, std::size_t>("Progressive Rock"s, 92),
		std::pair<std::string, std::size_t>("Psychedelic Rock"s, 93),
		std::pair<std::string, std::size_t>("Symphonic Rock"s, 94),
		std::pair<std::string, std::size_t>("Slow Rock"s, 95),
		std::pair<std::string, std::size_t>("Big Band"s, 96),
		std::pair<std::string, std::size_t>("Chorus"s, 97),
		std::pair<std::string, std::size_t>("Easy Listening"s, 98),
		std::pair<std::string, std::size_t>("Acoustic"s, 99),
		std::pair<std::string, std::size_t>("Humour"s, 100),
		std::pair<std::string, std::size_t>("Speech"s, 101),
		std::pair<std::string, std::size_t>("Chanson"s, 102),
		std::pair<std::string, std::size_t>("Opera"s, 103),
		std::pair<std::string, std::size_t>("Chamber Music"s, 104),
		std::pair<std::string, std::size_t>("Sonata"s, 105),
		std::pair<std::string, std::size_t>("Symphony"s, 106),
		std::pair<std::string, std::size_t>("Booty Bass"s, 107),
		std::pair<std::string, std::size_t>("Primus"s, 108),
		std::pair<std::string, std::size_t>("Porn Groove"s, 109),
		std::pair<std::string, std::size_t>("Satire"s, 110),
		std::pair<std::string, std::size_t>("Slow Jam"s, 111),
		std::pair<std::string, std::size_t>("Club"s, 112),
		std::pair<std::string, std::size_t>("Tango"s, 113),
		std::pair<std::string, std::size_t>("Samba"s, 114),
		std::pair<std::string, std::size_t>("Folklore"s, 115),
		std::pair<std::string, std::size_t>("Ballad"s, 116),
		std::pair<std::string, std::size_t>("Power Ballad"s, 117),
		std::pair<std::string, std::size_t>("Rhythmic Soul"s, 118),
		std::pair<std::string, std::size_t>("Freestyle"s, 119),
		std::pair<std::string, std::size_t>("Duet"s, 120),
		std::pair<std::string, std::size_t>("Punk Rock"s, 121),
		std::pair<std::string, std::size_t>("Drum Solo"s, 122),
		std::pair<std::string, std::size_t>("Acapella"s, 123),
		std::pair<std::string, std::size_t>("Euro-House"s, 124),
		std::pair<std::string, std::size_t>("Dance Hall"s, 125),
		std::pair<std::string, std::size_t>("Goa"s, 126),
		std::pair<std::string, std::size_t>("Drum & Bass"s, 127),
		std::pair<std::string, std::size_t>("Club - House"s, 128),
		std::pair<std::string, std::size_t>("Hardcore"s, 129),
		std::pair<std::string, std::size_t>("Terror"s, 130),
		std::pair<std::string, std::size_t>("Indie"s, 131),
		std::pair<std::string, std::size_t>("BritPop"s, 132),
		std::pair<std::string, std::size_t>("Negerpunk"s, 133),
		std::pair<std::string, std::size_t>("Polsk Punk"s, 134),
		std::pair<std::string, std::size_t>("Beat"s, 135),
		std::pair<std::string, std::size_t>("Christian Gangsta Rap"s, 136),
		std::pair<std::string, std::size_t>("Heavy Metal"s, 137),
		std::pair<std::string, std::size_t>("Black Metal"s, 138),
		std::pair<std::string, std::size_t>("Crossover"s, 139),
		std::pair<std::string, std::size_t>("Contemporary Christian"s, 140),
		std::pair<std::string, std::size_t>("Christian Rock"s, 141),
		std::pair<std::string, std::size_t>("Merengue"s, 142),
		std::pair<std::string, std::size_t>("Salsa"s, 143),
		std::pair<std::string, std::size_t>("Thrash Metal"s, 144),
		std::pair<std::string, std::size_t>("Anime"s, 145),
		std::pair<std::string, std::size_t>("JPop"s, 146),
		std::pair<std::string, std::size_t>("Synthpop"s, 147),
		std::pair<std::string, std::size_t>("Unknown"s, 148)
	};

	class AudioTag {
	public:
		using SharedAudioTag = std::shared_ptr<AudioTag>;
		enum class Type {
			String,
			Number,
			Date,
			Image
		};
		explicit AudioTag(const std::string &name);
		virtual ~AudioTag();
		const std::string& getName() const noexcept;

		virtual Type getType() const noexcept = 0;
		virtual bool isNull() const noexcept = 0;
	private:
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
		explicit ImageAudioTag(const std::string name, const type::Image &image = type::Image());
		explicit ImageAudioTag(const std::string name, type::Image &&image);
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
}

namespace tag::string {
	std::string toString(AudioTag::Type type);
	std::string toString(ImageAudioTag::ImageType imageType);
}

