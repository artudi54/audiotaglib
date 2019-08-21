#pragma once
#include <audiotaglib/config/ScanConfiguration.hpp>
#include <boost/property_tree/ptree.hpp>

namespace audiotaglib::priv::config {
    void fillPropertyTree(boost::property_tree::ptree &propertyTree,
                            const audiotaglib::config::ScanConfiguration &scanConfiguration);
    audiotaglib::config::ScanConfiguration scanConfigurationFromPropertyTree(const boost::property_tree::ptree &propertyTree);
}