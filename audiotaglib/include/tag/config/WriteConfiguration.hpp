#pragma once
#include <tag/config/types.hpp>
#include <tag/except/FileNotWritableException.hpp>
#include <tag/except/FileNotReadableException.hpp>
#include <tag/except/FileParseException.hpp>
#include <filesystem>

namespace tag::config {
	class WriteConfiguration {
	public:
		bool					appendID3v1Tag			    = true;
		ID3v2APEv2Option        id3v2APEv2Option            = ID3v2APEv2Option::ID3v2;
		ID3v2Version			id3v2Version			    = ID3v2Version::V4;
		PreferredID3v2Encoding	preferredID3v2Encoding	    = PreferredID3v2Encoding::Utf8;
		bool                    preserveModificationTime    = false;
		bool					saveOnDestroy			    = false;
		WaveTagFormat			waveTagFormat			    = WaveTagFormat::BothChunks;

		void saveTo(const std::filesystem::path &iniFilePath) const;
		static WriteConfiguration loadFrom(const std::filesystem::path &iniFilePath);
	};
}