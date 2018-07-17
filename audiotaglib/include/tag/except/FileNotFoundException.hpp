#pragma once

#include <tag/except/FileException.hpp>


namespace tag::except {
	class FileNotFoundException : public FileException {
	public:
		FileNotFoundException(const std::filesystem::path &filePath);
	};
}