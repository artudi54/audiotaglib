#pragma once
#include <filesystem>
#include <audiotaglib/config/ScanConfiguration.hpp>
#include <audiotaglib/config/WriteConfiguration.hpp>

namespace audiotaglib::config {
    class Configuration {
	public:
		ScanConfiguration scanConfiguration;
		WriteConfiguration writeConfiguration;

		void saveTo(const std::filesystem::path &iniFilePath) const;
		static Configuration loadFrom(const std::filesystem::path &iniFilePath);
	};
}

