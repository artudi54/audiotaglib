#include <tag/types/Image.hpp>

using namespace std::literals;
namespace fs = std::filesystem;

namespace tag::types {
	Image::Image(const std::vector<std::byte>& data, const std::string &description, MimeType mimeType)
		: mimeType(mimeType), description(description), data(data)  {}

	Image::Image(std::vector<std::byte>&& data, const std::string &description, MimeType mimeType)
		: mimeType(mimeType), description(description), data(std::move(data)) {}

	Image::Image(const std::filesystem::path & filePath, const std::string &description)
		: description(description), data(), mimeType(){
		setFromFile(filePath);
	}




	Image::MimeType Image::getMimeType() const noexcept {
		return mimeType;
	}

	void Image::setMimeType(MimeType mimeType) {
		this->mimeType = mimeType;
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

	void Image::setFromFile(const fs::path & filePath) {
		std::error_code dummy;
		std::uintmax_t fileSize = fs::file_size(filePath, dummy);
		if (fileSize == -1)
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
