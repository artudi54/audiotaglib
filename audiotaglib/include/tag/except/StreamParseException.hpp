#pragma once
#include <stdexcept>
#include <string>

namespace tag::except {
	class StreamParseException : public std::runtime_error {
	public:
		StreamParseException(std::uint64_t position);
		std::uint64_t getPosition() const;
	private:
		std::uint64_t position;
	};
}