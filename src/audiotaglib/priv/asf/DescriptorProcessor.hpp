#pragma once
#include <audiotaglib/TagMap.hpp>

namespace audiotaglib::priv::asf {
	enum class DataType : std::uint16_t {
		String, ByteArray, Bool, Dword, Qword, Word
	};



	struct DescriptorProcessor {
		DescriptorProcessor(const std::string &name);
		virtual void process(std::istream &readStream, TagMap &map, std::uint16_t size, DataType dataType) const = 0;
	protected:
		std::string name;
	};
	using SharedDescriptorProcessor = std::shared_ptr<DescriptorProcessor>;


	struct StringDescriptorProcessor : public DescriptorProcessor {
		StringDescriptorProcessor(const std::string &name);
		virtual void process(std::istream &readStream, TagMap &map, std::uint16_t size, DataType dataType) const override;
	};


	struct MultiStringDescriptorProcessor : public DescriptorProcessor {
		MultiStringDescriptorProcessor(const std::string &name);
		virtual void process(std::istream &readStream, TagMap &map, std::uint16_t size, DataType dataType) const override;
	};


	struct CustomStringDescriptorProcessor : public DescriptorProcessor {
		CustomStringDescriptorProcessor();
		virtual void process(std::istream &readStream, TagMap &map, std::uint16_t size, DataType dataType) const override;
	};


	struct GenreDescriptorProcessor : public DescriptorProcessor {
		GenreDescriptorProcessor();
		virtual void process(std::istream &readStream, TagMap &map, std::uint16_t size, DataType dataType) const override;
	};


	struct NumberDescriptorProcessor : public DescriptorProcessor {
		NumberDescriptorProcessor(const std::string &name);
		virtual void process(std::istream &readStream, TagMap &map, std::uint16_t size, DataType dataType) const override;
	};


    struct ZeroBaseNumberDescriptorProcessor : public DescriptorProcessor {
        ZeroBaseNumberDescriptorProcessor(const std::string &name);
        virtual void process(std::istream &readStream, TagMap &map, std::uint16_t size, DataType dataType) const override;

    };


	struct DoubleNumberDescriptorProcessor : public DescriptorProcessor {
		DoubleNumberDescriptorProcessor(const std::string &firstName, const std::string &secondName);
		virtual void process(std::istream &readStream, TagMap &map, std::uint16_t size, DataType dataType) const override;
	private:
		std::string secondName;
	};


	struct YearDescriptorProcessor : public DescriptorProcessor {
		YearDescriptorProcessor(const std::string &name);
		virtual void process(std::istream &readStream, TagMap &map, std::uint16_t size, DataType dataType) const override;
	};


	struct DateDescirptorProcessor : public DescriptorProcessor {
		DateDescirptorProcessor(const std::string &name);
		virtual void process(std::istream &readStream, TagMap &map, std::uint16_t size, DataType dataType) const override;
	};


	struct PictureDescriptorProcessor : public DescriptorProcessor {
		PictureDescriptorProcessor();
		virtual void process(std::istream &readStream, TagMap &map, std::uint16_t size, DataType dataType) const override;
	};


	struct ISRCDescriptorProcessor : public DescriptorProcessor {
		ISRCDescriptorProcessor();
		virtual void process(std::istream &readStream, TagMap &map, std::uint16_t size, DataType dataType) const override;
	};

    struct BarcodeDescriptorProcessor : public DescriptorProcessor {
        BarcodeDescriptorProcessor();
        virtual void process(std::istream &readStream, TagMap &map, std::uint16_t size, DataType dataType) const override;
    };


    struct CustomStringProcessor : public StringDescriptorProcessor {
	    CustomStringProcessor();
	    void setName(const std::string &name);
	};

    struct LyricsProcessor : public DescriptorProcessor {
        LyricsProcessor();
        virtual void process(std::istream &readStream, TagMap &map, std::uint16_t size, DataType dataType) const override;
    };


	SharedDescriptorProcessor getDescriptorProcessor(const std::string &descriptorName);
}