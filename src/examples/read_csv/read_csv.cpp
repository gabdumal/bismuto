#include <cstdlib>
#include <format>
#include <fstream>
#include <iostream>
#include <string>

#include "../../util/util.hpp"
#include "../examples.hpp"

using namespace std;

void Examples::readCsv() {
    string csv_file_pth = format("{}/examples/read_csv/data.csv", Util::System::getResourcesDirectory());
    std::ifstream csv_file(csv_file_pth);

    if (!csv_file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << csv_file_pth << std::endl;
        return;
    }

    vector<string> cols_names;
    unordered_map<string, vector<string>> cols_data = Util::Csv::loadCsvData(csv_file, cols_names);

    csv_file.close();

    Util::printColsData(cols_data, cols_names);
}
