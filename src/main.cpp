#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "util.hpp"

#include "../external/pretty_console/pretty_console.hpp"
#include "examples/examples.hpp"

using std::vector, std::string, std::ifstream, std::cout, std::cerr, std::endl,
    std::unordered_map, std::stringstream;

int main() {

    string file_name = Util::getExecutableDirectory() + "/../../problemsData/dados_exemplo.csv";
    std::ifstream target_file(file_name);

    if (!target_file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << file_name << std::endl;
        return 1;
    }

    vector<string> cols_names;
    unordered_map<string, vector<string>> cols_data = Util::loadCSVData(target_file, cols_names);

    target_file.close();

    Util::printColsData(cols_data, cols_names);

    PrettyConsole::print(
        "Bismuto Optimizer\n",
        PrettyConsole::Decoration(PrettyConsole::Color::YELLOW,
                                  PrettyConsole::Color::DEFAULT,
                                  PrettyConsole::Format::BOLD),
        cout);
    Examples::run(Examples::Example::NEIGHBOURHOOD_PLANNING);

    return 0;
}
