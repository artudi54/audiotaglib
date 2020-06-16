#pragma once
#include <audiotaglib/config/WriteConfiguration.hpp>
#include <boost/property_tree/ptree.hpp>

namespace audiotaglib::config::tree {
    void fillPropertyTree(boost::property_tree::ptree &propertyTree, const WriteConfiguration &writeConfiguration);
    WriteConfiguration writeConfigurationFromPropertyTree(const boost::property_tree::ptree &propertyTree);
}