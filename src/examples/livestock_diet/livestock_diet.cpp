#include <cstdlib>
#include <format>
#include <fstream>
#include <iostream>
#include <string>

#include "../../constants/constants.hpp"
#include "../../model/model.hpp"
#include "../../util/util.hpp"
#include "../examples.hpp"

using namespace std;

void Examples::livestockDiet() {
    string runtime_directory = format("{}/examples/livestock_diet", Util::getExecutableDirectory());

    string convert_ods_to_csv = format(
        "{} --headless --convert-to csv:\"Text - txt - csv (StarCalc)\":9,34,76,0,1 {}/model.ods --outdir {}",
        Constants::Commands::libreoffice, runtime_directory, runtime_directory);

    int result = system(convert_ods_to_csv.c_str());
    if (result != 0) {
        throw runtime_error("Failed to convert model.ods to model.csv!");
    }

    string model_path = format("{}/model.csv", runtime_directory);

    cout << "Reading model from " << model_path << "..." << endl;

    ifstream file(model_path);

    Model::Model model("Livestock Diet");
    model.readCsv(file);

    cout << "Model read successfully!" << endl;
}
