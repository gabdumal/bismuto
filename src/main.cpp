#include <argparse/argparse.hpp>
#include <iostream>
#include <string>

#include "../external/pretty_console/pretty_console.hpp"
#include "examples/examples.hpp"
#include "model/model.hpp"

void setArguments(argparse::ArgumentParser &program, std::string &example_name, std::string &model_path) {
    program.add_argument("--version", "-v")
        .help("show program version")
        .default_value(false)
        .implicit_value(true);

    auto &exemple_argument = program.add_argument("--example", "-e")
                                 .help("run example")
                                 .nargs(1)
                                 .store_into(example_name);
    for (const auto &example_name : Examples::examples_names) {
        exemple_argument.choices(example_name);
    }

    program.add_argument("--model", "-m")
        .help("solve model")
        .nargs(1)
        .store_into(model_path);
}

void parseArguments(argparse::ArgumentParser &program, int argc, char *argv[]) {
    try {
        program.parse_args(argc, argv);
    } catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        exit(1);
    }
}

void handleArguments(argparse::ArgumentParser &program, std::string &example_name, std::string &model_path) {
    if (program["--version"] == true) {
        cout << "Version 0.1.0" << endl;
    }

    if (example_name != "") {
        Examples::run(example_name);
    }

    if (model_path != "") {
        Model::Model model(model_path);
        model.solve();
    }
}

int main(int argc, char *argv[]) {
    PrettyConsole::print("Bismuto Optimizer\n",
                         PrettyConsole::Decoration(PrettyConsole::Color::YELLOW, PrettyConsole::Color::DEFAULT,
                                                   PrettyConsole::Format::BOLD),
                         cout);

    argparse::ArgumentParser program("bismuto");
    string example_name = "";
    string model_path = "";

    setArguments(program, example_name, model_path);
    parseArguments(program, argc, argv);
    handleArguments(program, example_name, model_path);

    return 0;
}
