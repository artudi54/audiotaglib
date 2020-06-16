#pragma once
#include <audiotaglib/except/FileException.hpp>
#include <audiotaglib/except/StreamParseException.hpp>

namespace audiotaglib::except {
	class FileParseException : public FileException {
	public:
		enum class PositionType {
			Offset, Line
		};
		FileParseException(const std::filesystem::path &filePath, std::uint64_t position, PositionType PositionType);
		FileParseException(const std::filesystem::path &filePath, const StreamParseException &exception);
		[[nodiscard]] std::uint64_t getPosition() const noexcept;
		[[nodiscard]] PositionType getPositionType() const noexcept;
	private:
		std::uint64_t position;
		PositionType positionType;
	};
}