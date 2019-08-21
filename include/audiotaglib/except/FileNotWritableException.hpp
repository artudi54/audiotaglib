#pragma once
#include <audiotaglib/except/FileException.hpp>

namespace audiotaglib::except {
	class FileNotWritableException : public FileException {
	public:
		explicit FileNotWritableException(const std::filesystem::path &filePath);
	};
}