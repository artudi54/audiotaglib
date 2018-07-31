#include "icomp.hpp"
#include <locale>
#include <boost/functional/hash.hpp>
#include <boost/algorithm/string.hpp>

namespace tag::priv::ape {

	bool IEquals::operator()(const std::string & lhs, const std::string & rhs) const {
		return boost::iequals(lhs, rhs);
	}



	std::size_t IHash::operator()(const std::string & str) const {
		std::size_t seed = 0;
		std::locale locale;
		for (auto c : str)
			boost::hash_combine(seed, std::toupper(c, locale));
		return seed;
	}
}