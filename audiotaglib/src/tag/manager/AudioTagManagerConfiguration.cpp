#include <tag/manager/AudioTagManagerConfiguration.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <fstream>
namespace pt = boost::property_tree;
namespace fs = std::filesystem;
using namespace std::literals;




namespace tag::manager::priv {
	static const std::string APPEND_ID3V1_TAG = "AudioTagManagerConfiguration.AppendID3v1Tag"s;
	static const std::string ID3V2_VERSION = "AudioTagManagerConfiguration.ID3v2Version"s;
	static const std::string PREFFERED_ID3V2_ENCODING = "AudioTagManagerConfiguration.PrefferedID3v2Encoding"s;
	static const std::string SCAN_ALL_POSSIBLE = "AudioTagManagerConfiguration.ScanAllPossible"s;
	static const std::string SAVE_ON_DESTROY = "AudioTagManagerConfiguration.SaveOnDestroy"s;
	static const std::string WAVE_TAG_FORMAT = "AudioTagManagerConfiguration.WaveTagFormat"s;





	class WaveTagFormatTranslator {
		static const std::string INFO_CHUNK;
		static const std::string ID3_CHUNK;
		static const std::string BOTH_CHUNKS;
	public:
		using internal_type = std::string;
		using external_type = AudioTagManagerConfiguration::WaveTagFormat;

		boost::optional<external_type> get_value(const internal_type &str) {
			if (str == INFO_CHUNK)
				return external_type::InfoChunk;
			if (str == ID3_CHUNK)
				return external_type::ID3Chunk;
			if (str == BOTH_CHUNKS)
				return external_type::BothChunks;
			return boost::optional<external_type>();
		}

		boost::optional<internal_type> put_value(const external_type& waveTagFormat) {
			switch (waveTagFormat) {
			case external_type::InfoChunk:
				return INFO_CHUNK;
			case external_type::ID3Chunk:
				return ID3_CHUNK;
			case external_type::BothChunks:
				return BOTH_CHUNKS;
			default:
				return boost::optional<internal_type>();
			}
		}
	};
	const std::string WaveTagFormatTranslator::INFO_CHUNK = "InfoChunk"s;
	const std::string WaveTagFormatTranslator::ID3_CHUNK = "ID3Chunk"s;
	const std::string WaveTagFormatTranslator::BOTH_CHUNKS = "BothChunks"s;







	class ID3v2VersionTranslator {
		static const std::string V3;
		static const std::string V4;
	public:
		using internal_type = std::string;
		using external_type = AudioTagManagerConfiguration::ID3v2Version;

		boost::optional<external_type> get_value(const internal_type &str) {
			if (str == V3)
				return external_type::V3;
			if (str == V4)
				return external_type::V4;

			return boost::optional<external_type>();
		}

		boost::optional<internal_type> put_value(const external_type& waveTagFormat) {
			switch (waveTagFormat) {
			case external_type::V3:
				return V3;
			case external_type::V4:
				return V4;
			default:
				return boost::optional<internal_type>();
			}
		}
	};
	const std::string ID3v2VersionTranslator::V3 = "V3"s;
	const std::string ID3v2VersionTranslator::V4 = "V4"s;









	class PrefferedID3v2EncodingTranslator {
		static const std::string LATIN1;
		static const std::string UTF16BOM;
		static const std::string UTF16BE;
		static const std::string UTF8;
	public:
		using internal_type = std::string;
		using external_type = AudioTagManagerConfiguration::PrefferedID3v2Encoding;

		boost::optional<external_type> get_value(const internal_type &str) {
			if (str == LATIN1)
				return external_type::Latin1;
			if (str == UTF16BOM)
				return external_type::Utf16BOM;
			if (str == UTF16BE)
				return external_type::Utf16BE;
			if (str == UTF8)
				return external_type::Utf8;
			return boost::optional<external_type>();
		}

		boost::optional<internal_type> put_value(const external_type& waveTagFormat) {
			switch (waveTagFormat) {
			case external_type::Latin1:
				return LATIN1;
			case external_type::Utf16BOM:
				return UTF16BOM;
			case external_type::Utf16BE:
				return UTF16BE;
			case external_type::Utf8:
				return UTF8;
			default:
				return boost::optional<internal_type>();
			}
		}
	};
	const std::string PrefferedID3v2EncodingTranslator::LATIN1 = "Latin1"s;
	const std::string PrefferedID3v2EncodingTranslator::UTF16BOM = "Utf16BOM"s;
	const std::string PrefferedID3v2EncodingTranslator::UTF16BE = "Utf16BE"s;
	const std::string PrefferedID3v2EncodingTranslator::UTF8 = "Utf8"s;

}







namespace tag::manager {


	void AudioTagManagerConfiguration::saveTo(const fs::path & iniFilePath) const {
		pt::ptree propertyTree;


		propertyTree.add(
			priv::APPEND_ID3V1_TAG, appendID3v1Tag);

		propertyTree.add(
			priv::ID3V2_VERSION, id3v2Version, priv::ID3v2VersionTranslator());

		propertyTree.add(
			priv::PREFFERED_ID3V2_ENCODING, prefferedID3v2Encoding, priv::PrefferedID3v2EncodingTranslator());

		propertyTree.add(
			priv::SAVE_ON_DESTROY, saveOnDestroy);

		propertyTree.add(
			priv::SCAN_ALL_POSSIBLE, scanAllPossible);

		propertyTree.add(
			priv::WAVE_TAG_FORMAT, waveTagFormat, priv::WaveTagFormatTranslator());



		try {
			pt::write_ini(iniFilePath.string(), propertyTree);
		}
		catch (pt::ini_parser_error&) {
			throw except::FileNotWritableException(iniFilePath);
		}
	}









	AudioTagManagerConfiguration AudioTagManagerConfiguration::loadFrom(const fs::path & iniFilePath) {
		AudioTagManagerConfiguration configuration;
		pt::ptree propertyTree;

		std::fstream readStream(iniFilePath, std::ios::in);
		if (!readStream.is_open()) {
			readStream.open(iniFilePath, std::ios::in | std::ios::out | std::ios::trunc);
			if (!readStream.is_open())
				throw except::FileNotReadableException(iniFilePath);
		}

		try {
			pt::read_ini(readStream, propertyTree);
		}
		catch (pt::ini_parser_error &ex) {
			throw except::FileParseException(iniFilePath, ex.line(), except::FileParseException::PositionType::Line);
		}



		configuration.appendID3v1Tag = propertyTree.get<bool>(
			priv::APPEND_ID3V1_TAG, configuration.appendID3v1Tag);

		configuration.id3v2Version = propertyTree.get<ID3v2Version>(
			priv::ID3V2_VERSION, configuration.id3v2Version, priv::ID3v2VersionTranslator());

		configuration.prefferedID3v2Encoding = propertyTree.get<PrefferedID3v2Encoding>(
			priv::PREFFERED_ID3V2_ENCODING, configuration.prefferedID3v2Encoding, priv::PrefferedID3v2EncodingTranslator());
		
		configuration.saveOnDestroy = propertyTree.get<bool>(
			priv::SAVE_ON_DESTROY, configuration.saveOnDestroy);

		configuration.scanAllPossible = propertyTree.get<bool>(
			priv::SCAN_ALL_POSSIBLE, configuration.scanAllPossible);

		configuration.waveTagFormat = propertyTree.get<WaveTagFormat>(
			priv::WAVE_TAG_FORMAT, configuration.waveTagFormat, priv::WaveTagFormatTranslator());
		

		return configuration;
	}
}