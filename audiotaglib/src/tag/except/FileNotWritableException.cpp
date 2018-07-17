#include <tag/except/FileNotWritableException.hpp>

namespace tag::except {
	FileNotWritableException::FileNotWritableException(const std::filesystem::path & filePath)
		: FileException(filePath, "File: \"" + filePath.filename().string() + "\" is not writable") {}
}