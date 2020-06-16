#include "Configuration.hpp"
#include <fstream>
#include <boost/property_tree/ini_parser.hpp>
#include <audiotaglib/config/tree/tree_scan_configuration.hpp>
#include <audiotaglib/config/tree/tree_write_configuration.hpp>
namespace pt = boost::property_tree;
namespace fs = std::filesystem;

namespace audiotaglib::config {
	void Configuration::saveTo(const fs::path & iniFilePath) const {
		pt::ptree propertyTree;

        std::ofstream writeStream(iniFilePath, std::ios::out);
        if (!writeStream.is_open())
            throw except::FileNotWritableException(iniFilePath);

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
	}

	Configuration Configuration::loadFrom(const fs::path & iniFilePath) {
		Configuration configuration;
		pt::ptree propertyTree;

		std::ifstream readStream(iniFilePath, std::ios::in);
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

		configuration.scanConfiguration = tree::scanConfigurationFromPropertyTree(propertyTree);
        configuration.writeConfiguration = tree::writeConfigurationFromPropertyTree(propertyTree);

		return configuration;
	}
}