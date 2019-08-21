#include "FileNotFoundException.hpp"

namespace audiotaglib::except {
	FileNotFoundException::FileNotFoundException(const std::filesystem::path & filePath)
		: FileException(filePath, "File: \"" + filePath.filename().string() + "\" not found"){}
}