#include <glpk.h>

#include <cstdint>

#include "../examples.hpp"

constexpr uint16_t order = 1 + 1000;

void Examples::bookC1S3Sc1() {
    glp_prob *problem;
    int ia[order], ja[order];
    double ar[order * order], z, x1, x2, x3;

    problem = glp_create_prob();
    glp_set_prob_name(problem, "dcc163");
    glp_set_obj_dir(problem, GLP_MAX);

    glp_add_rows(problem, 3);

    glp_set_row_name(problem, 1, "p");
    glp_set_row_bnds(problem, 1, GLP_UP, 0.0, 100.0);

    glp_set_row_name(problem, 2, "q");
    glp_set_row_bnds(problem, 2, GLP_UP, 0.0, 600.0);

    glp_set_row_name(problem, 3, "r");
    glp_set_row_bnds(problem, 3, GLP_UP, 0.0, 300.0);

    glp_add_cols(problem, 3);

    glp_set_col_name(problem, 1, "x1");
    glp_set_col_bnds(problem, 1, GLP_LO, 0.0, 0.0);
    glp_set_obj_coef(problem, 1, 10.0);

    glp_set_col_name(problem, 2, "x2");
    glp_set_col_bnds(problem, 2, GLP_LO, 0.0, 0.0);
    glp_set_obj_coef(problem, 2, 6.0);

    glp_set_col_name(problem, 3, "x3");
    glp_set_col_bnds(problem, 3, GLP_LO, 0.0, 0.0);
    glp_set_obj_coef(problem, 3, 4.0);

    ia[1] = 1, ja[1] = 1, ar[1] = 1.0; /* a[1,1] */
    ia[2] = 1, ja[2] = 2, ar[2] = 1.0; /* a[1,2] */
    ia[3] = 1, ja[3] = 3, ar[3] = 1.0; /* a[1,3] */

    ia[4] = 2, ja[4] = 1, ar[4] = 2.0; /* a[2,1] */
    ia[5] = 2, ja[5] = 2, ar[5] = 1.0; /* a[2,2] */
    ia[6] = 2, ja[6] = 3, ar[6] = 0.0; /* a[2,3] */

    ia[7] = 3, ja[7] = 1, ar[7] = 3.0; /* a[3,1] */
    ia[8] = 3, ja[8] = 2, ar[8] = 4.0; /* a[3,2] */
    ia[9] = 3, ja[9] = 3, ar[9] = 2.0; /* a[3,3] */

    glp_load_matrix(problem, 9, ia, ja, ar);
    glp_simplex(problem, NULL);

    z = glp_get_obj_val(problem);
    x1 = glp_get_col_prim(problem, 1);
    x2 = glp_get_col_prim(problem, 2);
    x3 = glp_get_col_prim(problem, 3);

    glp_printf("z = %g; x1 = %g; x2 = %g; x3 = %g\n", z, x1, x2, x3);

    glp_delete_prob(problem);
}
