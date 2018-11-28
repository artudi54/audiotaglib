#include "WriteConfiguration.hpp"
#include <tag/priv/config/scan_configuration.hpp>
#include <tag/priv/config/write_configuration.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <fstream>
namespace pt = boost::property_tree;

namespace tag::config {

    void WriteConfiguration::saveTo(const std::filesystem::path &iniFilePath) const {
        pt::ptree propertyTree;

        std::ofstream writeStream(iniFilePath, std::ios::out);
        if (!writeStream.is_open())
            throw except::FileNotWritableException(iniFilePath);


        try {
            tag::priv::config::fillPropertyTree(propertyTree, *this);
            pt::write_ini(writeStream, propertyTree);
        }
        catch (pt::ini_parser_error&) {
            throw except::FileNotWritableException(iniFilePath);
        }
    }

    // todo: add file not found exception
    WriteConfiguration WriteConfiguration::loadFrom(const std::filesystem::path &iniFilePath) {
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

        return priv::config::getWriteConfigFromPropertyTree(propertyTree);
    }
}