#pragma once
#include <audiotaglib/except/FileException.hpp>

namespace audiotaglib::except {
	class FileNotFoundException : public FileException {
	public:
		explicit FileNotFoundException(const std::filesystem::path &filePath);
	};
}