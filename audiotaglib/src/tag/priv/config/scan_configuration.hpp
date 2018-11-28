#pragma once
#include <tag/config/ScanConfiguration.hpp>
#include <boost/property_tree/ptree.hpp>

namespace tag::priv::config {
    void fillPropertyTree(boost::property_tree::ptree &propertyTree,
                            const tag::config::ScanConfiguration &scanConfiguration);
    tag::config::ScanConfiguration getScanConfigFromPropertyTree(const boost::property_tree::ptree &propertyTree);
}