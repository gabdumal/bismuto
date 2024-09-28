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

        string model_stem = Util::getStem(model_path);

        string temp_directory = format("{}/temp", Util::getExecutableDirectory());

        // Create a temporary CSV file from the ODS file
        string convert_ods_to_csv = format(
            "{} --headless --convert-to csv:\"Text - txt - csv (StarCalc)\":9,34,76,0,1 {} --outdir {}",
            Constants::Commands::libreoffice, model_path, temp_directory);

        int result = system(convert_ods_to_csv.c_str());
        if (result != 0) {
            throw runtime_error("Failed to convert model.ods to model.csv!");
        }
        cout << endl;

        string model_csv_path = format("{}/{}.csv", temp_directory, model_stem);
        ifstream csv_file(model_csv_path);

        this->readCsv(csv_file);

        // Delete the temporary CSV file
        remove(model_csv_path.c_str());
    }

    void Model::getCanonicalSheet(optional<string> output_directory) {
        string canonical_sheets_path = format("{}/public/canonical.ods", Util::getExecutableDirectory());

        string output_path = format("{}/canonical.ods", output_directory.value_or("."));

        string copy_canonical_sheet = format("cp {} {}", canonical_sheets_path, output_path);

        int result = system(copy_canonical_sheet.c_str());
        if (result != 0) {
            throw runtime_error("Failed to copy canonical.ods to output directory!");
        }
    }

}  // namespace Model
