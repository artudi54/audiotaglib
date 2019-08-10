#pragma once
#include <filesystem>
#include <tag/config/ScanConfiguration.hpp>
#include <tag/config/WriteConfiguration.hpp>

namespace tag::config {
    class Configuration {
	public:
		ScanConfiguration scanConfiguration;
		WriteConfiguration writeConfiguration;

		void saveTo(const std::filesystem::path &iniFilePath) const;
		static Configuration loadFrom(const std::filesystem::path &iniFilePath);
	};
}

