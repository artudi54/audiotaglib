#pragma once

#include "ID3TagScanner.hpp"
#include "APETagScanner.hpp"
#include "RiffInfoScanner.hpp"

#include <experimental/filesystem>
#include <unordered_map>


namespace tag::scanner {
	class StaticScannerFactory {
	public:
		static const SharedTagScannerVector& getScanners(const std::filesystem::path &filePath, bool allPossible = false);
		
		static const SharedTagScannerVector& getAllProbes();
		static const SharedTagScannerVector& getWaveAudioProbes();
		static const SharedTagScannerVector& getMpegLayer3Probes();

	private:
		StaticScannerFactory() = delete;

		static const SharedTagScannerVector& getAllWaveAudioProbes();
		static const SharedTagScannerVector& getAllMpegLayer3Probes();

		using FunctionType = const SharedTagScannerVector&(*)();
		static const std::unordered_map<std::string, FunctionType> MAPPED_PROBES;
		static const std::unordered_map<std::string, FunctionType> MAPPED_ALL_PROBES;

	};

}

