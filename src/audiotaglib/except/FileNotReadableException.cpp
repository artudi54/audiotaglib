#include "FileNotReadableException.hpp"

namespace audiotaglib::except {
	FileNotReadableException::FileNotReadableException(const std::filesystem::path & filePath)
		: FileException(filePath, "File: \"" + filePath.filename().string() + "\" is not readable") {}
}
