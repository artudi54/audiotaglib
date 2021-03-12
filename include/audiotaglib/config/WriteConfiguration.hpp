#pragma once
#include <filesystem>
#include <audiotaglib/except/FileNotReadableException.hpp>
#include <audiotaglib/except/FileNotWritableException.hpp>
#include <audiotaglib/except/FileParseException.hpp>

namespace audiotaglib::config {
    enum class WaveTagFormat : std::uint8_t {
        InfoChunk,
        ID3v2Chunk,
        BothChunks
    };

    enum class ID3v2APEv2Option {
        None,
        APEv2,
        ID3v2
    };

    enum class ID3v2Version : std::uint8_t {
        V3,
        V4
    };

    enum class ID3v2Encoding : std::uint8_t {
        Latin1,
        Utf16BOM,
        Utf16BE,
        Utf8
    };

	class WriteConfiguration {
	public:
		bool				appendID3v1Tag			    = true;
		ID3v2APEv2Option    id3v2APEv2Option            = ID3v2APEv2Option::ID3v2;
		ID3v2Encoding       id3v2Encoding	            = ID3v2Encoding::Utf8;
		ID3v2Version		id3v2Version			    = ID3v2Version::V4;
		bool                preserveModificationTime    = false;
		bool                safeWrite                   = false;
		bool				saveOnDestroy			    = false;
		WaveTagFormat       waveTagFormat			    = WaveTagFormat::BothChunks;

        bool operator==(const WriteConfiguration &rhs) const noexcept;
        bool operator!=(const WriteConfiguration &rhs) const noexcept;

        void saveTo(const std::filesystem::path &iniFilePath) const;
		static WriteConfiguration loadFrom(const std::filesystem::path &iniFilePath);
	};
}