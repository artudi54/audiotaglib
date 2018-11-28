#pragma once
#include <string>
#include <vector>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <filesystem>
#include <tag/except/FileNotFoundException.hpp>
#include <tag/except/FileNotReadableException.hpp>
#include <tag/except/InvalidFileException.hpp>

namespace tag::types {
	class Image {
	public:
		enum class MimeType : std::uint8_t {
			None, ImageJpeg, ImagePng
		};

		explicit Image(const std::vector<std::byte>& data = std::vector<std::byte>(),
			  const std::string &description = std::string(),
			  MimeType mimeType = MimeType::ImageJpeg);
		explicit Image(std::vector<std::byte>&& data,
			  const std::string &description = std::string(),
			  MimeType mimeType = MimeType::ImageJpeg);
		explicit Image(const std::filesystem::path &filePath,
			  const std::string &description = std::string());

		bool isEmpty() const;

        const std::vector<std::byte>& getData() const;
        std::vector<std::byte>& getData();
        void setData(const std::vector<std::byte>& data);
        void setData(std::vector<std::byte>&& data);

		const std::string& getDescription() const;
		std::string& getDescription();
		void setDescription(const std::string &description);

        MimeType getMimeType() const noexcept;
        void setMimeType(MimeType mimeType);

		void setFromFile(const std::filesystem::path &filePath);

		std::string toString() const;
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
