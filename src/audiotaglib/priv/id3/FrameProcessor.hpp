#pragma once
#include <istream>
#include <unordered_map>
#include <audiotaglib/TagMap.hpp>

namespace audiotaglib::priv::id3 {
	class FrameProcessor {
	public:
		FrameProcessor(const std::string &name);
		virtual ~FrameProcessor();
		virtual void process(std::istream& readStream, TagMap &map, std::uint32_t size) const = 0;
	protected:
		std::string name;
	};
	using SharedFrameProcessor = std::shared_ptr<FrameProcessor>;


	class TextProcessor : public FrameProcessor {
	public:
		TextProcessor(const std::string &name);
		virtual void process(std::istream& readStream, TagMap &map, std::uint32_t size) const override;
	};


	class MultiStringTextProcessor : public FrameProcessor {
	public:
		MultiStringTextProcessor(const std::string &name);
		virtual void process(std::istream& readStream, TagMap &map, std::uint32_t size) const override;
	};


	class URLProcessor: public FrameProcessor{
	public:
		URLProcessor(const std::string &name);
		virtual void process(std::istream& readStream, TagMap &map, std::uint32_t size) const override;
	};


	class SingleNumberTextProcessor : public FrameProcessor {
	public:
		SingleNumberTextProcessor(const std::string &name);
		virtual void process(std::istream& readStream, TagMap &map, std::uint32_t size) const override;
	};


	class DoubleNumberTextProcessor : public FrameProcessor {
	public:
		DoubleNumberTextProcessor(const std::string &firstName, const std::string &secondName);
		virtual void process(std::istream& readStream, TagMap &map, std::uint32_t size) const override;
		std::string secondName;
	};


	class FullDateProcessor : public FrameProcessor {
	public:
		FullDateProcessor(const std::string &name);
		virtual void process(std::istream& readStream, TagMap &map, std::uint32_t size) const override;
	};


	class DateProcessor: public FrameProcessor {
	public:
		DateProcessor(const std::string &name);
		virtual void process(std::istream& readStream, TagMap &map, std::uint32_t size) const override;
	};


	class YearProcessor : public FrameProcessor {
	public:
		YearProcessor(const std::string &name);
		virtual void process(std::istream& readStream, TagMap &map, std::uint32_t size) const override;
	};


	class GenreProcessor : public FrameProcessor {
	public:
		GenreProcessor();
		virtual void process(std::istream& readStream, TagMap &map, std::uint32_t size) const override;
	};


	class CustomTextProcessor : public FrameProcessor {
	public:
		CustomTextProcessor();
		virtual void process(std::istream& readStream, TagMap &map, std::uint32_t size) const override;
	};


	class CommentProcessor : public FrameProcessor {
	public:
		CommentProcessor();
		virtual void process(std::istream& readStream, TagMap &map, std::uint32_t size) const override;
	};


	class ImageProcessor : public FrameProcessor {
	public:
		ImageProcessor();
		virtual void process(std::istream &readStream, TagMap &map, std::uint32_t size) const override;
	};


	class LyricsProcessor : public FrameProcessor {
	public:
		LyricsProcessor();
		virtual void process(std::istream &readStream, TagMap &map, std::uint32_t size) const override;
	};


	class ISRCProcessor : public FrameProcessor {
	public:
		ISRCProcessor();
		virtual void process(std::istream &readStream, TagMap &map, std::uint32_t size) const override;
	};


	extern const std::unordered_map<std::string, SharedFrameProcessor> FRAME2_PROCESSORS;
	extern const std::unordered_map<std::string, SharedFrameProcessor> FRAME3_PROCESSORS;
	extern const std::unordered_map<std::string, SharedFrameProcessor> FRAME4_PROCESSORS;
}