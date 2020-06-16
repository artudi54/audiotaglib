#include "FileNotWritableException.hpp"
namespace fs = std::filesystem;

namespace audiotaglib::except {
	FileNotWritableException::FileNotWritableException(const fs::path & filePath)
		: FileException(filePath, "File: \"" + filePath.filename().string() + "\" is not writable") {}
}