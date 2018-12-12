#include "ValueType.hpp"

namespace tag::priv::ape {
	ValueType typeFromFlags(std::uint32_t flags) {
		const std::uint32_t RESERVED = 0b110;
		const std::uint32_t EXTERNAL = 0b100;
		const std::uint32_t BINARY = 0b010;

		if ((flags & RESERVED) == RESERVED)
			return ValueType::Reserved;
		if ((flags & EXTERNAL) == EXTERNAL)
			return ValueType::External;
		if ((flags & BINARY) == BINARY)
			return ValueType::Binary;
		return ValueType::String;
	}
}