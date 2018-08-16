#include "split.hpp"

namespace tag::priv::vorbis {

    std::tuple<bool, std::string_view, std::string_view> split(const std::string_view &str) {
        std::size_t pos = str.find('=');

        if (pos == std::string_view::npos)
            return {false, std::string_view(), std::string_view()};

        return {true, str.substr(0, pos), str.substr(pos + 1)};
    }
}