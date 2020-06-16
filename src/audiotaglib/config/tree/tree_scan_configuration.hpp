#pragma once
#include <audiotaglib/config/ScanConfiguration.hpp>
#include <boost/property_tree/ptree.hpp>

namespace audiotaglib::config::tree {
    void fillPropertyTree(boost::property_tree::ptree &propertyTree, const ScanConfiguration &scanConfiguration);
    ScanConfiguration scanConfigurationFromPropertyTree(const boost::property_tree::ptree &propertyTree);
}