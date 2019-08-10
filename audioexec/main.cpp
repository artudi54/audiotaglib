#include <tag/scanner/TagScannerProvider.hpp>
#include <tag/FileManager.hpp>
#include <tag/FileManagerFactory.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>

using namespace std::literals;
namespace fs = std::filesystem;

void test() {
}

//todo: make final review of noexcept (static analysis)
//todo: optimize custom processors
//todo: hide implementation
int main() {
    test();
	std::wcout << "";
    std::ios_base::sync_with_stdio(false);
    for (const fs::directory_entry &entry : fs::directory_iterator("audio")) {
		if (!entry.is_regular_file())
			continue;
		fs::path name = entry.path().filename();
        tag::FileManager manager(entry.path());
        tag::TagMap& tagMap = manager.getTagMap();
		std::cout << "File: " << manager.getContainerFormatString() << ' ' << name << '\n';
		std::cout << "Format: " << manager.getTagContainerFormatsString() << '\n';
        for (auto it = tagMap.begin(); it != tagMap.end(); ++it) {
            if ((*it)->isEmpty())
               continue;

            std::cout << (*it)->getName() << ": ";

            switch (it.getType()) {
            case tag::Tag::Type::String: {
                auto tag = it.as<tag::StringTag>();
                std::cout << tag->getText() << '\n';
            }
            break;

            case tag::Tag::Type::Number: {
                auto tag = it.as<tag::NumberTag>();
                std::cout << tag->getNumber() << '\n';
            }
            break;

            case tag::Tag::Type::Date: {
                auto tag = it.as<tag::DateTag>();
                if (tag->getDate().isYearOnly())
                    std::cout << "Year: " << tag->getDate().getYear() << '\n';
                else
                    std::cout << tag->getDate().getYear() << '.' << tag->getDate().getMonth() << '.'
                              << tag->getDate().getDay() << '\n';
            }
            break;

            case tag::Tag::Type::Image: {
                auto tag = it.as<tag::ImageTag>();
                std::cout << "Type: " << tag::string::toString(tag->getImage().getMimeType()) << "\tDescription: " << tag->getImage().getDescription() << '\n';
            }
            break;

			case tag::Tag::Type::Lyrics: {
				auto tag = it.as<tag::LyricsTag>();
				std::cout << "Description: " << tag->getLyrics().getDescription() << "\tLyrics: " << tag->getLyrics().getLyrics() << '\n';
			}
			break;

			case tag::Tag::Type::ISRC: {
				auto tag = it.as<tag::ISRCTag>();
				std::cout << tag->getISRC().getValue() << '\n';
			}
			break;

            case tag::Tag::Type::Barcode: {
                auto tag = it.as<tag::BarcodeTag>();
                std::cout << tag->getBarcode().getValue() << '\n';
            }
            break;
            }
        }
        std::cout << "\n\n\n";
    }
#ifdef _MSC_VER
	std::system("pause");
#endif
}