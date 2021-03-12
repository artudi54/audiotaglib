#include <audiotaglib/types/Image.hpp>
#include <audiotaglib/except/FileException.hpp>
#include <audiotaglib/priv/headers.hpp>
#include <audiotaglib/priv/read_util.hpp>
#include <boost/iostreams/stream.hpp>
using namespace std::literals;
namespace fs = std::filesystem;
namespace io = boost::iostreams;

namespace audiotaglib::types {
    const std::size_t MINIMAL_FILE_SIZE = 8;

    bool isJpgStream(std::istream &readStream) {
        static constexpr priv::ByteArray<2> JPG_HEADER = { std::byte(0xFF), std::byte(0xD8) };
        static constexpr priv::ByteArray<2> JPG_FOOTER = { std::byte(0xFF), std::byte(0xD9) };

        readStream.seekg(0, std::ios::beg);
        if (!priv::readAndEquals(readStream, JPG_HEADER))
            return false;

        readStream.seekg(-2, std::ios::end);
        return priv::readAndEquals(readStream, JPG_FOOTER);
    }

    bool isPngStream(std::istream &readStream) {
        static constexpr priv::ByteArray<8>  PNG_HEADER = {
                std::byte(0x89), std::byte(0x50), std::byte(0x4E), std::byte(0x47),
                std::byte(0x0D), std::byte(0x0A), std::byte(0x1A), std::byte(0x0A)
        };
        readStream.seekg(0, std::ios::beg);
        return priv::readAndEquals(readStream, PNG_HEADER);
    }

    static Image::MimeType mimeTypeFromStream(std::istream &readStream) {
        if (isPngStream(readStream))
            return Image::MimeType::ImagePng;
        if (isJpgStream(readStream))
            return Image::MimeType::ImageJpeg;
        return Image::MimeType::None;
    }

    static Image::MimeType mimeTypeFromData(const std::vector<std::byte> &data) {
        io::array_source source(reinterpret_cast<const char*>(data.data()), data.size());
        io::stream<io::array_source> dataStream(source);
        return mimeTypeFromStream(dataStream);
    }


	Image::Image(const std::vector<std::byte>& data, const std::string &description)
		: data(), description(description), mimeType(MimeType::None) {
        setFromData(data);
    }

	Image::Image(std::vector<std::byte>&& data, const std::string &description)
		: data(), description(description), mimeType(MimeType::None) {
        setFromData(std::move(data));
    }

	Image::Image(const std::filesystem::path & filePath, const std::string &description)
		: data(), description(description), mimeType(MimeType::None) {
		setFromFile(filePath);
	}


    const std::vector<std::byte>& Image::getData() const noexcept {
        return data;
    }

    bool Image::setFromData(std::vector<std::byte> &&data) {
        MimeType dataType = mimeTypeFromData(data);
        if (dataType == Image::MimeType::None)
            return false;

        this->data = std::move(data);
        this->mimeType = dataType;
        return true;
    }

    bool Image::setFromData(const std::vector<std::byte> &data) {
        MimeType dataType = mimeTypeFromData(data);
        if (dataType == Image::MimeType::None)
            return false;

        this->data = data;
        this->mimeType = dataType;
        return true;
    }

    bool Image::setFromFile(const fs::path & filePath) {
        std::error_code dummy;

        if (!fs::exists(filePath, dummy))
            return false;

        std::uint64_t fileSize = fs::file_size(filePath, dummy);
        if (fileSize == static_cast<std::uint64_t>(-1) || fileSize < MINIMAL_FILE_SIZE)
            return false;

        std::ifstream readStream;
        readStream.exceptions(std::ios::failbit | std::ios::badbit);
        try {
            readStream.open(filePath);
            Image::MimeType fileDataType = mimeTypeFromStream(readStream);
            if (fileDataType == MimeType::None)
                return false;

            std::vector<std::byte> fileData(fileSize);
            readStream.seekg(0, std::ios::beg);
            readStream.read(reinterpret_cast<char*>(fileData.data()), fileSize);

            data = std::move(fileData);
            mimeType = fileDataType;
            return true;
        }
        catch (std::ios::failure &) {
            return false;
        }
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


    bool Image::isEmpty() const noexcept {
        return mimeType == MimeType::None || data.empty();
    }

    std::string Image::toString() const {
        if (isEmpty())
            return std::string();
        return "Image (type: "s + string::toString(mimeType) +
               ", size: "s + std::to_string(data.size()) +
               ", description: "s + description + ")"s;
    }


    bool Image::operator==(const Image &other) const {
        return data == other.data && mimeType == other.mimeType && description == other.description;
    }

    bool Image::operator!=(const Image &other)  const {
        return !(*this == other);
    }
}

namespace audiotaglib::string {
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