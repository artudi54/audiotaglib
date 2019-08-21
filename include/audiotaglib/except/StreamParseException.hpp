#pragma once
#include <stdexcept>
#include <string>

namespace audiotaglib::except {
	class StreamParseException : public std::runtime_error {
	public:
		explicit StreamParseException(std::uint64_t position);
		std::uint64_t getPosition() const;
	private:
		std::uint64_t position;
	};
}