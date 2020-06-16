#include "FileNotReadableException.hpp"
namespace fs = std::filesystem;

namespace audiotaglib::except {
	FileNotReadableException::FileNotReadableException(const fs::path & filePath)
		: FileException(filePath, "File: \"" + filePath.filename().string() + "\" is not readable") {}
}
