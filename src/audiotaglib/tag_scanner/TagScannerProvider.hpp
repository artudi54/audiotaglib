#pragma once
#include <audiotaglib/ContainerFormat.hpp>
#include <audiotaglib/config/ScanConfiguration.hpp>
#include <audiotaglib/tag_scanner/TagScanner.hpp>

namespace audiotaglib::tag_scanner {
    class TagScannerProvider {
    public:
        TagScannerProvider() = delete;
        static const std::vector<std::unique_ptr<TagScanner>>& getScanners(ContainerFormat format, const config::ScanConfiguration &scanConfiguration = config::ScanConfiguration());
        static const std::vector<std::unique_ptr<TagScanner>>& getAllScanners();
    };
}

