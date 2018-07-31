#pragma once

namespace tag::priv::ape {
	enum class ValueType {
		String,
		Binary,
		External,
		Reserved
	};
	ValueType fromFlags(unsigned flags);
}