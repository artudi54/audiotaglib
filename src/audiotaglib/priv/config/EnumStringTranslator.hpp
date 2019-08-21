#pragma once
#include <string>
#include <type_traits>
#include <vector>
#include <unordered_map>
#include <boost/optional.hpp>

namespace audiotaglib::priv::config {
    template < class EnumType >
    class EnumStringTranslator {
        static_assert(std::is_enum_v<EnumType>, "EnumType must be an enumerative type");
    public:
        using internal_type = std::string;
        using external_type = EnumType;
        using integral_type = std::underlying_type_t<EnumType>;
        using value_list_type = std::vector<std::pair<external_type, std::string>>;

        explicit EnumStringTranslator(const value_list_type &valuesList) {
            for (const auto &item : valuesList) {
                stringToEnumMap.emplace(item.second, item.first);
                integralToStringMap.emplace(integral_type(item.first), item.second);
            }
        }

        boost::optional<external_type> get_value(const internal_type &str) const {
            auto it = stringToEnumMap.find(str);
            if (it != stringToEnumMap.end())
                return it->second;
            return boost::optional<external_type>();
        }

        boost::optional<internal_type> put_value(const external_type& enumValue) const {
            auto it = integralToStringMap.find(integral_type(enumValue));
            if (it != integralToStringMap.end())
                return it->second;
            return boost::optional<internal_type>();
        }
    private:
        std::unordered_map<std::string, external_type> stringToEnumMap;
        std::unordered_map<integral_type, std::string> integralToStringMap;
    };
}