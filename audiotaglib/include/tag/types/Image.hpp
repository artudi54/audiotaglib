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

		Image(const std::vector<std::byte>& data = std::vector<std::byte>(),
			  const std::string &description = std::string(),
			  MimeType mimeType = MimeType::ImageJpeg);

		Image(std::vector<std::byte>&& data,
			  const std::string &description,
			  MimeType mimeType = MimeType::ImageJpeg);

		Image(const std::filesystem::path &filePath,
			  const std::string &description = std::string());

		MimeType getMimeType() const noexcept;
		void setMimeType(MimeType mimeType);

		const std::string& getDescription() const;
		std::string& getDescription();
		void setDescription(const std::string &description);

		const std::vector<std::byte>& getData() const;
		std::vector<std::byte>& getData();
		void setData(const std::vector<std::byte>& data);
		void setData(std::vector<std::byte>&& data);


		void setFromFile(const std::filesystem::path &filePath);
	private:
		MimeType mimeType;
		std::string description;
		std::vector<std::byte> data;
	};
}

namespace tag::string {
std::string toString(types::Image::MimeType mimeType);
}
