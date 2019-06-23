#pragma once
#include <tag/AudioContainerFormat.hpp>
#include <tag/config/ScanConfiguration.hpp>
#include <tag/scanner/TagScanner.hpp>

namespace tag::scanner {
		class TagScannerProvider {
		public:
			TagScannerProvider() = delete;
			static const std::vector<std::unique_ptr<TagScanner>>& getScanners(AudioContainerFormat format, const config::ScanConfiguration &scanConfiguration = config::ScanConfiguration());
			static const std::vector<std::unique_ptr<TagScanner>>& getAllScanners();
};
}

