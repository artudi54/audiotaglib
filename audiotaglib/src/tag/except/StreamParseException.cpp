#include <tag/except/StreamParseException.hpp>
using namespace std::literals;
namespace tag::except {
	StreamParseException::StreamParseException(std::uint64_t position) 
		: std::runtime_error("Error occured while parsing stream at "s + std::to_string(position))
		, position(position) {}

	std::uint64_t StreamParseException::getPosition() const {
		return position;
	}
}