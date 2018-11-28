#include "ScanConfiguration.hpp"
#include <tag/priv/config/scan_configuration.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <fstream>
namespace pt = boost::property_tree;

namespace tag::config {
    void ScanConfiguration::saveTo(const std::filesystem::path &iniFilePath) const {
        pt::ptree propertyTree;
        priv::config::fillPropertyTree(propertyTree, *this);

        try {
            pt::write_ini(iniFilePath.string(), propertyTree);
        }
        catch (pt::ini_parser_error&) {
            throw except::FileNotWritableException(iniFilePath);
        }
    }

    ScanConfiguration ScanConfiguration::loadFrom(const std::filesystem::path &iniFilePath) {
        pt::ptree propertyTree;

        std::fstream readStream(iniFilePath, std::ios::in);
        if (!readStream.is_open()) {
            readStream.open(iniFilePath, std::ios::in | std::ios::out | std::ios::trunc);
            if (!readStream.is_open())
                throw except::FileNotReadableException(iniFilePath);
        }

        try {
            pt::read_ini(readStream, propertyTree);
        }
        catch (pt::ini_parser_error &ex) {
            throw except::FileParseException(iniFilePath, ex.line(), except::FileParseException::PositionType::Line);
        }

        return priv::config::getScanConfigFromPropertyTree(propertyTree);
    }
}