#include "tree_scan_configuration.hpp"
namespace pt = boost::property_tree;

namespace audiotaglib::config::tree {
    static const std::string PROCESS_UNKNOWN_CONTAINER_FORMATS = "ScanConfiguration.ProcessUnknownContainerFormats";
    static const std::string SEARCH_FOR_ALL_POSSIBLE_TAGS    = "ScanConfiguration.SearchForAllPossibleTags";

    void fillPropertyTree(pt::ptree &propertyTree, const ScanConfiguration &scanConfiguration) {
        propertyTree.add(PROCESS_UNKNOWN_CONTAINER_FORMATS, scanConfiguration.processUnknownContainerFormats);
        propertyTree.add(SEARCH_FOR_ALL_POSSIBLE_TAGS,    scanConfiguration.searchForAllPossibleTags);
    }

    ScanConfiguration scanConfigurationFromPropertyTree(const pt::ptree &propertyTree) {
        ScanConfiguration configuration;

        configuration.processUnknownContainerFormats = propertyTree.get<bool>(
                PROCESS_UNKNOWN_CONTAINER_FORMATS, configuration.processUnknownContainerFormats);

        configuration.searchForAllPossibleTags     = propertyTree.get<bool>(
                SEARCH_FOR_ALL_POSSIBLE_TAGS, configuration.searchForAllPossibleTags);

        return configuration;
    }
}
