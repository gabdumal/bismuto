#include <cstdlib>
#include <format>
#include <string>

#include "../../model/model.hpp"
#include "../../util/util.hpp"
#include "../examples.hpp"

using namespace std;

void Examples::livestockDiet() {
    string runtime_directory = format("{}", Util::getExecutableDirectory());
    string model_path = format("{}/examples/livestock_diet/model.ods", runtime_directory);
    string output_directory = format("{}/temp", runtime_directory);

    Model::Model model(model_path);
    model.solve(output_directory);
}
