#include <glpk.h>

#include "definitions.hpp"
#include "model.hpp"

namespace Model {

    void Model::solve() {
        glp_prob *problem = glp_create_prob();

        glp_set_prob_name(problem, this->name.c_str());

        glp_set_obj_dir(problem, this->objective->getDirection() == Objective::Direction::MINIMIZE ? GLP_MIN : GLP_MAX);

        glp_add_cols(problem, this->variables.size());

        for (auto variable : this->variables) {
            glp_set_col_name(problem, variable.getId(), variable.getName().c_str());

            auto minimum = variable.getMinimum();
            auto maximum = variable.getMaximum();

            if (minimum.has_value() && maximum.has_value()) {
                glp_set_col_bnds(problem, variable.getId(), GLP_DB, minimum.value(), maximum.value());
            } else if (minimum.has_value()) {
                glp_set_col_bnds(problem, variable.getId(), GLP_LO, minimum.value(), 0);
            } else if (maximum.has_value()) {
                glp_set_col_bnds(problem, variable.getId(), GLP_UP, 0, maximum.value());
            } else {
                glp_set_col_bnds(problem, variable.getId(), GLP_FR, 0, 0);
            }

            Coefficient coefficient = this->getVariableCoefficient(variable.getId(), Objective::id);
        }
    }

}  // namespace Model
