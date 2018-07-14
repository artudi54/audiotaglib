#pragma once
#include <tag/except/FileException.hpp>

namespace tag::except {
	class FileParseException : public FileException {
	public:
		enum class PositionType {
			Offset, Line
		};
		FileParseException(const std::filesystem::path &filePath, std::uint64_t offset, PositionType PositionType);
		std::uint64_t getPosition() const noexcept;
		PositionType getPositionType() const noexcept;
	private:
		std::uint64_t offset;
		PositionType positionType;
	};
}