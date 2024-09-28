#include "model.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>

#include "../constants/constants.hpp"
#include "../util/util.hpp"

using namespace std;

namespace Model {

    Model::Model(string model_path) {
        ifstream ods_file(model_path);
        if (!ods_file.is_open()) {
            cerr << "Could not open file " << model_path << endl;
            exit(1);
        }

        string runtime_directory = format("{}/examples/livestock_diet", Util::getExecutableDirectory());

        // Create a temporary CSV file from the ODS file
        string convert_ods_to_csv = format(
            "{} --headless --convert-to csv:\"Text - txt - csv (StarCalc)\":9,34,76,0,1 {}/model.ods --outdir {}",
            Constants::Commands::libreoffice, runtime_directory, runtime_directory);

        int result = system(convert_ods_to_csv.c_str());
        if (result != 0) {
            throw runtime_error("Failed to convert model.ods to model.csv!");
        }

        string model_csv_path = format("{}/model.csv", runtime_directory);
        ifstream csv_file(model_csv_path);

        this->readCsv(csv_file);

        // Delete the temporary CSV file
        remove(model_csv_path.c_str());
    }

}  // namespace Model
