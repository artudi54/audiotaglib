#include "FileNotFoundException.hpp"
namespace fs = std::filesystem;

namespace audiotaglib::except {
	FileNotFoundException::FileNotFoundException(const fs::path & filePath)
		: FileException(filePath, "File: \"" + filePath.filename().string() + "\" not found"){}
}