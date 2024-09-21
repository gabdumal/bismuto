#include <glpk.h>

#include <cstdlib>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <util.hpp>

#include "../examples.hpp"

using namespace std;

void Examples::neighbourhoodPlanning() {
    string runtime_directory = format("{}/examples/neighbourhood_planning",
                                      Util::getExecutableDirectory());

    string convert_ods_to_csv = format(
        "libreoffice --headless --convert-to "
        "csv {}/model.ods --outdir {}",
        runtime_directory, runtime_directory);

    int result = system(convert_ods_to_csv.c_str());
    if (result != 0) {
        throw runtime_error("Failed to convert model.ods to model.csv!");
    }

    string model_path = format("{}/model.csv", runtime_directory);
}
