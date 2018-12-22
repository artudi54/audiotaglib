#pragma once
#include <string>

struct Configuration {
    std::string csvFile;
    std::string outputHeaderFile;
    std::string outputSourceFile;
    static Configuration parseConfiguration(int argc, char **argv, bool &help);
};