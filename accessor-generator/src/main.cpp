#include <iostream>
#include <fstream>
#include "Configuration.hpp"
#include "Field.hpp"
#include <boost/algorithm/string.hpp>
using namespace std::literals;
namespace fs = std::filesystem;

std::pair<std::ofstream, std::ofstream> outputStreams(const fs::path &outputHeaderFile, const fs::path &outputSourceFile) {
    auto pair = std::make_pair(
            std::ofstream(outputHeaderFile, std::ios::out),
            std::ofstream(outputSourceFile, std::ios::out));
    if (!pair.first.is_open())
        throw fs::filesystem_error("file \"" + outputHeaderFile.string() + "\" is not writable", outputHeaderFile, std::error_code());
    if (!pair.second.is_open())
        throw fs::filesystem_error("file \"" + outputSourceFile.string() + "\" is not writable", outputSourceFile, std::error_code());
    return pair;
}

std::string camelCase(std::string name) {
    name[0] = static_cast<char>(std::tolower(name[0]));
    return name;
}

std::string upperCase(std::string name) {
    boost::to_upper(name);
    return name;
}

std::string pointer(const std::string &type) {
    return "Shared" + type + "AudioTag";
}

std::string pointerConst(const std::string &type) {
    return "SharedConst" + type + "AudioTag";
}

std::string optional(const std::string &type) {
    return "std::optional<" + type + ">";
}

std::string functionGet(const std::string &name) {
    return "get" + name + "()";
}

std::string functionGetOptional(const std::string &name) {
    return "get" + name + "Optional()";
}

std::string functionGetPointer(const std::string &name) {
    return "get" + name + "Pointer()";
}

std::string getImpl(const std::string &name, const std::string &type) {
    return "get" + type + "Tag" + "(" +upperCase(name) + "())";
}

std::string getPointerImpl(const std::string &name, const std::string &type) {
    return "get" + type + "TagPointer" + "(" +upperCase(name) + "())";
}

std::string getOptionalImpl(const std::string &name, const std::string &type) {
    return "get" + type + "TagOptional" + "(" +upperCase(name) + "())";
}

std::string functionSet(const std::string &name, const std::string &type, bool ref = true) {
    if (ref)
        return "set" + name + "(const " + type + "& " + camelCase(name) + ')';
    return "set" + name + "(" + type + ' ' + camelCase(name) + ')';
}

std::string functionSetMove(const std::string &name, const std::string &type) {
    return "set" + name + '(' + type + "&& " + camelCase(name) + ')';
}

std::string functionSetPrimitive(const std::string &name, const std::string &type) {
    return "set" + name + "(" + type + ' ' + camelCase(name) + ')';
}

std::string setImpl(const std::string &name, const std::string &type) {
    return "set" + type + "Tag" + "(" + upperCase(name) + "(), " + camelCase(name) + ")";
}

std::string setMoveImpl(const std::string &name, const std::string &type) {
    return "set" + type + "Tag" + "(" + upperCase(name) + "(), std::move" + camelCase(name) + "))";
}

void writeDeclaration(std::ostream &writeStream, const Field &field) {
    writeStream << pointerConst(field.tagType) << ' ' << functionGetPointer(field.tagName) << " const;\n";
    writeStream << pointer(field.tagType) << ' ' << functionGetPointer(field.tagName) << ";\n";
    writeStream << optional(field.dataType) << ' ' << functionGetOptional(field.tagName) << " const;\n";
    writeStream << field.dataType << ' ' << functionGet(field.tagName) << " const;\n";
    switch (field.setterType) {
        case SetterType::Primitive:
            writeStream << "bool " << functionSetPrimitive(field.tagName, field.dataType) << ";\n";
            break;
        case SetterType::Reference:
            writeStream << "bool " << functionSet(field.tagName, field.dataType) << ";\n";
            break;
        case SetterType::ReferenceMove:
            writeStream << "bool " << functionSet(field.tagName, field.dataType) << ";\n";
            writeStream << "bool " << functionSetMove(field.tagName, field.dataType) << ";\n";
            break;
    }
    writeStream << "\n\n";

}

void writeDefinition(std::ostream &writeStream, const Field &field) {
    writeStream << pointerConst(field.tagType) << " AudioTagMap::" << functionGetPointer(field.tagName) << " const {\n";
    writeStream << "\treturn " << getPointerImpl(field.tagName, field.tagType) << ";\n";
    writeStream << "}\n\n";

    writeStream << pointer(field.tagType) << " AudioTagMap::" << functionGetPointer(field.tagName) << " {\n";
    writeStream << "\treturn " << getPointerImpl(field.tagName, field.tagType) << ";\n";
    writeStream << "}\n\n";

    writeStream << optional(field.dataType) << " AudioTagMap::" << functionGetOptional(field.tagName) << " const {\n";
    writeStream << "\treturn " << getOptionalImpl(field.tagName, field.tagType) << ";\n";
    writeStream << "}\n\n";

    writeStream << field.dataType << " AudioTagMap::" << functionGet(field.tagName) << " const {\n";
    writeStream << "\treturn " << getImpl(field.tagName, field.tagType) << ";\n";
    writeStream << "}\n\n";

    switch (field.setterType) {
        case SetterType::Primitive:
            writeStream << "bool AudioTagMap::" << functionSetPrimitive(field.tagName, field.dataType) << " {\n";
            writeStream << "\treturn " << setImpl(field.tagName, field.tagType) << ";\n";
            writeStream << "}\n\n";
            break;
        case SetterType::Reference:
            writeStream << "bool AudioTagMap::" << functionSet(field.tagName, field.dataType) << " {\n";
            writeStream << "\treturn " << setImpl(field.tagName, field.tagType) << ";\n";
            writeStream << "}\n\n";
            break;
        case SetterType::ReferenceMove:
            writeStream << "bool AudioTagMap::" << functionSet(field.tagName, field.dataType) << " {\n";
            writeStream << "\treturn " << setImpl(field.tagName, field.tagType) << ";\n";
            writeStream << "}\n\n";
            writeStream << "bool AudioTagMap::" << functionSetMove(field.tagName, field.dataType) << " {\n";
            writeStream << "\treturn " << setMoveImpl(field.tagName, field.tagType) << ";\n";

            writeStream << "}\n\n";

            break;
    }

    writeStream << "\n\n";
}

void writeFields(std::ostream &headerWriteStream, std::ostream &sourceWriteStream, const std::vector<Field> &fields) {
    for (auto &field : fields) {
        writeDeclaration(headerWriteStream, field);
        writeDefinition(sourceWriteStream, field);
    }
}

int main(int argc, char **argv) {
    try {
        bool help;
        Configuration configuration = Configuration::parseConfiguration(argc, argv, help);
        if (help)
            return EXIT_SUCCESS;
        std::vector<Field> fields = Field::parseCsvFile(configuration.csvFile);
        auto[headerWriteStream, sourceWriteStream] = outputStreams(configuration.outputHeaderFile, configuration.outputSourceFile);
        writeFields(headerWriteStream, sourceWriteStream, fields);
    }
    catch (std::exception &ex) {
        std::cerr << "accessor-generator: error - " << ex.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}