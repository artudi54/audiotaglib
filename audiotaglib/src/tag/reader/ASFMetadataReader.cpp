#include <tag/reader/ASFMetadataReader.hpp>
#include <tag/priv/read_util.hpp>
#include <tag/priv/asf/DescriptorProcessor.hpp>

using namespace std::literals;

namespace tag::reader {
	AudioTagMap ASFMetadataReader::readTag(std::istream & readStream) const {
		AudioTagMap map;
		if (!priv::readAndEquals(readStream, priv::headers::ASF_HEADER_GUID))
			throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 16);

		std::uint64_t headerSize = priv::readLongLittleEndianSize(readStream);
		if (headerSize < 30)
			return map;

		unsigned objectsNumber = priv::readLittleEndianSize(readStream);
		readStream.ignore();
		if (readStream.get() != 0x02)
			throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 1);

		processHeader(map, readStream, headerSize - 30, objectsNumber);
		return map;
	}




	void ASFMetadataReader::processHeader(AudioTagMap & map, std::istream & readStream, std::uint64_t size, unsigned objectsNumber) const {
		std::array<std::byte, 16> objectGuid;
		std::uint64_t objectSize;

		while (objectsNumber-- > 0 && size > 0) {
			objectGuid = priv::readHeader<16>(readStream);
			objectSize = priv::readLongLittleEndianSize(readStream);

			if (objectGuid == priv::headers::ASF_CONTENT_DESCRIPTION_GUID)
				processContentDescription(map, readStream, objectSize);
			else if (objectGuid == priv::headers::ASF_EXTENDED_CONTENT_DESCRIPTION_GUID)
				processExtendedContentDescription(map, readStream, objectSize);
			else
				readStream.seekg(objectSize - 24, std::ios::cur);
			size -= objectSize;
		}
	}





	void ASFMetadataReader::processContentDescription(AudioTagMap & map, std::istream & readStream, std::uint64_t size) const {
		std::uint16_t titleLength = priv::readShortLittleEndianSize(readStream);
		std::uint16_t authorLength = priv::readShortLittleEndianSize(readStream);
		std::uint16_t copyrightLength = priv::readShortLittleEndianSize(readStream);
		std::uint16_t descriptionLength = priv::readShortLittleEndianSize(readStream);
		std::uint16_t ratingLength = priv::readShortLittleEndianSize(readStream);

		std::string title = priv::readUtf16LE(readStream, titleLength);
		std::string artist = priv::readUtf16LE(readStream, authorLength);
		std::string copyright = priv::readUtf16LE(readStream, copyrightLength);
		std::string comment = priv::readUtf16LE(readStream, descriptionLength);
		readStream.seekg(ratingLength, std::ios::cur);

		if (!title.empty())
			map.setTitle(title);
		if (!artist.empty())
			map.setArtist(artist);
		if (!copyright.empty())
			map.setCopyright(copyright);
		if (!comment.empty())
			map.setComment(comment);
	}




	void ASFMetadataReader::processExtendedContentDescription(AudioTagMap & map, std::istream & readStream, std::uint64_t size) const {
		std::uint16_t descriptorsCount = priv::readShortLittleEndianSize(readStream);

		priv::asf::DataType valueType;
		std::uint16_t nameLength, valueLength;
		std::string name;

		while (descriptorsCount--) {
			nameLength = priv::readShortLittleEndianSize(readStream);
			name = priv::readUtf16LE(readStream, nameLength);
			valueType = static_cast<priv::asf::DataType>(priv::readShortLittleEndianSize(readStream));
			valueLength = priv::readShortLittleEndianSize(readStream);
			priv::asf::SharedDescriptorProcessor processor = priv::asf::getDescriptorProcessor(name);
			if (processor != nullptr)
				processor->process(readStream, map, valueLength, valueType);
			else
				readStream.seekg(valueLength, std::ios::cur);
		}
	}
}