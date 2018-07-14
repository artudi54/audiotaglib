#pragma once
#include <tag/except/FileException.hpp>

namespace tag::except {
	class FileNotWritableException : public FileException {
	public:
		FileNotWritableException(const std::filesystem::path &filePath);
	};
}