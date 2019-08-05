#pragma once
#include <tag/except/FileNotWritableException.hpp>
#include <tag/except/FileNotReadableException.hpp>
#include <tag/except/FileParseException.hpp>
#include <filesystem>

namespace tag::config {
    class ScanConfiguration {
    public:
        bool processUnknownContainerFormats   = false;
        bool searchForAllPossibleTags       = false;

        void saveTo(const std::filesystem::path &iniFilePath) const;
        static ScanConfiguration loadFrom(const std::filesystem::path &iniFilePath);
    };
}