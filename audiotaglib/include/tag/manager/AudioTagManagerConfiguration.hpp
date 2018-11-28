#pragma once
#include <memory>
#include <filesystem>
#include <tag/config/ScanConfiguration.hpp>
#include <tag/config/WriteConfiguration.hpp>

namespace tag::manager {
    using namespace config;
    class AudioTagManagerConfiguration {
	public:
		ScanConfiguration readConfiguration;
		WriteConfiguration writeConfiguration;

		void saveTo(const std::filesystem::path &iniFilePath) const;
		static AudioTagManagerConfiguration loadFrom(const std::filesystem::path &iniFilePath);
	};
	using SharedAudioTagManagerConfiguration = std::shared_ptr<AudioTagManagerConfiguration>;
}

