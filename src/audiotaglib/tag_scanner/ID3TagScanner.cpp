#include "ID3TagScanner.hpp"
#include <audiotaglib/except/StreamParseException.hpp>
#include <audiotaglib/priv/read_util.hpp>
#include <audiotaglib/priv/id3/Header.hpp>
namespace fs = std::filesystem;

namespace audiotaglib::tag_scanner {
        ContainerFormat ID3TagScanner::getAssociatedContainerFormat() const noexcept {
        return ContainerFormat::Unknown;
    }

    void ID3TagScanner::appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                                        common::ReadStream &readStream) const {
		appendFrontV2(tagContainerLocations, readStream);
		appendV1(tagContainerLocations, readStream);
		appendBackV2(tagContainerLocations, readStream);
	}

    void ID3TagScanner::appendFrontV2(std::vector<TagContainerLocation> &tagContainerLocations, common::ReadStream &readStream) {
        if (readStream.getSize() >= 10 && readStream.readHeaderAndEquals(priv::headers::ID3_V2)) {
            readStream.setPosition(0);
            priv::id3::Header header = priv::id3::Header::readHeader(readStream.getNativeStream());

            if (header.tagVersion() == TagContainerFormat::None)
                throw except::StreamParseException(3);
            if (header.totalTagSize() > readStream.getSize())
                throw except::StreamParseException(6);

            tagContainerLocations.emplace_back(header.tagVersion(), 0, header.totalTagSize());
        }
    }

    void ID3TagScanner::appendV1(std::vector<TagContainerLocation> &tagContainerLocations, common::ReadStream &readStream) {
        if (readStream.getSize() >= 128) {
            readStream.setPosition(-128, common::ReadStream::Offset::END);
            if (readStream.readHeaderAndEquals(priv::headers::ID3_V1))
                tagContainerLocations.emplace_back(TagContainerFormat::ID3v1, readStream.getPosition() - 3, 128);
        }
    }

    void ID3TagScanner::appendBackV2(std::vector<TagContainerLocation> &tagContainerLocations, common::ReadStream &readStream) {
        if (readStream.getSize() >= 10) {
            readStream.setPosition(-10, common::ReadStream::Offset::END);
            if (readStream.readHeaderAndEquals(priv::headers::ID3_V2R)) {
                readStream.setPosition(-3, common::ReadStream::Offset::CURRENT);
                priv::id3::Header header = priv::id3::Header::readHeader(readStream.getNativeStream());

                if (header.tagVersion() == TagContainerFormat::None)
                    throw except::StreamParseException(readStream.getPosition() - 7);
                if (header.totalTagSize() > readStream.getSize())
                    throw except::StreamParseException(readStream.getPosition() - 4);

                tagContainerLocations.emplace_back(TagContainerFormat::ID3v24,
                                                   readStream.getPosition() - header.totalTagSize(),
                                                   header.totalTagSize());
            }
        }

        else if (readStream.getSize() >= 138) {
            readStream.setPosition(-138, common::ReadStream::Offset::END);
            if (readStream.readHeaderAndEquals(priv::headers::ID3_V2R)) {
                readStream.setPosition(-3, common::ReadStream::Offset::CURRENT);
                priv::id3::Header header = priv::id3::Header::readHeader(readStream.getNativeStream());

                if (header.tagVersion() == TagContainerFormat::None)
                    throw except::StreamParseException(readStream.getPosition() - 7);
                if (header.totalTagSize() > readStream.getSize())
                    throw except::StreamParseException(readStream.getPosition() - 4);

                tagContainerLocations.emplace_back(TagContainerFormat::ID3v24,
                                                   readStream.getPosition() - header.totalTagSize(),
                                                   header.totalTagSize());
            }
        }
    }
}
