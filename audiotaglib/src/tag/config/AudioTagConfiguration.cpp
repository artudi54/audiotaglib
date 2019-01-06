#include "AudioTagConfiguration.hpp"
#include <tag/priv/config/scan_configuration.hpp>
#include <tag/priv/config/write_configuration.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <fstream>
namespace pt = boost::property_tree;
namespace fs = std::filesystem;



namespace tag::config {
	void AudioTagConfiguration::saveTo(const fs::path & iniFilePath) const {
		pt::ptree propertyTree;

        std::ofstream writeStream(iniFilePath, std::ios::out);
        if (!writeStream.is_open())
            throw except::FileNotWritableException(iniFilePath);


		try {
		    tag::priv::config::fillPropertyTree(propertyTree, scanConfiguration);
            pt::write_ini(writeStream, propertyTree);

            writeStream << '\n';
            propertyTree.clear();

            tag::priv::config::fillPropertyTree(propertyTree, writeConfiguration);
            pt::write_ini(writeStream, propertyTree);
		}
		catch (pt::ini_parser_error&) {
			throw except::FileNotWritableException(iniFilePath);
		}
	}

	AudioTagConfiguration AudioTagConfiguration::loadFrom(const fs::path & iniFilePath) {
		AudioTagConfiguration configuration;
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

		configuration.scanConfiguration = tag::priv::config::getScanConfigFromPropertyTree(propertyTree);
        configuration.writeConfiguration = tag::priv::config::writeConfigurationFromPropertyTree(propertyTree);

		return configuration;
	}
}