#include "FileException.hpp"

namespace audiotaglib::except {
	FileException::FileException(const std::filesystem::path & filePath, const std::string & whatArg)
		: std::runtime_error(whatArg)
		, filePath(filePath) {}


	const std::filesystem::path& FileException::getFilePath() const noexcept {
		return filePath;
	}
}