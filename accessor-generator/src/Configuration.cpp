#include "Configuration.hpp"
#include <boost/program_options.hpp>
#include <filesystem>
#include <iostream>
namespace po = boost::program_options;
namespace fs = std::filesystem;
using namespace std::literals;

static void notify(const Configuration &configuration, po::variables_map &vm) {
    if (!vm.count("csv")) // it's argument, not an option
        throw po::error("the argument 'csv' is required but missing");
    po::notify(vm);
    if (!fs::exists(configuration.csvFile)) {
        throw po::error("file \"" + configuration.csvFile + "\" does not exist");
    }
}

Configuration Configuration::parseConfiguration(int argc, char **argv, bool &help) {
    Configuration configuration;
    po::options_description options("USAGE: accessor-generator [OPTION]... [CSV_FILE]");
    po::options_description hidden;
    po::options_description allOptions;
    po::positional_options_description positional;

    options.add_options()
            ("help", "print usage")
            ("header,h", po::value(&configuration.outputHeaderFile)->default_value("header.hpp"), "output header file")
            ("source,s", po::value(&configuration.outputSourceFile)->default_value("source.cpp"), "output source file");
    hidden.add_options()
            ("csv", po::value(&configuration.csvFile)->required());
    allOptions.add(options).add(hidden);
    positional.add("csv", 1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(allOptions).positional(positional).run(), vm);

    if (vm.count("help")) {
        help = true;
        std::cout << options;
        return configuration;
    } else
        help = false;

    notify(configuration, vm);
    return configuration;
}