#include <cstdlib>
#include <format>
#include <string>

#include "../../model/model.hpp"
#include "../../util/util.hpp"
#include "../examples.hpp"

using namespace std;

void Examples::livestockDiet() {
    string model_path = format("{}/examples/livestock_diet/model.ods", Util::System::getResourcesDirectory());
    string output_directory = format("{}/bismuto", Util::System::getTempDirectory());

    Model::Model model(model_path);
    model.solve(output_directory);
}
