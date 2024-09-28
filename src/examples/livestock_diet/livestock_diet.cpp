#include <cstdlib>
#include <format>
#include <iostream>
#include <string>

#include "../../constants/constants.hpp"
#include "../../model/model.hpp"
#include "../../util/util.hpp"
#include "../examples.hpp"

using namespace std;

void Examples::livestockDiet() {
    string runtime_directory = format("{}/examples/livestock_diet", Util::getExecutableDirectory());
    string model_path = format("{}/model.ods", runtime_directory);

    Model::Model model(model_path);
    model.solve();
}
