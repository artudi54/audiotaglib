#pragma once
#include <string>
#include <vector>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <filesystem>

namespace tag::types {
	class Image {
	public:
		enum class MimeType : std::uint8_t {
			None,
			ImageJpeg,
			ImagePng
		};
		explicit Image(const std::vector<std::byte>& data = std::vector<std::byte>(),
			  const std::string &description = std::string());
		explicit Image(std::vector<std::byte>&& data,
			  const std::string &description = std::string());
		explicit Image(const std::filesystem::path &filePath,
			  const std::string &description = std::string());

		const std::vector<std::byte>& getData() const noexcept;
        bool setFromData(std::vector<std::byte>&& data);
        bool setFromData(const std::vector<std::byte>& data);
		bool setFromFile(const std::filesystem::path &filePath);

		const std::string& getDescription() const noexcept;
		std::string& getDescription() noexcept;
		void setDescription(const std::string &description);

        MimeType getMimeType() const noexcept;

        bool isEmpty() const noexcept;
        std::string toString() const;

        bool operator==(const Image &other) const;
		bool operator!=(const Image &other) const;
	private:
        std::vector<std::byte> data;
        std::string description;
        MimeType mimeType;
	};
}

namespace tag::string {
	std::string toString(types::Image::MimeType mimeType);
    std::string toString(const types::Image &image);
    types::Image::MimeType parseImageMimeType(const std::string &mimeTypeString);
}
