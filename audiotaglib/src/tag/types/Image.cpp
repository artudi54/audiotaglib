#include <tag/types/Image.hpp>
using namespace std::literals;
namespace fs = std::filesystem;

namespace tag::types {
	Image::Image(const std::vector<std::byte>& data, const std::string &description, MimeType mimeType)
		: data(data), description(description), mimeType(mimeType) {}

	Image::Image(std::vector<std::byte>&& data, const std::string &description, MimeType mimeType)
		: data(std::move(data)), description(description), mimeType(mimeType) {}

	Image::Image(const std::filesystem::path & filePath, const std::string &description)
		: data(), description(description), mimeType() {
		setFromFile(filePath);
	}


    const std::vector<std::byte>& Image::getData() const {
        return data;
    }

    std::vector<std::byte>& Image::getData() {
        return data;
    }

    void Image::setData(const std::vector<std::byte>& data) {
        this->data = data;
    }

    void Image::setData(std::vector<std::byte>&& data) {
        this->data = std::move(data);
    }


	const std::string & Image::getDescription() const {
		return description;
	}

	std::string & Image::getDescription() {
		return description;
	}

	void Image::setDescription(const std::string & description) {
		this->description = description;
	}


    Image::MimeType Image::getMimeType() const noexcept {
        return mimeType;
    }

    void Image::setMimeType(MimeType mimeType) {
        this->mimeType = mimeType;
    }


    // todo: add exceptions
	void Image::setFromFile(const fs::path & filePath) {
		std::error_code dummy;
		std::uintmax_t fileSize = fs::file_size(filePath, dummy);
		if (fileSize == std::uintmax_t(-1))
			return;

		std::string extension = filePath.extension().string();
		if (extension == ".jpg"s || extension == ".jpeg"s)
			mimeType = MimeType::ImageJpeg;
		else if (extension == ".png"s)
			mimeType = MimeType::ImagePng;
		else
			return;

		std::ifstream input(filePath, std::ios::in | std::ios::binary);
		data.resize(fileSize);
		input.read(reinterpret_cast<char*>(data.data()), fileSize);
	}
}


std::string tag::string::toString(types::Image::MimeType mimeType) {
	switch (mimeType) {
	case types::Image::MimeType::ImageJpeg:
		return "image/jpeg"s;
	case types::Image::MimeType::ImagePng:
		return "image/png"s;
	default:
		return std::string();
	}
}
