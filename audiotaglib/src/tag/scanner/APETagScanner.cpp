#include "APETagScanner.hpp"
#include <tag/except/StreamParseException.hpp>
#include <tag/priv/read_util.hpp>
#include <tag/priv/ape/Header.hpp>
#include <fstream>
namespace fs = std::filesystem;

namespace tag::scanner {
    static void appendFront(AudioTagInformationVector & informationVector, std::istream & readStream,
                                    std::uint64_t fileSize) {
        if (fileSize >= 32 && priv::readAndEquals(readStream, priv::headers::APE)) {
            readStream.seekg(0, std::ios::beg);
            priv::ape::Header header = priv::ape::Header::readHeader(readStream);

            if (header.tagVersion() == AudioTagFormat::None)
                throw except::StreamParseException(8);
            if (header.totalTagSize() > fileSize)
                throw except::StreamParseException(12);

            informationVector.emplace_back(AudioTagFormat::APEv2, header.size, header.totalTagSize());
        }
    }

    static void appendBack(AudioTagInformationVector & informationVector, std::istream & readStream,
                                   std::uint64_t fileSize) {
        if (fileSize >= 32 && readStream.seekg(-32, std::ios::end)
            && priv::readAndEquals(readStream, priv::headers::APE)) {
            readStream.seekg(-8, std::ios::cur);
            priv::ape::Header header = priv::ape::Header::readHeader(readStream);

            if (header.tagVersion() == AudioTagFormat::None)
                throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 24);
            if (header.totalTagSize() > fileSize)
                throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 20);

            informationVector.emplace_back(header.tagVersion(), std::uint64_t(readStream.tellg()) - 32,
                                           header.totalTagSize());
        }

        else if (fileSize >= 160 && readStream.seekg(-160, std::ios::end)
                 && priv::readAndEquals(readStream, priv::headers::APE)) {
            readStream.seekg(-8, std::ios::cur);
            priv::ape::Header header = priv::ape::Header::readHeader(readStream);

            if (header.tagVersion() == AudioTagFormat::None)
                throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 24);
            if (header.totalTagSize() > fileSize)
                throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 20);

            informationVector.emplace_back(header.tagVersion(), std::uint64_t(readStream.tellg()) - 32,
                                           header.totalTagSize());
        }
    }

    AudioContainerFormat APETagScanner::getSpecificFormat() const {
        return AudioContainerFormat::Unspecified;
    }

    void APETagScanner::appendAudioTagInformationImpl(AudioTagInformationVector &informationVector,
                                                      std::istream &readStream, std::uint64_t fileSize) const {
		appendFront(informationVector, readStream, fileSize);
		appendBack(informationVector, readStream, fileSize);
	}
}