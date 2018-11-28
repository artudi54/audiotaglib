#pragma once
#include <tag/AudioContainerFormat.hpp>
#include <tag/config/ScanConfiguration.hpp>
#include <tag/scanner/AiffChunksScanner.hpp>
#include <tag/scanner/APETagScanner.hpp>
#include <tag/scanner/ASFMetadataScanner.hpp>
#include <tag/scanner/ID3TagScanner.hpp>
#include <tag/scanner/RiffInfoScanner.hpp>
#include <tag/scanner/FLACScanner.hpp>
#include <filesystem>
#include <unordered_map>

namespace tag::scanner {
	class StaticScannerFactory {
	public:
        StaticScannerFactory() = delete;

        static const SharedTagScannerVector& getScanners(AudioContainerFormat format,
		                                                 const config::ScanConfiguration &scanConfiguration = config::ScanConfiguration());
		static const SharedTagScannerVector& getAllScanners();
	private:
		static const std::unordered_map<AudioContainerFormat, const SharedTagScannerVector*> SCANNERS_MAP;
		static const std::unordered_map<AudioContainerFormat, const SharedTagScannerVector*> SCANNERS_ALL_MAP;
	};

}

