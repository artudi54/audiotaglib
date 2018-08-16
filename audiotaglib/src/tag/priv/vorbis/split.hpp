#pragma once
#include <tuple>
#include <string>
#include <string_view>

namespace tag::priv::vorbis {
    std::tuple<bool, std::string_view, std::string_view> split(const std::string_view &str);
}