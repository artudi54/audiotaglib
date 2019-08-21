#include "write_configuration.hpp"
#include <audiotaglib/priv/config/EnumStringTranslator.hpp>
using namespace std::literals;

namespace audiotaglib::priv::config {
    static const std::string APPEND_ID3V1_TAG           = "WriteConfiguration.AppendID3v1Tag"s;
    static const std::string ID3V2_APEV2_OPTION         = "WriteConfiguration.ID3v2APEv2Option"s;
    static const std::string ID3V2_ENCODING             = "WriteConfiguration.ID3v2Encoding"s;
    static const std::string ID3V2_VERSION              = "WriteConfiguration.ID3v2Version"s;
    static const std::string PRESERVE_MODIFICATION_TIME = "WriteConfiguration.PreserveModificationTime"s;
    static const std::string SAVE_ON_DESTROY            = "WriteConfiguration.SaveOnDestroy"s;
    static const std::string WAVE_TAG_FORMAT            = "WriteConfiguration.WaveTagFormat"s;

    static const EnumStringTranslator<audiotaglib::config::ID3v2APEv2Option > ID3V2_APEV2_OPTION_TRANSLATOR({
        {audiotaglib::config::ID3v2APEv2Option::None,  "None"s},
        {audiotaglib::config::ID3v2APEv2Option::APEv2, "APEv2"s},
        {audiotaglib::config::ID3v2APEv2Option::ID3v2, "ID3v2"s}
    });

    static const EnumStringTranslator<audiotaglib::config::ID3v2Encoding> ID3V2_ENCODING_TRANSLATOR({
        {audiotaglib::config::ID3v2Encoding::Latin1,   "Latin1"s},
        {audiotaglib::config::ID3v2Encoding::Utf16BOM, "Utf16BOM"s},
        {audiotaglib::config::ID3v2Encoding::Utf16BE,  "Utf16BE"s},
        {audiotaglib::config::ID3v2Encoding::Utf8,     "Utf8"s}
    });

    static const EnumStringTranslator<audiotaglib::config::ID3v2Version> ID3V2_VERSION_TRANSLATOR({
        {audiotaglib::config::ID3v2Version::V3, "V3"s},
        {audiotaglib::config::ID3v2Version::V4, "V4"s}
    });

    static const EnumStringTranslator<audiotaglib::config::WaveTagFormat > WAVE_TAG_FORMAT_TRANSLATOR({
        {audiotaglib::config::WaveTagFormat::InfoChunk,  "InfoChunk"s},
        {audiotaglib::config::WaveTagFormat::ID3v2Chunk, "ID3v2Chunk"s},
        {audiotaglib::config::WaveTagFormat::BothChunks, "BothChunks"s}
    });

    void fillPropertyTree(boost::property_tree::ptree &propertyTree,
                          const audiotaglib::config::WriteConfiguration &writeConfiguration) {
        propertyTree.add(APPEND_ID3V1_TAG,           writeConfiguration.appendID3v1Tag);
        propertyTree.add(ID3V2_APEV2_OPTION,         writeConfiguration.id3v2APEv2Option,       ID3V2_APEV2_OPTION_TRANSLATOR);
        propertyTree.add(ID3V2_VERSION,              writeConfiguration.id3v2Version,           ID3V2_VERSION_TRANSLATOR);
        propertyTree.add(ID3V2_ENCODING,             writeConfiguration.id3v2Encoding,          ID3V2_ENCODING_TRANSLATOR);
        propertyTree.add(PRESERVE_MODIFICATION_TIME, writeConfiguration.preserveModificationTime);
        propertyTree.add(SAVE_ON_DESTROY,            writeConfiguration.saveOnDestroy);
        propertyTree.add(WAVE_TAG_FORMAT,            writeConfiguration.waveTagFormat,           WAVE_TAG_FORMAT_TRANSLATOR);
    }

    audiotaglib::config::WriteConfiguration writeConfigurationFromPropertyTree(const boost::property_tree::ptree &propertyTree) {
        audiotaglib::config::WriteConfiguration writeConfiguration;

        writeConfiguration.appendID3v1Tag = propertyTree.get<bool>(
                APPEND_ID3V1_TAG, writeConfiguration.appendID3v1Tag);

        writeConfiguration.id3v2APEv2Option = propertyTree.get<audiotaglib::config::ID3v2APEv2Option >(
                ID3V2_VERSION, writeConfiguration.id3v2APEv2Option, ID3V2_APEV2_OPTION_TRANSLATOR);

        writeConfiguration.id3v2Encoding = propertyTree.get<audiotaglib::config::ID3v2Encoding>(
                ID3V2_ENCODING, writeConfiguration.id3v2Encoding, ID3V2_ENCODING_TRANSLATOR);

        writeConfiguration.id3v2Version = propertyTree.get<audiotaglib::config::ID3v2Version>(
                ID3V2_VERSION, writeConfiguration.id3v2Version, ID3V2_VERSION_TRANSLATOR);

        writeConfiguration.preserveModificationTime = propertyTree.get<bool>(
                PRESERVE_MODIFICATION_TIME, writeConfiguration.preserveModificationTime);

        writeConfiguration.saveOnDestroy = propertyTree.get<bool>(
                SAVE_ON_DESTROY, writeConfiguration.saveOnDestroy);

        writeConfiguration.waveTagFormat = propertyTree.get<audiotaglib::config::WaveTagFormat>(
                WAVE_TAG_FORMAT, writeConfiguration.waveTagFormat, WAVE_TAG_FORMAT_TRANSLATOR);

        return writeConfiguration;
    }
}
