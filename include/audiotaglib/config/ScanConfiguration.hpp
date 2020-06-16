#pragma once
#include <filesystem>
#include <audiotaglib/except/FileNotReadableException.hpp>
#include <audiotaglib/except/FileNotWritableException.hpp>
#include <audiotaglib/except/FileParseException.hpp>

namespace audiotaglib::config {
    class ScanConfiguration {
    public:
        bool processUnknownContainerFormats   = false;
        bool searchForAllPossibleTags         = false;

        void saveTo(const std::filesystem::path &iniFilePath) const;
        static ScanConfiguration loadFrom(const std::filesystem::path &iniFilePath);
    };
}