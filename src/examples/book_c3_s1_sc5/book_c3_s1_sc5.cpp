#include <glpk.h>

#include "../examples.hpp"

void Examples::bookC3S1Sc5() {
    glp_prob *problem;
    double z, bin1, bin2, bin3, bin4, bin5, aluminium, silicon;

    problem = glp_create_prob();

    glp_read_prob(problem, 0, SRC__EXAMPLES__BOOK_C3_S1_SC5__MODEL_FILE_PATH);

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
        "z = %lf;\nbin1 = %lf;\nbin2 = %lf;\nbin3 = %lf;\nbin4 = %lf;\nbin5 = "
        "%lf;\n"
        "aluminium = %lf;\nsilicon = %lf;\n",
        z, bin1, bin2, bin3, bin4, bin5, aluminium, silicon);

    glp_delete_prob(problem);
}
