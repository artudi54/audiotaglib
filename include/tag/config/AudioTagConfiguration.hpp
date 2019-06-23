#pragma once
#include <filesystem>
#include <tag/config/ScanConfiguration.hpp>
#include <tag/config/WriteConfiguration.hpp>

namespace tag::config {
    class AudioTagConfiguration {
	public:
		ScanConfiguration scanConfiguration;
		WriteConfiguration writeConfiguration;

		void saveTo(const std::filesystem::path &iniFilePath) const;
		static AudioTagConfiguration loadFrom(const std::filesystem::path &iniFilePath);
	};
}

