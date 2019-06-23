#pragma once
#include <tag/except/FileException.hpp>

namespace tag::except {
	class FileNotFoundException : public FileException {
	public:
		explicit FileNotFoundException(const std::filesystem::path &filePath);
	};
}