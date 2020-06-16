#include "FileException.hpp"
namespace fs = std::filesystem;

namespace audiotaglib::except {
	FileException::FileException(const fs::path & filePath, const std::string & whatArg)
		: std::runtime_error(whatArg)
		, filePath(filePath) {}


	const fs::path& FileException::getFilePath() const noexcept {
		return filePath;
	}
}