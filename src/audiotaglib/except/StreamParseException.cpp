#include "StreamParseException.hpp"
using namespace std::literals;

namespace audiotaglib::except {
	StreamParseException::StreamParseException(std::uint64_t position) 
		: std::runtime_error("Error occurred while parsing stream at "s + std::to_string(position))
		, position(position) {}

	std::uint64_t StreamParseException::getPosition() const noexcept {
		return position;
	}
}