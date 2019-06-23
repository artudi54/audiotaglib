#pragma once
#include <stdexcept>
#include <filesystem>

namespace tag::except {
	class FileException : public std::runtime_error {
	public:
		FileException(const std::filesystem::path &filePath, const std::string &whatArg);
		const std::filesystem::path getFilePath() const noexcept;
	private:
		std::filesystem::path filePath;
	};
}