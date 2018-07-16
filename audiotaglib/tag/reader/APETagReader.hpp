#pragma once
#include <unordered_map>
#include <boost/algorithm/string.hpp>
#include <boost/functional/hash.hpp>
#include "AudioTagReader.hpp"
namespace tag::reader {
	class APETagReader : public AudioTagReader {
	public:
		virtual AudioTagMap readTag(std::istream &readStream) const override;
	private:
		enum class ValueType {
			String,
			Binary,
			External,
			Reserved
		};
		static ValueType fromFlags(unsigned flags);
		class ValueProcessor {
		public:
			ValueProcessor(const std::string &name);
			virtual void process(std::istream &readStream, AudioTagMap &map, unsigned size, ValueType valueType) = 0;
		protected:
			std::string name;
		};
		using SharedValueProcessor = std::shared_ptr<ValueProcessor>;

		class StringProcessor : public ValueProcessor {
		public:
			StringProcessor(const std::string &name);
			virtual void process(std::istream &readStream, AudioTagMap &map, unsigned size, ValueType valueType) override;
		};

		class MultiStringProcessor : public ValueProcessor {
		public:
			MultiStringProcessor(const std::string &name);
			virtual void process(std::istream &readStream, AudioTagMap &map, unsigned size, ValueType valueType) override;
		};

		class NumberProcessor : public ValueProcessor {
		public:
			NumberProcessor(const std::string &name);
			virtual void process(std::istream &readStream, AudioTagMap &map, unsigned size, ValueType valueType) override;
		};





		struct IEquals {
			bool operator()(const std::string &lhs, const std::string &rhs) const;
		};
		struct IHash {
			std::size_t operator()(const std::string &str) const;
		};



		static const std::unordered_map<std::string, SharedValueProcessor, IHash, IEquals> MAPPED_PROCESSORS;
	};
}