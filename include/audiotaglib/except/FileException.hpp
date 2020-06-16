#pragma once
#include <filesystem>
#include <stdexcept>

namespace audiotaglib::except {
	class FileException : public std::runtime_error {
	public:
		FileException(const std::filesystem::path &filePath, const std::string &whatArg);
		[[nodiscard]] const std::filesystem::path& getFilePath() const noexcept;
	private:
		std::filesystem::path filePath;
	};
}