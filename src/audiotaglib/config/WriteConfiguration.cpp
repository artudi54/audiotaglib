#include "WriteConfiguration.hpp"
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <audiotaglib/config/tree/tree_write_configuration.hpp>
namespace pt = boost::property_tree;

namespace audiotaglib::config {
    void WriteConfiguration::saveTo(const std::filesystem::path &iniFilePath) const {
        pt::ptree propertyTree;

        std::ofstream writeStream(iniFilePath, std::ios::out);
        if (!writeStream.is_open())
            throw except::FileNotWritableException(iniFilePath);


        try {
            tree::fillPropertyTree(propertyTree, *this);
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

        return tree::writeConfigurationFromPropertyTree(propertyTree);
    }
}