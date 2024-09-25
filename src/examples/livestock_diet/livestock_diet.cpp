#include <cstdlib>
#include <format>
#include <fstream>
#include <iostream>
#include <string>

#include "../../constants/constants.hpp"
#include "../../util/util.hpp"
#include "../examples.hpp"

using namespace std;

void Examples::livestockDiet() {
    string runtime_directory =
        format("{}/examples/livestock_diet", Util::getExecutableDirectory());

    string convert_ods_to_csv = format(
        "{} --headless --convert-to "
        "csv {}/model.ods --outdir {}",
        Constants::Commands::libreoffice, runtime_directory, runtime_directory);

    int result = system(convert_ods_to_csv.c_str());
    if (result != 0) {
        throw runtime_error("Failed to convert model.ods to model.csv!");
    }

    string model_path = format("{}/model.csv", runtime_directory);

    cout << "Reading model from " << model_path << "..." << endl;

    ifstream file(model_path);
    if (!file.is_open()) {
        throw runtime_error("Failed to open model.csv!");
    }

    string line;
    int row = 1;

    // Skip the header
    getline(file, line);

    while (getline(file, line)) {
        size_t pos = 0;
        string token;
        int col = 0;

        while ((pos = line.find(',')) != string::npos) {
            token = line.substr(0, pos);
            line.erase(0, pos + 1);

            if (col == 0) {
                col++;
                continue;
            }

            double value = atof(token.c_str());

            cout << "Row: " << row << ", Col: " << col << ", Value: " << value
                 << endl;

            col++;
        }

        // Process the last token
        if (!line.empty()) {
            double value = atof(line.c_str());
            cout << "Row: " << row << ", Col: " << col << ", Value: " << value
                 << endl;
        }

        row++;
    }

    file.close();
}
