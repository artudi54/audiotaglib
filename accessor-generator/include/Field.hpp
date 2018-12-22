#pragma once
#include <string>
#include <filesystem>
#include <vector>

enum class SetterType {
    Primitive,
    Reference,
    ReferenceMove
};

struct Field {
    Field(const std::string &tagType, const std::string &tagName, const std::string &dataType, SetterType setterType);

    static std::vector<Field> parseCsvFile(const std::filesystem::path &csvFile);

    std::string tagType;
    std::string tagName;
    std::string dataType;
    SetterType setterType;
};
