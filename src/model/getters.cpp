#include "model.hpp"

namespace Model {

    double Model::getVariableCoefficient(Id variable_id, Id constraint_id) {
        if (variable_id < 1 || variable_id > this->variables.size()) {
            throw invalid_argument("Variable ID out of range!");
        }

        if (constraint_id == Objective::id) {
            if (this->objective.has_value()) {
                return this->objective.value().getCoefficient(variable_id);
            }
            throw invalid_argument("Objective has not been set!");
        }

        if (constraint_id < 1 || constraint_id > this->constraints.size()) {
            throw invalid_argument("Constraint ID out of range!");
        }
        return this->constraints[constraint_id - 1].getCoefficient(variable_id);
    }

}  // namespace Model
