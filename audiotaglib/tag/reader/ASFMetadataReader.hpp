#pragma once
#include "AudioTagReader.hpp"
#include "ID3v2AudioTagReader.hpp"
#include <unordered_map>
#include <memory>
#include <ctime>

namespace tag::reader {
	class ASFMetadataReader : public AudioTagReader {
	public:
		virtual AudioTagMap readTag(std::istream &readStream) const override;
	private:
		enum class DataType : std::uint16_t {
			String, ByteArray, Bool, Dword, Qword, Word
		};

		void processHeader(AudioTagMap &map, std::istream &readStream, std::uint64_t size, unsigned objectsNumber) const;
		void processContentDescription(AudioTagMap &map, std::istream &readStream, std::uint64_t size) const;
		void processExtendedContentDescription(AudioTagMap &map, std::istream &readStream, std::uint64_t size) const;









		struct DescriptorProcessor {
			DescriptorProcessor(const std::string &name);
			virtual void process(std::istream &readStream, AudioTagMap &map, std::uint16_t size, DataType dataType) const = 0;
		protected:
			std::string name;
		};
		using SharedDescriptorProcessor = std::shared_ptr<DescriptorProcessor>;

		struct StringDescriptorProcessor : public DescriptorProcessor {
			StringDescriptorProcessor(const std::string &name);
			virtual void process(std::istream &readStream, AudioTagMap &map, std::uint16_t size, DataType dataType) const override;
		};

		struct MultiStringDescriptorProcessor : public DescriptorProcessor {
			MultiStringDescriptorProcessor(const std::string &name);
			virtual void process(std::istream &readStream, AudioTagMap &map, std::uint16_t size, DataType dataType) const override;
		};

		struct CustomStringDescriptorProcessor : public DescriptorProcessor {
			CustomStringDescriptorProcessor();
			virtual void process(std::istream &readStream, AudioTagMap &map, std::uint16_t size, DataType dataType) const override;
		};

		struct GenreDescriptorProcessor : public DescriptorProcessor {
			GenreDescriptorProcessor();
			virtual void process(std::istream &readStream, AudioTagMap &map, std::uint16_t size, DataType dataType) const override;
		};

		struct NumberDescriptorProcessor : public DescriptorProcessor {
			NumberDescriptorProcessor(const std::string &name);
			virtual void process(std::istream &readStream, AudioTagMap &map, std::uint16_t size, DataType dataType) const override;
		};

		struct DoubleNumberDescriptorProcessor : public DescriptorProcessor {
			DoubleNumberDescriptorProcessor(const std::string &firstName, const std::string &secondName);
			virtual void process(std::istream &readStream, AudioTagMap &map, std::uint16_t size, DataType dataType) const override;
		private:
			std::string secondName;
		};

		struct YearDescriptorProcessor : public DescriptorProcessor {
			YearDescriptorProcessor(const std::string &name);
			virtual void process(std::istream &readStream, AudioTagMap &map, std::uint16_t size, DataType dataType) const override;
		};

		struct DateDescirptorProcessor : public DescriptorProcessor {
			DateDescirptorProcessor(const std::string &name);
			virtual void process(std::istream &readStream, AudioTagMap &map, std::uint16_t size, DataType dataType) const override;
		};

		struct PictureDescriptorProcessor : public DescriptorProcessor{
			PictureDescriptorProcessor();
			virtual void process(std::istream &readStream, AudioTagMap &map, std::uint16_t size, DataType dataType) const override;
		};

		struct ISRCDescriptorProcessor : public DescriptorProcessor {
			ISRCDescriptorProcessor();
			virtual void process(std::istream &readStream, AudioTagMap &map, std::uint16_t size, DataType dataType) const override;
		};

		static const std::unordered_map<std::string, SharedDescriptorProcessor> PROCESSORS;
	};
}