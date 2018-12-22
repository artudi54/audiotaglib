#include "Field.hpp"
#include <fstream>
#include <boost/algorithm/string.hpp>
namespace fs = std::filesystem;

Field::Field(const std::string &tagType, const std::string &tagName, const std::string &dataType, SetterType setterType)
    : tagType(tagType), tagName(tagName), dataType(dataType), setterType(setterType) {}

std::vector<Field> Field::parseCsvFile(const fs::path &csvFile) {
    std::ifstream readStream(csvFile, std::ios::in);
    std::string line;
    std::vector<Field> fields;
    if (!readStream.is_open())
        throw fs::filesystem_error("file \"" + csvFile.string() + "\" is not readable", csvFile, std::error_code());
    while (std::getline(readStream, line)) {
        boost::trim(line);
        if (line.empty())
            continue;
        std::vector<std::string> params;
        boost::split(params, line, boost::is_any_of(","), boost::token_compress_on);
        if (params.size() != 4)
            throw std::runtime_error("Could not parse \"" + csvFile.string() +'"');
        fields.emplace_back(params[0], params[1], params[2], static_cast<SetterType>(std::stoi(params[3])));
    }
    return fields;
}


