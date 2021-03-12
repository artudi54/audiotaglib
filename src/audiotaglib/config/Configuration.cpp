#include "Configuration.hpp"
#include <fstream>
#include <boost/property_tree/ini_parser.hpp>
#include <audiotaglib/common/io/file_stream_utils.hpp>
#include <audiotaglib/config/tree/tree_scan_configuration.hpp>
#include <audiotaglib/config/tree/tree_write_configuration.hpp>
namespace pt = boost::property_tree;
namespace fs = std::filesystem;

namespace audiotaglib::config {
    bool Configuration::operator==(const Configuration &rhs) const noexcept {
        return scanConfiguration == rhs.scanConfiguration &&
               writeConfiguration == rhs.writeConfiguration;
    }

    bool Configuration::operator!=(const Configuration &rhs) const noexcept {
        return !(rhs == *this);
    }

	void Configuration::saveTo(const fs::path &iniFilePath) const {
		pt::ptree propertyTree;

        std::ofstream writeStream = common::validOutputFileStream(iniFilePath, false);

		try {
		    tree::fillPropertyTree(propertyTree, scanConfiguration);
            pt::write_ini(writeStream, propertyTree);

            writeStream << '\n';
            propertyTree.clear();

            tree::fillPropertyTree(propertyTree, writeConfiguration);
            pt::write_ini(writeStream, propertyTree);
		}
		catch (pt::ini_parser_error&) {
			throw except::FileNotWritableException(iniFilePath);
		}
		catch (std::ios::failure &exc) {
            throw except::FileNotWritableException(iniFilePath);
		}
	}

	Configuration Configuration::loadFrom(const fs::path & iniFilePath) {
		pt::ptree propertyTree;
		std::ifstream readStream = common::validInputFileStreamWithCreation(iniFilePath, false, false);

		try {
			pt::read_ini(readStream, propertyTree);
		}
		catch (pt::ini_parser_error &ex) {
			throw except::FileParseException(iniFilePath, ex.line(), except::FileParseException::PositionType::Line);
		}

        Configuration configuration;
		configuration.scanConfiguration = tree::scanConfigurationFromPropertyTree(propertyTree);
        configuration.writeConfiguration = tree::writeConfigurationFromPropertyTree(propertyTree);

		return configuration;
	}
}