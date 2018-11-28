#include <tag/types/Image.hpp>
#include <tag/priv/headers.hpp>
#include <tag/priv/read_util.hpp>
using namespace std::literals;
namespace fs = std::filesystem;

namespace tag::priv {
    types::Image::MimeType imageMimeTypeFromFileName(const std::filesystem::path &filePath) {
        std::string extension = filePath.extension().string();
        if (extension == ".jpg"s || extension == ".jpeg"s)
            return types::Image::MimeType::ImageJpeg;
        if (extension == ".png"s)
            return types::Image::MimeType::ImagePng;
        std::ifstream readStream = std::ifstream(filePath, std::ios::in | std::ios::binary);
        return types::Image::MimeType::None;
    }

    types::Image::MimeType imageMimeTypeFromData(const std::vector<std::byte> &imageData) {
        static constexpr ByteArray<8>  PNG_HEADER = {
                std::byte(0x89), std::byte(0x50), std::byte(0x4E), std::byte(0x47),
                std::byte(0x0D), std::byte(0x0A), std::byte(0x1A), std::byte(0x0A)
        };
        static constexpr ByteArray<2> JPG_HEADER = { std::byte(0xFF), std::byte(0xD8) };
        static constexpr ByteArray<2> JPG_FOOTER = { std::byte(0xFF), std::byte(0xD9) };

        if (imageData.size() < 8)
            return types::Image::MimeType::None;

        types::Image::MimeType mimeType = types::Image::MimeType::None;
        if (std::equal(PNG_HEADER.begin(), PNG_HEADER.end(), imageData.begin()))
            mimeType = types::Image::MimeType::ImagePng;
        else if (std::equal(JPG_HEADER.begin(), JPG_HEADER.end(), imageData.begin()) &&
                 std::equal(JPG_FOOTER.rbegin(), JPG_FOOTER.rend(), imageData.rbegin()))
            mimeType = types::Image::MimeType::ImageJpeg;
        return mimeType;
    }
}

namespace tag::types {

	Image::Image(const std::vector<std::byte>& data, const std::string &description, MimeType mimeType)
		: data(data), description(description), mimeType(mimeType) {}

	Image::Image(std::vector<std::byte>&& data, const std::string &description, MimeType mimeType)
		: data(std::move(data)), description(description), mimeType(mimeType) {}

	Image::Image(const std::filesystem::path & filePath, const std::string &description)
		: data(), description(description), mimeType() {
		setFromFile(filePath);
	}


    bool Image::isEmpty() const noexcept {
        return mimeType == MimeType::None || data.empty();
    }

    const std::vector<std::byte>& Image::getData() const noexcept {
        return data;
    }

    std::vector<std::byte>& Image::getData() noexcept {
        return data;
    }

    void Image::setData(const std::vector<std::byte>& data) {
        this->data = data;
    }

    void Image::setData(std::vector<std::byte>&& data) {
        this->data = std::move(data);
    }


	const std::string & Image::getDescription() const noexcept {
		return description;
	}

	std::string & Image::getDescription() noexcept {
		return description;
	}

	void Image::setDescription(const std::string & description) {
		this->description = description;
	}


    Image::MimeType Image::getMimeType() const noexcept {
        return mimeType;
    }

    void Image::setMimeType(MimeType mimeType) noexcept {
        this->mimeType = mimeType;
    }


	bool Image::setFromFile(const fs::path & filePath) {
		std::error_code dummy;

		if (!fs::exists(filePath, dummy))
		    throw except::FileNotFoundException(filePath);

		try {
            auto[fileSize, readStream] = priv::validatedSizeAndStream(filePath);

            if (fileSize == 0)
                return false;

            MimeType newMimeType = priv::imageMimeTypeFromFileName(filePath);
            std::vector<std::byte> newData(fileSize);
            if (!readStream.read(reinterpret_cast<char *>(newData.data()), fileSize))
                return false;

            if (newMimeType == MimeType::None) {
                newMimeType = priv::imageMimeTypeFromData(newData);
                if (newMimeType == MimeType::None)
                    return false;
            }

            data = std::move(newData);
            mimeType = newMimeType;
            return true;
        }
        catch (except::InvalidFileException&) {
            return false;
        }
	}


    std::string Image::toString() const {
        if (isEmpty())
            return std::string();
        return "Image (type: "s + string::toString(mimeType) +
               ", size: "s + std::to_string(data.size()) +
               ", description: "s + description + ")"s;
    }

    bool Image::operator==(const Image &other) {
        return data == other.data && mimeType == other.mimeType && description == other.description;
    }

    bool Image::operator!=(const Image &other) {
        return !(*this == other);
    }
}

namespace tag::string {
    std::string toString(types::Image::MimeType mimeType) {
        switch (mimeType) {
            case types::Image::MimeType::ImageJpeg:
                return "image/jpeg"s;
            case types::Image::MimeType::ImagePng:
                return "image/png"s;
            default:
                return std::string();
        }
    }

    std::string toString(const types::Image &image) {
        return image.toString();
    }

    types::Image::MimeType parseImageMimeType(const std::string &mimeTypeString) {
        if (mimeTypeString == "image/jpeg"s)
            return types::Image::MimeType::ImageJpeg;
        if (mimeTypeString == "image/png"s)
            return types::Image::MimeType::ImagePng;
        return types::Image::MimeType::None;
    }
}