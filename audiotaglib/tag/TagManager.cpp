#include "TagManager.hpp"

namespace tag::manager {
	TagManager::TagManager(const fs::path & filePath)
		: filePath(filePath)
		, configuration(const_cast<TagConfiguration*>(&DEFAULT_CONFIGURATION), [](auto) {})
		, readingDone(false)
		, audioTagFormat(AudioTagFormat::None)
		, audioTagPositions()
		, tagMap() {}


	TagManager::~TagManager() {}







	const TagConfiguration & TagManager::getConfiguration() const {
		return *configuration;
	}

	AudioTagFormat TagManager::getAudioTagFormat() const {
		if (!readingDone) {
			read();
			readingDone = true;
		}
		return audioTagFormat;
	}

	const scanner::AudioTagPosVector& TagManager::getAudioTagPositions() const {
		if (!readingDone) {
			read();
			readingDone = true;
		}
		return audioTagPositions;
	}

	const AudioTagMap & TagManager::getTagMap() const {
		if (!readingDone) {
			read();
			readingDone = true;
		}
		return tagMap;
	}

	AudioTagMap & TagManager::getTagMap() {
		if (!readingDone) {
			read();
			readingDone = true;
		}
		return tagMap;
	}

	void TagManager::setTagMap(const AudioTagMap & tagMap) {
		if (!readingDone) {
			read();
			readingDone = true;
		}
		this->tagMap = tagMap;
	}









	scanner::AudioTagPosVector TagManager::scanFile(const fs::path & filePath, bool allPossible) {
		const scanner::SharedTagScannerVector &probes = scanner::StaticScannerFactory::getScanners(filePath);
		std::vector<scanner::AudioTagPosVector> positionVectors;
		positionVectors.reserve(probes.size());

		for (const scanner::SharedTagScanner &probe : probes) {
			scanner::AudioTagPosVector tagPositions = probe->getTagPositions(filePath);
			if (!tagPositions.empty()) {
				positionVectors.push_back(std::move(tagPositions));
				if (probe->isFormatSpecific())
					break;
			}
		}
	
		std::size_t totalSize = 0;
		for (auto &vec : positionVectors)
			totalSize += vec.size();
		
		scanner::AudioTagPosVector concatenatedPositions;
		concatenatedPositions.reserve(totalSize);
		for (auto &vec : positionVectors)
			concatenatedPositions.insert(concatenatedPositions.end(), vec.begin(), vec.end());
		return concatenatedPositions;
	}









	void TagManager::read() const {
		audioTagPositions = scanFile(filePath, configuration->probeAllPossible);
		audioTagFormat = scanner::toFormat(audioTagPositions);
		readingDone = true;
		tagMap.clear();
		for (auto &pos : audioTagPositions) {
			reader::SharedAudioTagReader reader = reader::StaticReaderFactory::getReader(pos.first);
			if (reader != nullptr) {
				std::ifstream fileStream = reader::AudioTagReader::makeStream(filePath, pos.second);
				tagMap.mergeWithOverwrite(reader->readTag(fileStream));
			}
		}
	}






	const TagConfiguration TagManager::DEFAULT_CONFIGURATION;










	ConfigurableTagManager::ConfigurableTagManager(const fs::path & filePath, const TagConfiguration & configuration)
		: TagManager(filePath) {
		this->configuration = std::make_shared<TagConfiguration>(configuration);
	}


	ConfigurableTagManager::~ConfigurableTagManager() {}


	TagConfiguration & ConfigurableTagManager::getConfiguration() const {
		return *configuration;
	}


	void ConfigurableTagManager::setConfiguration(const TagConfiguration & configuration) {
		*this->configuration = configuration;
	}









	SharedConfigTagManager::SharedConfigTagManager(const fs::path & filePath, SharedTagConfiguration configuration)
		: TagManager(filePath){
		this->configuration = configuration;
	}

	SharedConfigTagManager::~SharedConfigTagManager() {}
}
