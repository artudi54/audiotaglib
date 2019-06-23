#pragma once
#include <tag/config/WriteConfiguration.hpp>
#include <boost/property_tree/ptree.hpp>

namespace tag::priv::config {
    void fillPropertyTree(boost::property_tree::ptree &propertyTree,
                          const tag::config::WriteConfiguration &writeConfiguration);
    tag::config::WriteConfiguration writeConfigurationFromPropertyTree(const boost::property_tree::ptree &propertyTree);

}