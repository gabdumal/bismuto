#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include <string>
#include <vector>

#include "constraint/constraint.hpp"
#include "data_type.hpp"
#include "objective/objective.hpp"
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

            long next_variable_id = 1;
            long next_constraint_id = 1;

            void setObjective(Objective::Objective objective) { this->objective = objective; }

            void addVariable(string name, DataType data_type, optional<double> minimum, optional<double> maximum);

            void allVariablesHaveBeenSet();

            void addConstraint(string name, DataType data_type, vector<double> coefficients,
                               Constraint::Comparision comparision, double compared_value);

            void readVariables(ifstream &file);

        public:
            Model(string name): name(name) {};
            ~Model() {};

            void readCsv(ifstream &file);
    };

}  // namespace Model

#endif  // __MODEL_HPP__
