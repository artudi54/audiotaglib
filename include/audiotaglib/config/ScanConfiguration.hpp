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

        bool operator==(const ScanConfiguration &rhs) const noexcept;
        bool operator!=(const ScanConfiguration &rhs) const noexcept;

        void saveTo(const std::filesystem::path &iniFilePath) const;
        static ScanConfiguration loadFrom(const std::filesystem::path &iniFilePath);
    };
}