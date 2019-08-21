#pragma once
#include <cstdint>

namespace audiotaglib::priv::ape {
	enum class ValueType {
		String,
		Binary,
		External,
		Reserved
	};
	ValueType typeFromFlags(std::uint32_t flags);
}