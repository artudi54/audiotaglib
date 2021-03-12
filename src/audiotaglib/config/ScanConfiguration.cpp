#include "ScanConfiguration.hpp"
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <audiotaglib/common/io/file_stream_utils.hpp>
#include <audiotaglib/config/tree/tree_scan_configuration.hpp>

namespace pt = boost::property_tree;

namespace audiotaglib::config {
    bool ScanConfiguration::operator==(const ScanConfiguration &rhs) const noexcept {
        return processUnknownContainerFormats == rhs.processUnknownContainerFormats &&
               searchForAllPossibleTags == rhs.searchForAllPossibleTags;
    }

    bool ScanConfiguration::operator!=(const ScanConfiguration &rhs) const noexcept {
        return !(rhs == *this);
    }

    void ScanConfiguration::saveTo(const std::filesystem::path &iniFilePath) const {
        pt::ptree propertyTree;
        tree::fillPropertyTree(propertyTree, *this);

        std::ofstream writeStream = common::validOutputFileStream(iniFilePath, false);

        try {
            pt::write_ini(writeStream, propertyTree);
        }
        catch (pt::ini_parser_error&) {
            throw except::FileNotWritableException(iniFilePath);
        }
        catch (std::ios::failure &exc) {
            throw except::FileNotWritableException(iniFilePath);
        }
    }

    ScanConfiguration ScanConfiguration::loadFrom(const std::filesystem::path &iniFilePath) {
        pt::ptree propertyTree;
        std::ifstream readStream = common::validInputFileStreamWithCreation(iniFilePath, false, false);

        try {
            pt::read_ini(readStream, propertyTree);
        }
        catch (pt::ini_parser_error &ex) {
            throw except::FileParseException(iniFilePath, ex.line(), except::FileParseException::PositionType::Line);
        }

        return tree::scanConfigurationFromPropertyTree(propertyTree);
    }
}