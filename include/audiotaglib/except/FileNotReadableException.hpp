#pragma once
#include <audiotaglib/except/FileException.hpp>

namespace audiotaglib::except {
	class FileNotReadableException : public FileException {
	public:
		explicit FileNotReadableException(const std::filesystem::path &filePath);
	};
}