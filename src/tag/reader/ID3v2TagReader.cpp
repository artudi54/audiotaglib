#include "ID3v2TagReader.hpp"
#include <tag/priv/read_util.hpp>
#include <tag/priv/id3/Header.hpp>
#include <tag/priv/id3/Frame.hpp>
#include <tag/priv/id3/FrameProcessor.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/zlib.hpp>
namespace io = boost::iostreams;

namespace tag::reader {
	AudioTagMap ID3v2AudioTagReader::readTag(std::istream & readStream) const {
		if (!priv::readAndEquals(readStream, priv::headers::ID3_V2))
			throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 3);
		readStream.seekg(-3, std::ios::cur);

		AudioTagMap map;
		priv::id3::Header header = priv::id3::Header::readHeader(readStream);
		std::uint32_t leftSize = header.size;

		if (header.tagVersion() == TagContainerFormat::None)
			throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 7);

		if (header.hasExtendedHeader())
			leftSize -= priv::id3::skipExtendedHeaderAndGetSize(readStream);
		if (header.hasFooter())
			leftSize -= 10;

		const std::unordered_map<std::string, priv::id3::SharedFrameProcessor> *PROCESSORS = header.frameProcessors();
		priv::id3::FrameReaderProc readFrame = header.frameReaderProc();
		std::uint32_t framesHeaderSize = header.frameHeaderSize();

		priv::id3::Frame frame;
		while (leftSize > 0) {
			frame = readFrame(readStream);
			if (!frame.identifier[0]) //padding started
				break;
			auto it = PROCESSORS->find(frame.identifier);

			if (it != PROCESSORS->end()) {
				if (frame.isCompressed()) {
					std::vector<char> compressedData(frame.size);
					std::vector<char> decompressedData;
					decompressedData.reserve(frame.size);

					readStream.read(compressedData.data(), frame.size);

					io::array_source source(compressedData.data(), compressedData.size());

					io::filtering_istreambuf filteringBuf;
					filteringBuf.push(source);
					filteringBuf.push(io::zlib_decompressor());

					io::copy(filteringBuf, std::back_inserter(decompressedData));

					source = io::array_source(decompressedData.data(), decompressedData.size());

					io::stream<io::array_source> filteringStream(source);
					it->second->process(filteringStream, map, frame.size);

				} else {
					it->second->process(readStream, map, frame.size);
				}
			} else
				readStream.seekg(frame.size, std::ios::cur);
			leftSize -= framesHeaderSize + frame.size;
		}

        if (header.tagVersion() != TagContainerFormat::ID3v24) {
            auto date = map.getDatePointer();
            if (date != nullptr) {
                if (date->getDate().getYear() == 0 && date->getDate().getMonth() != 0 && date->getDate().getDay() != 0)
                    map.removeTag(AudioTagMap::DATE());
            }
        }

		return map;
	}
}