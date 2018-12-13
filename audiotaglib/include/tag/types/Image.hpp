#pragma once
#include <string>
#include <vector>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <filesystem>

namespace tag::types {
    /**
     * Image class.
     * Stores image data for PNG or JPEG images. Internally used in tag::ImageAudioTag.
     */
	class Image {
	public:
	    /**
	     * MimeType enum.
	     * Holds information about stored image format.
	     */
		enum class MimeType : std::uint8_t {
			None, /**< Invalid or unknown image format. */
			ImageJpeg, /**< JPEG image format. */
			ImagePng /**< PNG image format. */
		};

		/**
		 * Default constructor.
		 * Creates empty image object or image from passed optional arguments.
		 * @param data Binary data of image, default empty vector.
		 * @param description Description of image, default empty string.
		 * @param mimeType Mime type of the image, default JPEG.
		 */
		explicit Image(const std::vector<std::byte>& data = std::vector<std::byte>(),
			  const std::string &description = std::string(),
			  MimeType mimeType = MimeType::ImageJpeg);

        /**
         * Move constructor for data.
         * Creates image taking rvalue reference to data.
         * @param data Binary data rvalue reference of image.
         * @param description Description of image, default empty string.
         * @param mimeType Mime type of the image, default JPEG.
         */
		explicit Image(std::vector<std::byte>&& data,
			  const std::string &description = std::string(),
			  MimeType mimeType = MimeType::ImageJpeg);

        /**
         * File constructor.
         * Creates image representing file specified in filePath
         * @param filePath Path to image.
         * @param description Description of image, default empty string.
         */
		explicit Image(const std::filesystem::path &filePath,
			  const std::string &description = std::string());

		/**
		 * Method checking if image object is empty.
		 * %Image is empty if data is empty or mimeType is MimeType::None.
		 * @return true if empty, false otherwise.
		 */
		bool isEmpty() const noexcept;

		/**
		 * Getter for data
		 * @return Image data const reference
		 */
        const std::vector<std::byte>& getData() const noexcept;
        /**
         * Getter for data.
         * @return %Image data reference.
         */
        std::vector<std::byte>& getData() noexcept;
        /**
         *  Setter for data.
         * @param data %Image data const reference.
         */
        void setData(const std::vector<std::byte>& data);
        /**
         * Setter for data.
         * @param data %Image data rvalue reference.
         */
        void setData(std::vector<std::byte>&& data);

        /**
         * Getter for description.
         * @return %Image description const reference.
         */
		const std::string& getDescription() const noexcept;
        /**
         * Getter for description.
         * @return %Image description reference.
         */
		std::string& getDescription() noexcept;
		/**
		 * Setter for description
		 * @param description Description of image.
		 */
		void setDescription(const std::string &description);

        /**
         * Getter for mimeType.
         * @return %Image mimeType.
         */
        MimeType getMimeType() const noexcept;
        /**
         * Setter for mimeType
         * @param mimeType %Image mimeType.
         */
        void setMimeType(MimeType mimeType) noexcept;

        /**
         * Sets data and mimeType representing file specified in filePath.
         * If error occurred during reading data, or specified filePath is invalid, image state is left unchanged.
         * @param filePath Path to image.
         * @returns true on success, false otherwise.
       */
		bool setFromFile(const std::filesystem::path &filePath);

		/**
		 * Returns image string representation in format: "Image (type: t, size: s, description: d)".
		 * @return Printable representation of image.
		 */
		std::string toString() const;

		bool operator==(const Image &other);
		bool operator!=(const Image &other);
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
