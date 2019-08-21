#include "icomp.hpp"
#include <locale>
#include <boost/functional/hash.hpp>
#include <boost/algorithm/string.hpp>

namespace audiotaglib::priv {
	bool IEquals::operator()(const std::string & lhs, const std::string & rhs) const {
		return boost::iequals(lhs, rhs);
	}

    bool IEquals::operator()(const std::string_view &lhs, const std::string_view &rhs) const {
        return boost::iequals(lhs, rhs);
    }

    bool IEquals::operator()(const std::string_view &lhs, const std::string &rhs) const {
        return operator()(lhs, std::string_view(rhs));
    }

    bool IEquals::operator()(const std::string &lhs, const std::string_view &rhs) const {
        return operator()(std::string_view(lhs), rhs);
    }


    std::size_t IHash::operator()(const std::string & str) const {
		std::size_t seed = 0;
		std::locale locale;
		for (auto c : str)
			boost::hash_combine(seed, std::toupper(c, locale));
		return seed;
	}

    std::size_t IHash::operator()(const std::string_view & str) const {
        std::size_t seed = 0;
        std::locale locale;
        for (auto c : str)
            boost::hash_combine(seed, std::toupper(c, locale));
        return seed;
    }
}