#pragma once
#include <tag/except/FileException.hpp>
#include <tag/except/StreamParseException.hpp>

namespace tag::except {
	class FileParseException : public FileException {
	public:
		enum class PositionType {
			Offset, Line
		};
		FileParseException(const std::filesystem::path &filePath, std::uint64_t position, PositionType PositionType);
		FileParseException(const std::filesystem::path &filePath, const StreamParseException &exception);
		std::uint64_t getPosition() const noexcept;
		PositionType getPositionType() const noexcept;
	private:
		std::uint64_t position;
		PositionType positionType;
	};
}