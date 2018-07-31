#pragma once
#include <string>

namespace tag::priv::ape {
	struct IEquals {
		bool operator()(const std::string &lhs, const std::string &rhs) const;
	};
	struct IHash {
		std::size_t operator()(const std::string &str) const;
	};
}