#include "StaticScannerFactory.hpp"
namespace fs = std::filesystem;
using namespace std::literals;

namespace tag::scanner {
	const SharedTagScannerVector& StaticScannerFactory::getScanners(const fs::path & filePath, bool allPossible) {
		if (allPossible) {
			auto it = MAPPED_ALL_SCANNERS.find(filePath.extension().string());
			if (it != MAPPED_ALL_SCANNERS.end())
				return it->second();
			return getAllScanners();
		} else {
			auto it = MAPPED_SCANNERS.find(filePath.extension().string());
			if (it != MAPPED_SCANNERS.end())
				return it->second();
			return getAllScanners();
		}
	}




	const SharedTagScannerVector& StaticScannerFactory::getAllScanners() {
		static const SharedTagScannerVector VECTOR = {
			std::make_shared<RiffInfoScanner>(),
			std::make_shared<ASFMetadataScanner>(),
			std::make_shared<ID3TagScanner>(),
			std::make_shared<APETagScanner>()
		};
		return VECTOR;
	}








	const SharedTagScannerVector& StaticScannerFactory::getWaveAudioScanners() {
		static const SharedTagScannerVector VECTOR = {
			std::make_shared<RiffInfoScanner>()
		};
		return VECTOR;
	}

	const SharedTagScannerVector& StaticScannerFactory::getMpegLayer3Scanners() {
		static const SharedTagScannerVector VECTOR = {
			std::make_shared<ID3TagScanner>(),
			std::make_shared<APETagScanner>()
		};
		return VECTOR;
	}

	const SharedTagScannerVector & StaticScannerFactory::getWindowsMediaAudioScanners() {
		static const SharedTagScannerVector VECTOR = {
			std::make_shared<ASFMetadataScanner>()
		};
		return VECTOR;
	}









	const SharedTagScannerVector& StaticScannerFactory::getAllWaveAudioScanners() {
		static const SharedTagScannerVector VECTOR = {
			std::make_shared<RiffInfoScanner>(),
			std::make_shared<ASFMetadataScanner>(),
			std::make_shared<ID3TagScanner>(),
			std::make_shared<APETagScanner>()
		};
		return VECTOR;
	}

	const SharedTagScannerVector& StaticScannerFactory::getAllMpegLayer3Scanners() {
		static const SharedTagScannerVector VECTOR = {
			std::make_shared<ID3TagScanner>(),
			std::make_shared<ASFMetadataScanner>(),
			std::make_shared<APETagScanner>(),
			std::make_shared<RiffInfoScanner>()
		};
		return VECTOR;
	}

	const SharedTagScannerVector & StaticScannerFactory::getAllWindowsMediaAudioScanners() {
		static const SharedTagScannerVector VECTOR = {
			std::make_shared<ASFMetadataScanner>(),
			std::make_shared<RiffInfoScanner>(),
			std::make_shared<ID3TagScanner>(),
			std::make_shared<APETagScanner>()
		};
		return VECTOR;
	}






	const std::unordered_map<std::string, StaticScannerFactory::FunctionType > StaticScannerFactory::MAPPED_SCANNERS = {
		std::make_pair(""s, &StaticScannerFactory::getAllScanners),
		std::make_pair("mp3"s, &StaticScannerFactory::getMpegLayer3Scanners),
		std::make_pair("wav"s, &StaticScannerFactory::getWaveAudioScanners),
		std::make_pair("wave"s, &StaticScannerFactory::getWaveAudioScanners),
		std::make_pair("wma"s, &StaticScannerFactory::getWindowsMediaAudioScanners)
	};

	const std::unordered_map<std::string, StaticScannerFactory::FunctionType > StaticScannerFactory::MAPPED_ALL_SCANNERS = {
		std::make_pair(""s, &StaticScannerFactory::getAllScanners),
		std::make_pair("mp3"s, &StaticScannerFactory::getAllMpegLayer3Scanners),
		std::make_pair("wav"s, &StaticScannerFactory::getAllWaveAudioScanners),
		std::make_pair("wave"s, &StaticScannerFactory::getAllWaveAudioScanners),
		std::make_pair("wma"s, &StaticScannerFactory::getAllWindowsMediaAudioScanners)
	};
}
