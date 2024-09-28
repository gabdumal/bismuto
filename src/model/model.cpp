#include "model.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>

#include "../constants/constants.hpp"
#include "../util/util.hpp"

using namespace std;

namespace Model {

    Model::Model(string model_path) {
        ifstream model_file(model_path);
        if (!model_file.is_open()) {
            cerr << "Could not open file " << model_path << endl;
            exit(1);
        }

        this->stem = Util::System::getStem(model_path);
        string extension = Util::System::getExtension(model_path);
        string model_csv_path = model_path;

        // Convert ODS to CSV if necessary
        if (extension == ".ods") {
            string temp_directory = format("{}/bismuto", Util::System::getTempDirectory());

            // Create a temporary CSV file from the ODS file
            string convert_ods_to_csv = format(
                "{} --headless --convert-to csv:\"Text - txt - csv (StarCalc)\":9,34,76,0,1 {} --outdir {}",
                Constants::Commands::libreoffice, model_path, temp_directory);

            int result = system(convert_ods_to_csv.c_str());
            if (result != 0) {
                throw runtime_error("Failed to convert model.ods to model.csv!");
            }
            cout << endl;
            model_csv_path = format("{}/{}.csv", temp_directory, this->stem);
        } else if (extension != ".csv") {
            throw runtime_error("Model file must be in ODS or CSV format!");
        }

        ifstream csv_file(model_csv_path);
        this->readCsv(csv_file);

        if (extension == ".ods") {
            // Remove the temporary CSV file
            string remove_temp_csv = format("rm {}", model_csv_path);
            int result = system(remove_temp_csv.c_str());
            if (result != 0) {
                throw runtime_error("Failed to remove temporary CSV file!");
            }
        }
    }

    void Model::getCanonicalSheet(optional<string> output_directory) {
        string canonical_sheets_path = format("{}/canonical.ods", Util::System::getResourcesDirectory());

        string output_path = format("{}/canonical.ods", output_directory.value_or("."));

        string copy_canonical_sheet = format("cp {} {}", canonical_sheets_path, output_path);

        int result = system(copy_canonical_sheet.c_str());
        if (result != 0) {
            throw runtime_error("Failed to copy canonical.ods to output directory!");
        }
    }

}  // namespace Model
