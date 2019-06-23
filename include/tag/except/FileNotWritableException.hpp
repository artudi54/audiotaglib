#pragma once
#include <tag/except/FileException.hpp>

namespace tag::except {
	class FileNotWritableException : public FileException {
	public:
		explicit FileNotWritableException(const std::filesystem::path &filePath);
	};
}