#pragma once
#include <tag/AudioTagMap.hpp>

namespace tag::priv::vorbis {
    class ValueProcessor {
    public:
        ValueProcessor(const std::string &name);
        virtual void process(const std::string_view &value, AudioTagMap &map) const = 0;
    protected:
        std::string name;
    };
    using SharedValueProcessor = std::shared_ptr<ValueProcessor>;


    class StringProcessor : public ValueProcessor {
    public:
        StringProcessor(const std::string &name);
        virtual void process(const std::string_view &value, AudioTagMap &map) const override;
    };

    class MultiStringProcessor : public ValueProcessor {
    public:
        MultiStringProcessor(const std::string &name);
        virtual void process(const std::string_view &value, AudioTagMap &map) const override;
    };


    class NumberProcessor : public ValueProcessor {
    public:
        NumberProcessor(const std::string &name);
        virtual void process(const std::string_view &value, AudioTagMap &map) const override;
    };


    class DateProcessor : public ValueProcessor {
    public:
        DateProcessor(const std::string &name);
        virtual void process(const std::string_view &value, AudioTagMap &map) const override;
    };



    class ISRCProcessor : public ValueProcessor {
    public:
        ISRCProcessor();
        virtual void process(const std::string_view &value, AudioTagMap &map) const override;
    };

    class BarcodeProcessor : public ValueProcessor {
    public:
        BarcodeProcessor();
        virtual void process(const std::string_view &value, AudioTagMap &map) const override;
    };

	class ImageProcessor : public ValueProcessor {
	public:
		ImageProcessor();
		virtual void process(const std::string_view &value, AudioTagMap &map) const override;
		void processStream(std::istream &readStream, std::uint32_t size, AudioTagMap &map) const;
	};


    SharedValueProcessor getValueProcessor(const std::string_view &name);
}