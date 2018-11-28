#include "ID3TagScanner.hpp"
#include <tag/priv/read_util.hpp>
#include <tag/priv/id3/Header.hpp>
namespace fs = std::filesystem;

namespace tag::scanner {
	void ID3TagScanner::appendAudioTagInformation(AudioTagInformationVector& informationVector,
												  const std::filesystem::path & filePath) const {
		auto[size, readStream] = priv::validatedSizeAndStream(filePath);
		appendFrontV2(informationVector, size, readStream, filePath);
		appendV1(informationVector, size, readStream);
		appendBackV2(informationVector, size, readStream, filePath);
	}

	AudioContainerFormat ID3TagScanner::getSpecificFormat() const {
		return AudioContainerFormat::Unspecified;
	}


	void ID3TagScanner::appendFrontV2(AudioTagInformationVector & informationVector, std::uintmax_t size, std::istream & readStream,
									  const fs::path & filePath) const {
		if (size >= 10 && priv::readAndEquals(readStream, priv::headers::ID3_V2)) {
			readStream.seekg(0, std::ios::beg);
			priv::id3::Header header = priv::id3::Header::readHeader(readStream);

			if (header.tagVersion() == AudioTagFormat::None)
				throw except::FileParseException(filePath, 3, except::FileParseException::PositionType::Offset);
			if (header.totalTagSize() > size)
				throw except::FileParseException(filePath, 6, except::FileParseException::PositionType::Offset);

			informationVector.emplace_back(header.tagVersion(), 0, header.totalTagSize());
		}
	}

	void ID3TagScanner::appendV1(AudioTagInformationVector & informationVector, std::uintmax_t size, std::istream & readStream) const {
		if (size >= 128 && readStream.seekg(-128, std::ios::end)
			&& priv::readAndEquals(readStream, priv::headers::ID3_V1))
			informationVector.emplace_back(AudioTagFormat::ID3v1, std::uint64_t(readStream.tellg()) - 3, 128);

	}

	void ID3TagScanner::appendBackV2(AudioTagInformationVector & informationVector, std::uintmax_t size, std::istream & readStream,
									 const fs::path & filePath) const {
		if (size >= 10 && readStream.seekg(-10, std::ios::end)
			&& priv::readAndEquals(readStream, priv::headers::ID3_V2R)) {

			readStream.seekg(-3, std::ios::cur);
			priv::id3::Header header = priv::id3::Header::readHeader(readStream);

			if (header.tagVersion() == AudioTagFormat::None)
				throw except::FileParseException(filePath, std::uint64_t(readStream.tellg()) - 7,
												 except::FileParseException::PositionType::Offset);
			if (header.totalTagSize() > size)
				throw except::FileParseException(filePath, std::uint64_t(readStream.tellg()) - 4,
												 except::FileParseException::PositionType::Offset);

			informationVector.emplace_back(AudioTagFormat::ID3v24,
				std::uint64_t(readStream.tellg()) - header.totalTagSize(),
				header.totalTagSize());
		}

		else if (size >= 138 && readStream.seekg(-138, std::ios::end)
			&& priv::readAndEquals(readStream, priv::headers::ID3_V2R)) {

			readStream.seekg(-3, std::ios::cur);
			priv::id3::Header header = priv::id3::Header::readHeader(readStream);

			if (header.tagVersion() == AudioTagFormat::None)
				throw except::FileParseException(filePath, std::uint64_t(readStream.tellg()) - 7,
												 except::FileParseException::PositionType::Offset);
			if (header.totalTagSize() > size)
				throw except::FileParseException(filePath, std::uint64_t(readStream.tellg()) - 4,
												 except::FileParseException::PositionType::Offset);

			informationVector.emplace_back(AudioTagFormat::ID3v24,
				std::uint64_t(readStream.tellg()) - header.totalTagSize(),
				header.totalTagSize());
		}
	}
}
