#include <tag/scanner/StaticScannerFactory.hpp>
#include "tag/manager/AudioTagManager.hpp"
#include "tag/AudioTagMap.hpp"
#include "tag/AudioFileInformation.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>
using namespace std::literals;
namespace fs = std::filesystem;


//todo: make final review of noexcept (static analysis)
int main() {
    std::ios_base::sync_with_stdio(false);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    for (const fs::directory_entry &entry : fs::recursive_directory_iterator(fs::path("."))) {
		fs::path name = entry.path().filename();
        std::chrono::steady_clock::time_point tp1 = std::chrono::steady_clock::now();
        tag::manager::AudioTagManager manager(entry.path());
		manager.getConfiguration().saveTo("file.ini");
        tag::AudioTagMap& tagMap = manager.getTagMap();
		std::chrono::steady_clock::time_point tp2 = std::chrono::steady_clock::now();
		std::cout << "File: " << manager.getAudioContainerFormatString() << ' ';
		std::wcout << name << '\n';
		std::cout << "Format: " << manager.getAudioTagFormatString() << '\n';
        for (auto it = tagMap.begin(); it != tagMap.end(); ++it) {
            if ((*it)->isNull())
                continue;

            std::cout << (*it)->getName() << ": ";

            switch (it.getType()) {
            case tag::AudioTag::Type::String: {
                auto tag = it.as<tag::StringAudioTag>();
                std::cout << tag->getText() << '\n';
            }
            break;

            case tag::AudioTag::Type::Number: {
                auto tag = it.as<tag::NumberAudioTag>();
                std::cout << tag->getNumber() << '\n';
            }
            break;

            case tag::AudioTag::Type::Date: {
                auto tag = it.as<tag::DateAudioTag>();
                if (tag->getDate().isYearOnly())
                    std::cout << "Year: " << tag->getDate().getYear() << '\n';
                else
                    std::cout << tag->getDate().getYear() << '.' << tag->getDate().getMonth() << '.'
                              << tag->getDate().getDay() << '\n';
            }
            break;

            case tag::AudioTag::Type::Image: {
                auto tag = it.as<tag::ImageAudioTag>();
                std::cout << "Type: " << tag::string::toString(tag->getImage().getMimeType()) << "\tDescription: " << tag->getImage().getDescription() << '\n';
            }
            break;

			case tag::AudioTag::Type::Lyrics: {
				auto tag = it.as<tag::LyricsAudioTag>();
				std::cout << "Description: " << tag->getLyrics().getDescription() << "\tLyrics: " << tag->getLyrics().getLyrics() << '\n';
			}
			break;

			case tag::AudioTag::Type::ISRC: {
				auto tag = it.as<tag::ISRCAudioTag>();
				std::cout << tag->getISRC().getValue() << '\n';
			}
			break;

            default:
                break;
            }
        }
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(tp2 - tp1).count();
        std::cout << "\n\n\n";
    }
    system("pause");
}