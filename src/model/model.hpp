#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include <string>
#include <vector>

#include "constraint/constraint.hpp"
#include "objective/objective.hpp"
#include "value/value.hpp"
#include "variable/variable.hpp"

using namespace std;

namespace Model {

    class Model {
        private:
            string name;
            vector<Variable::Variable> variables;
            bool has_set_all_variables = false;
            vector<Constraint::Constraint> constraints;
            optional<Objective::Objective> objective;

            long last_variable_id = 0;
            long last_constraint_id = 0;

        public:
            Model(string name): name(name) {};
            ~Model() {};

            void setObjective(Objective::Objective objective) { this->objective = objective; }

            void addVariable(string name, DataType data_type, optional<double> minimum, optional<double> maximum) {
                if (data_type == DataType::DOUBLE) {
                    auto minimum_value =
                        minimum.has_value() ? optional<Value::Double>(Value::Double(minimum.value())) : nullopt;
                    auto maximum_value =
                        maximum.has_value() ? optional<Value::Double>(Value::Double(maximum.value())) : nullopt;

                    auto variable = Variable::Double(this->last_variable_id++, name, minimum_value, maximum_value);
                    variables.push_back(variable);

                } else if (data_type == DataType::INTEGER) {
                    optional<Value::Integer> minimum_value;
                    optional<Value::Integer> maximum_value;

                    if (minimum.has_value() && maximum.has_value()) {
                        if (minimum.value() > maximum.value()) {
                            throw invalid_argument("Minimum value must be less than or equal to maximum value!");
                        }
                    }

                    if (minimum.has_value()) {
                        if (minimum.value() != static_cast<int>(minimum.value())) {
                            throw invalid_argument("Minimum value must be an integer!");
                        }
                        minimum_value = optional<Value::Integer>(Value::Integer(minimum.value()));
                    }

                    if (maximum.has_value()) {
                        if (maximum.value() != static_cast<int>(maximum.value())) {
                            throw invalid_argument("Maximum value must be an integer!");
                        }
                        maximum_value = optional<Value::Integer>(Value::Integer(maximum.value()));
                    }

                    auto variable = Variable::Integer(this->last_variable_id++, name, minimum_value, maximum_value);
                    variables.push_back(variable);

                } else {
                    auto variable = Variable::Binary(this->last_variable_id++, name);
                }
            }

            void allVariablesHaveBeenSet() {
                if (this->variables.empty()) {
                    throw invalid_argument("At least one variable must be added to the model!");
                }
                this->has_set_all_variables = true;
            }

            void addConstraint(string name, DataType data_type, vector<double> coefficients,
                               Constraint::Comparision comparision, double compared_value) {
                if (!this->has_set_all_variables) {
                    throw invalid_argument("All variables must be set before adding constraints!");
                }
                auto shared_variables = make_shared<vector<shared_ptr<Variable::Variable>>>();
                Constraint::Constraint constraint(last_constraint_id++, name, data_type, shared_variables, coefficients,
                                                  comparision, compared_value);
            }
    };

}  // namespace Model

#endif  // __MODEL_HPP__
