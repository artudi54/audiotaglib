#include "ValueType.hpp"

namespace tag::priv::ape {
	ValueType fromFlags(unsigned flags) {
		const unsigned RESERVED = 0b110;
		const unsigned EXTERNAL = 0b100;
		const unsigned BINARY = 0b010;

		if (flags & RESERVED)
			return ValueType::Reserved;
		if (flags & EXTERNAL)
			return ValueType::External;
		if (flags & BINARY)
			return ValueType::Binary;
		return ValueType::String;
	}
}