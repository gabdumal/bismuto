#include <argparse/argparse.hpp>
#include <iostream>
#include <string>

#include "../external/pretty_console/pretty_console.hpp"
#include "examples/examples.hpp"
#include "model/model.hpp"

void setArguments(argparse::ArgumentParser &program, std::string &example_name, std::string &input_path, std::string &output_path) {
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
        .help("solve model given input path")
        .nargs(1)
        .store_into(input_path);

    program.add_argument("--get-sheet", "-g")
        .help("get canonical sheet to describe the model")
        .flag();

    program.add_argument("--output", "-o")
        .help("set output path")
        .nargs(1)
        .store_into(output_path);
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

void handleArguments(argparse::ArgumentParser &program, std::string &example_name, std::string &input_path, std::string &output_path) {
    if (program["--version"] == true) {
        cout << "Version 0.1.0" << endl;
        return;
    }

    if (example_name != "") {
        PrettyConsole::print("Running ",
                             PrettyConsole::Decoration(),
                             cout);

        PrettyConsole::print(
            "example",
            PrettyConsole::Decoration(
                PrettyConsole::Color::CYAN, PrettyConsole::Color::DEFAULT, PrettyConsole::Format::BOLD),
            cout);

        PrettyConsole::print(
            format(": {}\n\n", example_name),
            PrettyConsole::Decoration(),
            cout);

        Examples::run(example_name);
        return;
    }

    if (input_path != "") {
        PrettyConsole::print("Solving ",
                             PrettyConsole::Decoration(),
                             cout);

        PrettyConsole::print(
            "model\n",
            PrettyConsole::Decoration(
                PrettyConsole::Color::CYAN, PrettyConsole::Color::DEFAULT, PrettyConsole::Format::BOLD),
            cout);

        PrettyConsole::print(
            format("{}Input path: {}\n{}Output path: {}\n", PrettyConsole::tab, input_path, PrettyConsole::tab, output_path),
            PrettyConsole::Decoration(),
            cout);

        Model::Model model(input_path);
        string output_directory = output_path == "" ? "." : output_path;
        model.solve(output_directory);
        return;
    }

    if (program["--get-sheet"] == true) {
        PrettyConsole::print("Getting ",
                             PrettyConsole::Decoration(),
                             cout);

        PrettyConsole::print(
            "canonical",
            PrettyConsole::Decoration(
                PrettyConsole::Color::CYAN, PrettyConsole::Color::DEFAULT, PrettyConsole::Format::BOLD),
            cout);

        PrettyConsole::print(" sheet.\n",
                             PrettyConsole::Decoration(),
                             cout);

        string output_directory = output_path == "" ? "." : output_path;
        Model::Model::getCanonicalSheet(output_directory);
        return;
    }
}

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("bismuto");
    string example_name = "";
    string input_path = "";
    string output_path = "";

    PrettyConsole::print("Bismuto Optimizer\n",
                         PrettyConsole::Decoration(PrettyConsole::Color::YELLOW, PrettyConsole::Color::DEFAULT,
                                                   PrettyConsole::Format::BOLD),
                         cout);

    setArguments(program, example_name, input_path, output_path);
    parseArguments(program, argc, argv);
    handleArguments(program, example_name, input_path, output_path);

    return 0;
}
