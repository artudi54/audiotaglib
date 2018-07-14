#pragma once

#include <tag/scanner/APETagScanner.hpp>
#include <tag/scanner/ASFMetadataScanner.hpp>
#include <tag/scanner/ID3TagScanner.hpp>
#include <tag/scanner/RiffInfoScanner.hpp>
#include <tag/AudioContainerFormat.hpp>
#include <filesystem>
#include <unordered_map>


namespace tag::scanner {
	class StaticScannerFactory {
	public:
		[[deprecated("This will be removed soon")]] static const SharedTagScannerVector& getScanners(const std::filesystem::path &filePath, bool allPossible = false);
		static const SharedTagScannerVector& getScanners(AudioContainerFormat format, bool allPossible = false);
		static const SharedTagScannerVector& getAllScanners();
	private:
		StaticScannerFactory() = delete;

		static const std::unordered_map<AudioContainerFormat, const SharedTagScannerVector*> SCANNERS_MAP;
		static const std::unordered_map<AudioContainerFormat, const SharedTagScannerVector*> SCANNERS_ALL_MAP;
	};

}

