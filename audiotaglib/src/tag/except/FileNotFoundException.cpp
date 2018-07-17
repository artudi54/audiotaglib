#include <tag/except/FileNotFoundException.hpp>


namespace tag::except {
	FileNotFoundException::FileNotFoundException(const std::filesystem::path & filePath)
		: FileException(filePath, "File: \"" + filePath.filename().string() + "\" not found"){}
}