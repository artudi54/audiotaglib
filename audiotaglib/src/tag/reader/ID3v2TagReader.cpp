#include <tag/reader/ID3v2TagReader.hpp>
#include <tag/priv/read_util.hpp>
#include <tag/priv/id3/Header.hpp>
#include <tag/priv/id3/Frame.hpp>
#include <tag/priv/id3/FrameProcessor.hpp>
#include <boost/iostreams/stream.hpp>
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
		unsigned leftSize = header.size;

		if (header.tagVersion() == AudioTagFormat::None)
			throw except::StreamParseException(std::uint64_t(readStream.tellg()) - 7);

		if (header.hasExtendedHeader())
			leftSize -= priv::id3::skipExtendedHeaderAndGetSize(readStream);
		if (header.hasFooter())
			leftSize -= 10;

		const std::unordered_map<std::string, priv::id3::SharedFrameProcessor> *PROCESSORS = header.frameProcessors();
		priv::id3::FrameReaderProc readFrame = header.frameReaderProc();
		unsigned framesHeaderSize = header.frameHeaderSize();


		priv::id3::Frame frame;
		while (leftSize > 0) {
			frame = readFrame(readStream);
			if (!frame.identifier[0]) //padding started
				break;
			auto it = PROCESSORS->find(frame.identifier);
			if (it != PROCESSORS->end()) {
				io::array_source source(reinterpret_cast<char*>(frame.data.data()), frame.size);
				io::filtering_istreambuf filteringBuf;
				if (frame.isCompressed())
					filteringBuf.push(io::zlib_decompressor());
				filteringBuf.push(source);

				std::istream stream(&filteringBuf);
				it->second->process(stream, map, frame.size);
			}
			leftSize -= framesHeaderSize + frame.size;
		}
		return map;
	}

}