#pragma once
#include "AudioTagFormat.hpp"
#include "AudioFormat.hpp"
#include "AudioTagMap.hpp"
#include "TagConfiguration.hpp"
#include "StaticScannerFactory.hpp"
#include "StaticReaderFactory.hpp"
#include <experimental/filesystem>
namespace fs = std::filesystem;

namespace tag::manager {

	class TagManager {
	public:
		explicit TagManager(const fs::path &filePath);
		virtual ~TagManager();
		
		const TagConfiguration& getConfiguration() const;
		AudioTagFormat getAudioTagFormat() const;
		const scanner::AudioTagPosVector& getAudioTagPositions() const;
		
		const AudioTagMap& getTagMap() const;
		AudioTagMap& getTagMap();
		void setTagMap(const AudioTagMap &tagMap);

		static scanner::AudioTagPosVector scanFile(const fs::path &filePath, bool allPossible = false);
	protected:
		fs::path filePath;
		SharedTagConfiguration configuration;
	private:
		void read() const;

		mutable bool readingDone;
		mutable AudioTagFormat audioTagFormat;
		mutable scanner::AudioTagPosVector audioTagPositions;
		mutable AudioTagMap tagMap;

		static const TagConfiguration DEFAULT_CONFIGURATION;
	};
	using SharedTagManager = std::shared_ptr<TagManager>;





	class ConfigurableTagManager : public TagManager {
	public:
		explicit ConfigurableTagManager(const fs::path &filePath, const TagConfiguration &configuration = TagConfiguration());
		virtual ~ConfigurableTagManager();

		TagConfiguration& getConfiguration() const;
		void setConfiguration(const TagConfiguration &configuration);
	};




	class SharedConfigTagManager : public TagManager {
	public:
		explicit SharedConfigTagManager(const fs::path &filePath, SharedTagConfiguration configuration);
		virtual ~SharedConfigTagManager();
	};
}

