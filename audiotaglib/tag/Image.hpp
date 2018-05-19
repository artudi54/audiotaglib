#pragma once
#include <string>
#include <vector>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <filesystem>
//todo: add description
namespace tag::type {
class Image {
public:
    enum class MimeType : std::uint8_t {
        ImageJpeg, ImagePng
    };

    Image(const std::vector<std::byte>& data = std::vector<std::byte>(),
          MimeType mimeType = MimeType::ImageJpeg);
    Image(std::vector<std::byte>&& data, MimeType mimeType = MimeType::ImageJpeg);
    Image(const std::filesystem::path &filePath);

    MimeType getMimeType() const noexcept;
    void setMimeType(MimeType mimeType);

    const std::vector<std::byte>& getData() const;
    std::vector<std::byte>& getData();
    void setData(const std::vector<std::byte>& data);
    void setData(std::vector<std::byte>&& data);
    void setData(const std::filesystem::path &filePath);
private:
    MimeType mimeType;
    std::vector<std::byte> data;
};
}

namespace tag::string {
std::string toString(type::Image::MimeType mimeType);
}
