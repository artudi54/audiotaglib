#pragma once
#include <audiotaglib/config/WriteConfiguration.hpp>
#include <boost/property_tree/ptree.hpp>

namespace audiotaglib::priv::config {
    void fillPropertyTree(boost::property_tree::ptree &propertyTree,
                          const audiotaglib::config::WriteConfiguration &writeConfiguration);
    audiotaglib::config::WriteConfiguration writeConfigurationFromPropertyTree(const boost::property_tree::ptree &propertyTree);

}