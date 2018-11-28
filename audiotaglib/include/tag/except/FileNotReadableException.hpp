#pragma once
#include <tag/except/FileException.hpp>

namespace tag::except {
	class FileNotReadableException : public FileException {
	public:
		explicit FileNotReadableException(const std::filesystem::path &filePath);
	};
}