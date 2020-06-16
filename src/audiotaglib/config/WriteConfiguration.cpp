#include "WriteConfiguration.hpp"
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <audiotaglib/common/file_stream_utils.hpp>
#include <audiotaglib/config/tree/tree_write_configuration.hpp>
namespace pt = boost::property_tree;

namespace audiotaglib::config {
    void WriteConfiguration::saveTo(const std::filesystem::path &iniFilePath) const {
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

    WriteConfiguration WriteConfiguration::loadFrom(const std::filesystem::path &iniFilePath) {
        pt::ptree propertyTree;
        std::ifstream readStream = common::validInputFileStreamWithCreation(iniFilePath, false, false);

        try {
            pt::read_ini(readStream, propertyTree);
        }
        catch (pt::ini_parser_error &ex) {
            throw except::FileParseException(iniFilePath, ex.line(), except::FileParseException::PositionType::Line);
        }

        return tree::writeConfigurationFromPropertyTree(propertyTree);
    }
}