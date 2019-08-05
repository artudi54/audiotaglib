#include "ID3TagScanner.hpp"
#include <tag/except/StreamParseException.hpp>
#include <tag/priv/read_util.hpp>
#include <tag/priv/id3/Header.hpp>
#include <fstream>
namespace fs = std::filesystem;

namespace tag::scanner {
    static void appendFrontV2(std::vector<AudioTagLocation> &informationVector, std::istream &readStream, std::uint64_t fileSize) {
        if (fileSize >= 10 && priv::readAndEquals(readStream, priv::headers::ID3_V2)) {
            readStream.seekg(0, std::ios::beg);
            priv::id3::Header header = priv::id3::Header::readHeader(readStream);

            if (header.tagVersion() == AudioTagFormat::None)
                throw except::StreamParseException(3);
            if (header.totalTagSize() > fileSize)
                throw except::StreamParseException(6);

            informationVector.emplace_back(header.tagVersion(), 0, header.totalTagSize());
        }
    }

    static void appendV1(std::vector<AudioTagLocation> &informationVector, std::istream &readStream, std::uint64_t fileSize) {
        if (fileSize >= 128 && readStream.seekg(-128, std::ios::end)
            && priv::readAndEquals(readStream, priv::headers::ID3_V1))
            informationVector.emplace_back(AudioTagFormat::ID3v1, std::uint64_t(readStream.tellg()) - 3, 128);
    }

    static void appendBackV2(std::vector<AudioTagLocation> &informationVector, std::istream &readStream, std::uint64_t fileSize) {
        if (fileSize >= 10 && readStream.seekg(-10, std::ios::end)
            && priv::readAndEquals(readStream, priv::headers::ID3_V2R)) {

            readStream.seekg(-3, std::ios::cur);
            priv::id3::Header header = priv::id3::Header::readHeader(readStream);

            if (header.tagVersion() == AudioTagFormat::None)
                throw except::StreamParseException(static_cast<std::uint64_t>(readStream.tellg()) - 7);
            if (header.totalTagSize() > fileSize)
                throw except::StreamParseException(static_cast<std::uint64_t>(readStream.tellg()) - 4);

            informationVector.emplace_back(AudioTagFormat::ID3v24,
                                           std::uint64_t(readStream.tellg()) - header.totalTagSize(),
                                           header.totalTagSize());
        }

        else if (fileSize >= 138 && readStream.seekg(-138, std::ios::end)
                 && priv::readAndEquals(readStream, priv::headers::ID3_V2R)) {

            readStream.seekg(-3, std::ios::cur);
            priv::id3::Header header = priv::id3::Header::readHeader(readStream);

            if (header.tagVersion() == AudioTagFormat::None)
                throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 7);
            if (header.totalTagSize() > fileSize)
                throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 4);

            informationVector.emplace_back(AudioTagFormat::ID3v24,
                                           std::uint64_t(readStream.tellg()) - header.totalTagSize(),
                                           header.totalTagSize());
        }
    }

    AudioContainerFormat ID3TagScanner::getSpecificFormat() const noexcept {
        return AudioContainerFormat::Unspecified;
    }

    void ID3TagScanner::appendAudioTagInformationImpl(std::vector<AudioTagLocation> &informationVector,
                                                           std::istream &readStream, std::uint64_t fileSize) const {
		appendFrontV2(informationVector, readStream, fileSize);
		appendV1(informationVector, readStream, fileSize);
		appendBackV2(informationVector, readStream, fileSize);
	}
}
