#pragma once
#include <sstream>
#include <regex>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/array.hpp>
#include "ID3v2TagReaderBase.hpp"
#include "AudioTagReader.hpp"
#include "genres.hpp"


namespace tag::reader {
	class ID3v2AudioTagReader : public base::ID3v2TagReaderBase {
		struct FrameProcessor : public base::AudioTagProcessorBase {
			FrameProcessor(const std::string &name);
			virtual ~FrameProcessor();
			virtual void process(std::istream& readStream, AudioTagMap &map, unsigned size) const = 0;
		protected:
			std::string name;
		};
		using SharedFrameProcessor = std::shared_ptr<FrameProcessor>;
	public:
		virtual AudioTagMap readTag(std::istream &readStream) const override;
	private:
		void processFrame(Frame &frame, AudioTagMap &map, const std::unordered_map<std::string, SharedFrameProcessor>& PROCESSORS) const;





		struct TextProcessor : public FrameProcessor {
			TextProcessor(const std::string &name);
			virtual void process(std::istream& readStream, AudioTagMap &map, unsigned size) const override;
		};

		struct MultistringTextProcessor : public FrameProcessor {
			MultistringTextProcessor(const std::string &name);
			virtual void process(std::istream& readStream, AudioTagMap &map, unsigned size) const override;
		};

		struct URLProcessor : public FrameProcessor {
			URLProcessor(const std::string &name);
			virtual void process(std::istream& readStream, AudioTagMap &map, unsigned size) const override;
		};

		struct SingleNumberTextProcessor : public FrameProcessor {
			SingleNumberTextProcessor(const std::string &name);
			virtual void process(std::istream& readStream, AudioTagMap &map, unsigned size) const override;
		};

		struct DoubleNumberTextProcessor : public FrameProcessor {
			DoubleNumberTextProcessor(const std::string &firstName, const std::string &secondName);
			virtual void process(std::istream& readStream, AudioTagMap &map, unsigned size) const override;
			std::string secondName;
		};

		struct FullDateProcessor : public FrameProcessor {
			FullDateProcessor(const std::string &name);
			virtual void process(std::istream& readStream, AudioTagMap &map, unsigned size) const override;

		};

		struct DateProcessor : public FrameProcessor {
			DateProcessor(const std::string &name);
			virtual void process(std::istream& readStream, AudioTagMap &map, unsigned size) const override;
		};

		struct YearProcessor : public FrameProcessor {
			YearProcessor(const std::string &name);
			virtual void process(std::istream& readStream, AudioTagMap &map, unsigned size) const override;
		};

		struct GenreProcessor : public FrameProcessor {
			GenreProcessor();
			virtual void process(std::istream& readStream, AudioTagMap &map, unsigned size) const override;
		};

		struct CustomTextProcessor : public FrameProcessor {
			CustomTextProcessor();
			virtual void process(std::istream& readStream, AudioTagMap &map, unsigned size) const override;
		};

		struct CommentProcessor : public FrameProcessor {
			CommentProcessor();
			virtual void process(std::istream& readStream, AudioTagMap &map, unsigned size) const override;
		};

		struct ImageProcessor : public FrameProcessor {
			ImageProcessor();
			virtual void process(std::istream &readStream, AudioTagMap &map, unsigned size) const override;
		};

		static const std::unordered_map<std::string, SharedFrameProcessor> FRAME2_PROCESSORS;
		static const std::unordered_map<std::string, SharedFrameProcessor> FRAME3_PROCESSORS;
		static const std::unordered_map<std::string, SharedFrameProcessor> FRAME4_PROCESSORS;
	};
}