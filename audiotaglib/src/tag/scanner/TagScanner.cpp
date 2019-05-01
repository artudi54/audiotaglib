#include "TagScanner.hpp"
#include <tag/except/FileNotReadableException.hpp>
#include <tag/except/FileParseException.hpp>
#include <fstream>
namespace fs = std::filesystem;

namespace tag::scanner {
	TagScanner::~TagScanner() {}

    AudioTagInformationVector TagScanner::getAudioTagInformation(const std::filesystem::path &filePath) const {
        AudioTagInformationVector informationVector;
        informationVector.reserve(8);
        appendAudioTagInformation(informationVector, filePath);
        return informationVector;
    }

    void TagScanner::appendAudioTagInformation(AudioTagInformationVector &informationVector,
                                                   const std::filesystem::path &filePath) const {
        std::error_code dummy;

        std::ifstream readStream(filePath, std::ios::in | std::ios::binary);
        std::uint64_t fileSize = fs::file_size(filePath, dummy);
        if (!readStream.is_open() || fileSize == std::uint64_t(-1))
            throw except::FileNotReadableException(filePath);

        try {
            readStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            appendAudioTagInformationImpl(informationVector, readStream, fileSize);
        }
        catch (std::ios::failure &exc) {
            throw except::FileParseException(filePath, std::uint64_t(readStream.tellg()),
                                             except::FileParseException::PositionType::Offset);
        }
        catch (except::StreamParseException &exc) {
            throw except::FileParseException(filePath, exc);
        }
    }
}
