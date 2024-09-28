#include <glpk.h>

#include <format>
#include <string>

#include "../../util/util.hpp"
#include "../examples.hpp"

using namespace std;

void Examples::bookC3S1Sc5() {
    string model_path = format("{}/examples/book_c3_s1_sc5/model.glpk",
                               Util::System::getResourcesDirectory());

    glp_prob *problem;
    double z, bin1, bin2, bin3, bin4, bin5, aluminium, silicon;

    problem = glp_create_prob();

    glp_read_prob(problem, 0, model_path.c_str());

    glp_simplex(problem, NULL);

    z = glp_get_obj_val(problem);
    bin1 = glp_get_col_prim(problem, 1);
    bin2 = glp_get_col_prim(problem, 2);
    bin3 = glp_get_col_prim(problem, 3);
    bin4 = glp_get_col_prim(problem, 4);
    bin5 = glp_get_col_prim(problem, 5);
    aluminium = glp_get_col_prim(problem, 6);
    silicon = glp_get_col_prim(problem, 7);

    glp_printf(
        "z = %lf;\n"
        "bin1 = %lf;\nbin2 = %lf;\nbin3 = %lf;\n"
        "bin4 = %lf;\nbin5 = %lf;\n"
        "aluminium = %lf;\nsilicon = %lf;\n",
        z, bin1, bin2, bin3, bin4, bin5, aluminium, silicon);

    glp_delete_prob(problem);
}
