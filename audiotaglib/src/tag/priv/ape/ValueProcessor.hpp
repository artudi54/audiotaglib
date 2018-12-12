#pragma once
#include <tag/AudioTagMap.hpp>
#include <tag/priv/ape/ValueType.hpp>

namespace tag::priv::ape {
	class ValueProcessor {
	public:
		ValueProcessor(const std::string &name);
		virtual void process(std::istream &readStream, AudioTagMap &map, std::uint32_t size, ValueType valueType) = 0;
	protected:
		std::string name;
	};
	using SharedValueProcessor = std::shared_ptr<ValueProcessor>;


	class StringProcessor : public ValueProcessor {
	public:
		StringProcessor(const std::string &name);
		virtual void process(std::istream &readStream, AudioTagMap &map, std::uint32_t size, ValueType valueType) override;
	};


	class MultiStringProcessor : public ValueProcessor {
	public:
		MultiStringProcessor(const std::string &name);
		virtual void process(std::istream &readStream, AudioTagMap &map, std::uint32_t size, ValueType valueType) override;
	};


	class NumberProcessor : public ValueProcessor {
	public:
		NumberProcessor(const std::string &name);
		virtual void process(std::istream &readStream, AudioTagMap &map, std::uint32_t size, ValueType valueType) override;
	};


	class DoubleNumberProcessor : public ValueProcessor {
	public:
		DoubleNumberProcessor(const std::string &name, const std::string &secondName);
		virtual void process(std::istream &readStream, AudioTagMap &map, std::uint32_t size, ValueType valueType) override;
	private:
		std::string secondName;
	};


	class GenreProcessor : public ValueProcessor {
	public:
		GenreProcessor();
		virtual void process(std::istream &readStream, AudioTagMap &map, std::uint32_t size, ValueType valueType) override;
	};


	class DateProcessor : public ValueProcessor {
	public:
		DateProcessor(const std::string &name);
		virtual void process(std::istream &readStream, AudioTagMap &map, std::uint32_t size, ValueType valueType) override;
	};


	class ISRCProcessor : public ValueProcessor {
	public:
		ISRCProcessor();
		virtual void process(std::istream &readStream, AudioTagMap &map, std::uint32_t size, ValueType valueType) override;
	};

	class BarcodeProcessor : public ValueProcessor {
	public:
		BarcodeProcessor();
		virtual void process(std::istream &readStream, AudioTagMap &map, std::uint32_t size, ValueType valueType) override;
	};

	
	class LyricsProcessor : public ValueProcessor {
	public:
		LyricsProcessor();
		virtual void process(std::istream &readStream, AudioTagMap &map, std::uint32_t size, ValueType valueType) override;
	};


	class FrontImageProcessor : public ValueProcessor {
	public:
		FrontImageProcessor(const std::string &name);
		virtual void process(std::istream &readStream, AudioTagMap &map, std::uint32_t size, ValueType valueType) override;
	};


	class CustomStringProcessor : public StringProcessor {
	public:
	    CustomStringProcessor();
	    void setName(const std::string &name);
	};


	SharedValueProcessor getValueProcessor(const std::string &name);
}