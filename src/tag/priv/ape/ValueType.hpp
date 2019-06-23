#pragma once
#include <cstdint>

namespace tag::priv::ape {
	enum class ValueType {
		String,
		Binary,
		External,
		Reserved
	};
	ValueType typeFromFlags(std::uint32_t flags);
}