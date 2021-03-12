#include "FileParseException.hpp"
namespace fs = std::filesystem;

namespace audiotaglib::except {
	FileParseException::FileParseException(const fs::path & filePath, std::uint64_t position, PositionType positionType)
		: FileException(filePath,
						"Error occurred while parsing \"" +
						filePath.filename().string() +
						(positionType == PositionType::Offset ? "\" at offset: " : "\" at line: ") +
						std::to_string(position))
		, position(position)
		, positionType(positionType) {}
	
	FileParseException::FileParseException(const fs::path & filePath, const StreamParseException & exception)
		: FileParseException(filePath, exception.getPosition(), PositionType::Offset) {}


	std::uint64_t FileParseException::getPosition() const noexcept {
		return position;
	}

	FileParseException::PositionType FileParseException::getPositionType() const noexcept {
		return positionType;
	}
}