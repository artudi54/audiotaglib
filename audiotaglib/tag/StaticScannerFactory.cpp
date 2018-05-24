#include "StaticScannerFactory.hpp"
namespace fs = std::filesystem;
using namespace std::literals;

namespace tag::scanner {
	const SharedTagScannerVector& StaticScannerFactory::getScanners(const fs::path & filePath, bool allPossible) {
		if (allPossible) {
			auto it = MAPPED_ALL_PROBES.find(filePath.extension().string());
			if (it != MAPPED_ALL_PROBES.end())
				return it->second();
			return getAllProbes();
		} else {
			auto it = MAPPED_PROBES.find(filePath.extension().string());
			if (it != MAPPED_PROBES.end())
				return it->second();
			return getAllProbes();
		}
	}




	const SharedTagScannerVector& StaticScannerFactory::getAllProbes() {
		static const SharedTagScannerVector VECTOR = {
			std::make_shared<RiffInfoScanner>(),
			std::make_shared<ID3TagScanner>(),
			std::make_shared<APETagScanner>()
		};
		return VECTOR;
	}








	const SharedTagScannerVector& StaticScannerFactory::getWaveAudioProbes() {
		static const SharedTagScannerVector VECTOR = {
			std::make_shared<RiffInfoScanner>()
		};
		return VECTOR;
	}

	const SharedTagScannerVector& StaticScannerFactory::getMpegLayer3Probes() {
		static const SharedTagScannerVector VECTOR = {
			std::make_shared<ID3TagScanner>(),
			std::make_shared<APETagScanner>()
		};
		return VECTOR;
	}









	const SharedTagScannerVector& StaticScannerFactory::getAllWaveAudioProbes() {
		static const SharedTagScannerVector VECTOR = {
			std::make_shared<RiffInfoScanner>(),
			std::make_shared<ID3TagScanner>(),
			std::make_shared<APETagScanner>()
		};
		return VECTOR;
	}

	const SharedTagScannerVector& StaticScannerFactory::getAllMpegLayer3Probes() {
		static const SharedTagScannerVector VECTOR = {
			std::make_shared<ID3TagScanner>(),
			std::make_shared<APETagScanner>(),
			std::make_shared<RiffInfoScanner>()
		};
		return VECTOR;
	}






	const std::unordered_map<std::string, StaticScannerFactory::FunctionType > StaticScannerFactory::MAPPED_PROBES = {
		std::make_pair(""s, &StaticScannerFactory::getAllProbes),
		std::make_pair("mp3"s, &StaticScannerFactory::getMpegLayer3Probes),
		std::make_pair("wav"s, &StaticScannerFactory::getWaveAudioProbes),
		std::make_pair("wave"s, &StaticScannerFactory::getWaveAudioProbes)
	};

	const std::unordered_map<std::string, StaticScannerFactory::FunctionType > StaticScannerFactory::MAPPED_ALL_PROBES = {
		std::make_pair(""s, &StaticScannerFactory::getAllProbes),
		std::make_pair("mp3"s, &StaticScannerFactory::getAllMpegLayer3Probes),
		std::make_pair("wav"s, &StaticScannerFactory::getAllWaveAudioProbes),
		std::make_pair("wave"s, &StaticScannerFactory::getAllWaveAudioProbes)
	};
}
