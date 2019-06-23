#include "scan_configuration.hpp"
namespace pt = boost::property_tree;

namespace tag::priv::config {
    static const std::string PROCESS_FILES_WITHOUT_EXTENSION = "ScanConfiguration.ProcessFilesWithoutExtension";
    static const std::string PROCESS_NON_AUDIO_FILES         = "ScanConfiguration.ProcessNonAudioFiles";
    static const std::string SEARCH_FOR_ALL_POSSIBLE_TAGS    = "ScanConfiguration.SearchForAllPossibleTags";

    void fillPropertyTree(pt::ptree &propertyTree,
                            const tag::config::ScanConfiguration &scanConfiguration) {
        propertyTree.add(PROCESS_FILES_WITHOUT_EXTENSION, scanConfiguration.processFilesWithoutExtension);
        propertyTree.add(PROCESS_NON_AUDIO_FILES,         scanConfiguration.processNonAudioFiles);
        propertyTree.add(SEARCH_FOR_ALL_POSSIBLE_TAGS,    scanConfiguration.searchForAllPossibleTags);
    }

    tag::config::ScanConfiguration scanConfigurationFromPropertyTree(const pt::ptree &propertyTree) {
        tag::config::ScanConfiguration configuration;

        configuration.processFilesWithoutExtension = propertyTree.get<bool>(
                PROCESS_FILES_WITHOUT_EXTENSION, configuration.processFilesWithoutExtension);

        configuration.processNonAudioFiles         = propertyTree.get<bool>(
                PROCESS_NON_AUDIO_FILES, configuration.processNonAudioFiles);

        configuration.searchForAllPossibleTags     = propertyTree.get<bool>(
                SEARCH_FOR_ALL_POSSIBLE_TAGS, configuration.searchForAllPossibleTags);

        return configuration;
    }
}
