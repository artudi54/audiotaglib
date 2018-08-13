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
	private:
        std::vector<std::byte> data;
        std::string description;
        MimeType mimeType;
	};
}

namespace tag::string {
	std::string toString(types::Image::MimeType mimeType);
}
