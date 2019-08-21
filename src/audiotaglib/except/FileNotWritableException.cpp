#include "FileNotWritableException.hpp"

namespace audiotaglib::except {
	FileNotWritableException::FileNotWritableException(const std::filesystem::path & filePath)
		: FileException(filePath, "File: \"" + filePath.filename().string() + "\" is not writable") {}
}