#include "FileParseException.hpp"

namespace tag::except {
	FileParseException::FileParseException(const std::filesystem::path & filePath, std::uint64_t position, PositionType PositionType)
		: FileException(filePath,
						"Error occured while parsing \"" +
						filePath.filename().string() +
						(positionType == PositionType::Offset ? "\" at offset: " : "\" at line: ") +
						std::to_string(position))
		, position(position)
		, positionType(positionType) {}
	





	FileParseException::FileParseException(const std::filesystem::path & filePath, const StreamParseException & exception)
		: FileParseException(filePath, exception.getPosition(), PositionType::Offset) {}


	std::uint64_t FileParseException::getPosition() const noexcept {
		return position;
	}

	FileParseException::PositionType FileParseException::getPositionType() const noexcept {
		return positionType;
	}
}