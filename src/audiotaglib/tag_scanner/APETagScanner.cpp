#include "APETagScanner.hpp"
#include <audiotaglib/except/StreamParseException.hpp>
#include <audiotaglib/priv/read_util.hpp>
#include <audiotaglib/priv/ape/Header.hpp>
#include <fstream>
namespace fs = std::filesystem;

namespace audiotaglib::tag_scanner {
    void APETagScanner::appendTagContainerLocationsImpl(std::vector<TagContainerLocation> &tagContainerLocations,
                                                        common::ReadStream &readStream) const {
		appendFront(tagContainerLocations, readStream);
		appendBack(tagContainerLocations, readStream);
	}

    void APETagScanner::appendFront(std::vector<TagContainerLocation> & tagContainerLocations,
                                    common::ReadStream & readStream) {
        if (readStream.getSize() >= 32 && readStream.readHeaderAndEquals(priv::headers::APE)) {
            readStream.setPosition(0);
            priv::ape::Header header = priv::ape::Header::readHeader(readStream.getNativeStream());

            if (header.tagVersion() == TagContainerFormat::None)
                throw except::StreamParseException(8);
            if (header.totalTagSize() > readStream.getSize())
                throw except::StreamParseException(12);

            tagContainerLocations.emplace_back(TagContainerFormat::APEv2, header.size, header.totalTagSize());
        }
    }

    void APETagScanner::appendBack(std::vector<TagContainerLocation> & tagContainerLocations,
                                   common::ReadStream & readStream) {
        if (readStream.getSize() >= 32) {
            readStream.setPosition(-32, common::ReadStream::Offset::END);
            if (readStream.readHeaderAndEquals(priv::headers::APE)) {
                readStream.setPosition(-8, common::ReadStream::Offset::CURRENT);
                priv::ape::Header header = priv::ape::Header::readHeader(readStream.getNativeStream());

                if (header.tagVersion() == TagContainerFormat::None)
                    throw except::StreamParseException(readStream.getPosition() - 24);
                if (header.totalTagSize() > readStream.getSize())
                    throw except::StreamParseException(readStream.getPosition() - 20);

                tagContainerLocations.emplace_back(header.tagVersion(), readStream.getPosition() - 32,
                                                   header.totalTagSize());
            }
        }

        else if (readStream.getSize() >= 160) {
            readStream.setPosition(-160, common::ReadStream::Offset::END);
            if (readStream.readHeaderAndEquals(priv::headers::APE)) {
                readStream.setPosition(-8, common::ReadStream::Offset::CURRENT);
                priv::ape::Header header = priv::ape::Header::readHeader(readStream.getNativeStream());

                if (header.tagVersion() == TagContainerFormat::None)
                    throw except::StreamParseException(readStream.getPosition() - 24);
                if (header.totalTagSize() > readStream.getSize())
                    throw except::StreamParseException(readStream.getPosition() - 20);

                tagContainerLocations.emplace_back(header.tagVersion(), readStream.getPosition() - 32,
                                                   header.totalTagSize());
            }
        }
    }
}