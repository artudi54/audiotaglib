#pragma once
#include <string>
#include <string_view>

namespace audiotaglib::priv {
	struct IEquals {
		bool operator()(const std::string &lhs, const std::string &rhs) const;
        bool operator()(const std::string_view &lhs, const std::string_view &rhs) const;
        bool operator()(const std::string_view &lhs, const std::string &rhs) const;
        bool operator()(const std::string &lhs, const std::string_view &rhs) const;
    };

	struct IHash {
		std::size_t operator()(const std::string &str) const;
		std::size_t operator()(const std::string_view &str) const;
	};
}