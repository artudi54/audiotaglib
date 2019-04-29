#include "TagScanner.hpp"
namespace fs = std::filesystem;

namespace tag::scanner {
	TagScanner::~TagScanner() {}

    AudioTagInformationVector TagScanner::getAudioTagInformation(const std::filesystem::path &filePath) const {
        AudioTagInformationVector informationVector;
        informationVector.reserve(8);
        appendAudioTagInformation(informationVector, filePath);
        return informationVector;
    }
}
