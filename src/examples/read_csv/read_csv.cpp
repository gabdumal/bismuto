#include <cstdlib>
#include <format>
#include <fstream>
#include <iostream>
#include <string>

#include "../../util/util.hpp"
#include "../examples.hpp"

using namespace std;

void Examples::readCsv() {
    string runtime_directory = format("{}/examples/read_csv", Util::getExecutableDirectory());

    string file_name = format("{}/data.csv", runtime_directory);
    std::ifstream target_file(file_name);

    if (!target_file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << file_name << std::endl;
        return;
    }

    vector<string> cols_names;
    unordered_map<string, vector<string>> cols_data = Util::loadCsvData(target_file, cols_names);

    target_file.close();

    Util::printColsData(cols_data, cols_names);
}
