#include "FileParseException.hpp"

namespace tag::except {
	FileParseException::FileParseException(const std::filesystem::path & filePath, std::uint64_t offset, PositionType PositionType)
		: FileException(filePath,
						"Error occured while parsing \"" +
						filePath.filename().string() +
						(positionType == PositionType::Offset ? "\" at offset: " : "\" at line: ") +
						std::to_string(offset))
		, offset(offset)
		, positionType(positionType) {}
	


	std::uint64_t FileParseException::getPosition() const noexcept {
		return offset;
	}

	FileParseException::PositionType FileParseException::getPositionType() const noexcept {
		return positionType;
	}
}