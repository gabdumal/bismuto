#include "definitions.hpp"
#include "model.hpp"

namespace Model {

    void Model::setName(string name) {
        if (!this->name.empty()) {
            throw invalid_argument("Name has already been set!");
        }
        this->name = name;
    }

    void Model::setObjective(Objective::Objective objective) {
        if (this->objective.has_value()) {
            throw invalid_argument("Objective has already been set!");
        }
        this->objective = objective;
    }

    void Model::addVariable(string name, DataType data_type, optional<double> minimum, optional<double> maximum) {
        if (this->has_set_all_variables) {
            throw invalid_argument("All variables have already been set!");
        }

        if (data_type == DataType::BINARY) {
            auto variable = Variable::Binary(this->next_variable_id++, name);
            variables.push_back(variable);
            return;
        }

        // Guarantee that all the variables are non negative

        if (minimum.has_value()) {
            if (minimum.value() < 0) {
                throw invalid_argument("Minimum value must be greater than or equal to 0!");
            }
        } else {
            minimum = 0;
        }

        if (maximum.has_value() && maximum.value() < 0) {
            throw invalid_argument("Maximum value must be greater than or equal to 0!");
        }

        if (minimum.has_value() && maximum.has_value()) {
            if (minimum.value() > maximum.value()) {
                throw invalid_argument("Minimum value must be less than or equal to maximum value!");
            }
        }

        if (data_type == DataType::INTEGER) {
            auto variable = Variable::Integer(this->next_variable_id++, name, minimum, maximum);
            variables.push_back(variable);
            return;
        }

        auto variable = Variable::Double(this->next_variable_id++, name, minimum, maximum);
        variables.push_back(variable);
    }

    void Model::allVariablesHaveBeenSet() {
        if (this->variables.empty()) {
            throw invalid_argument("At least one variable must be added to the model!");
        }
        this->has_set_all_variables = true;
    }

    void Model::addConstraint(string name, DataType data_type, vector<double> coefficients, Constraint::Comparision comparision, double compared_to) {
        if (!this->has_set_all_variables) {
            throw invalid_argument("All variables must be set before adding constraints!");
        }
        Constraint::Constraint constraint(next_constraint_id++, name, data_type, coefficients, comparision, compared_to);
        this->constraints.push_back(constraint);
    }

}  // namespace Model
