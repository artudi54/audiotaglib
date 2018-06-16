#pragma once

#include "ID3TagScanner.hpp"
#include "APETagScanner.hpp"
#include "RiffInfoScanner.hpp"
#include "ASFMetadataScanner.hpp"

#include <experimental/filesystem>
#include <unordered_map>


namespace tag::scanner {
	class StaticScannerFactory {
	public:
		static const SharedTagScannerVector& getScanners(const std::filesystem::path &filePath, bool allPossible = false);
		
		static const SharedTagScannerVector& getAllScanners();
		static const SharedTagScannerVector& getWaveAudioScanners();
		static const SharedTagScannerVector& getMpegLayer3Scanners();
		static const SharedTagScannerVector& getWindowsMediaAudioScanners();

	private:
		StaticScannerFactory() = delete;

		static const SharedTagScannerVector& getAllWaveAudioScanners();
		static const SharedTagScannerVector& getAllMpegLayer3Scanners();
		static const SharedTagScannerVector& getAllWindowsMediaAudioScanners();

		using FunctionType = const SharedTagScannerVector&(*)();
		static const std::unordered_map<std::string, FunctionType> MAPPED_SCANNERS;
		static const std::unordered_map<std::string, FunctionType> MAPPED_ALL_SCANNERS;

	};

}

