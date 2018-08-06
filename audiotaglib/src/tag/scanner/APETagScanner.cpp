#include "APETagScanner.hpp"
#include <tag/priv/read_util.hpp>
#include <tag/priv/ape/Header.hpp>
namespace fs = std::filesystem;

namespace tag::scanner {

	void APETagScanner::appendAudioTagInformation(AudioTagInformationVector& informationVector,
												  const fs::path & filePath) const {
		auto[size, readStream] = getValidatedSizeAndStream(filePath);
		appendFront(informationVector, size, readStream, filePath);
		appendBack(informationVector, size, readStream, filePath);
	}

	AudioContainerFormat APETagScanner::getSpecificFormat() const {
		return AudioContainerFormat::Unspecified;
	}






	void APETagScanner::appendFront(AudioTagInformationVector & informationVector, std::uintmax_t size,
									std::istream & readStream, const fs::path & filePath) const {
		if (size >= 32 && priv::readAndEquals(readStream, priv::headers::APE)) {
			readStream.seekg(0, std::ios::beg);
			priv::ape::Header header = priv::ape::Header::readHeader(readStream);

			if (header.tagVersion() == AudioTagFormat::None)
				throw except::FileParseException(filePath, 8,
												 except::FileParseException::PositionType::Offset);
			if (header.totalTagSize() > size)
				throw except::FileParseException(filePath, 12,
												 except::FileParseException::PositionType::Offset);

			informationVector.emplace_back(AudioTagFormat::APEv2, header.size, header.totalTagSize());
		}
	}





	void APETagScanner::appendBack(AudioTagInformationVector & informationVector, std::uintmax_t size,
								   std::istream & readStream, const fs::path & filePath) const {
		if (size >= 32 && readStream.seekg(-32, std::ios::end)
			&& priv::readAndEquals(readStream, priv::headers::APE)) {
			readStream.seekg(-8, std::ios::cur);
			priv::ape::Header header = priv::ape::Header::readHeader(readStream);

			if (header.tagVersion() == AudioTagFormat::None)
				throw except::FileParseException(filePath, std::uint64_t(readStream.tellg()) - 24,
												 except::FileParseException::PositionType::Offset);
			if (header.totalTagSize() > size)
				throw except::FileParseException(filePath, std::uint64_t(readStream.tellg()) - 20,
												 except::FileParseException::PositionType::Offset);

			informationVector.emplace_back(header.tagVersion(), std::uint64_t(readStream.tellg()) - 32,
										   header.totalTagSize());
		}

		else if (size >= 160 && readStream.seekg(-160, std::ios::end)
			&& priv::readAndEquals(readStream, priv::headers::APE)) {
			readStream.seekg(-8, std::ios::cur);
			priv::ape::Header header = priv::ape::Header::readHeader(readStream);

			if (header.tagVersion() == AudioTagFormat::None)
				throw except::FileParseException(filePath, std::uint64_t(readStream.tellg()) - 24,
												 except::FileParseException::PositionType::Offset);
			if (header.totalTagSize() > size)
				throw except::FileParseException(filePath, std::uint64_t(readStream.tellg()) - 20,
												 except::FileParseException::PositionType::Offset);

			informationVector.emplace_back(header.tagVersion(), std::uint64_t(readStream.tellg()) - 32,
										   header.totalTagSize());
		}
	}

}