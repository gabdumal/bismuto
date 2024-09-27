#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include <glpk.h>

#include <string>
#include <vector>

#include "constraint/constraint.hpp"
#include "definitions.hpp"
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

            Id next_variable_id = 1;
            Id next_constraint_id = 1;

            /* Getters */

            double getVariableCoefficient(Id variable_id, Id constraint_id);

            /* Setters */

            void setName(string name);

            void setObjective(Objective::Objective objective);

            void addVariable(string name, DataType data_type, optional<double> minimum, optional<double> maximum);
            void allVariablesHaveBeenSet();

            void addConstraint(string name, DataType data_type, vector<double> coefficients, Constraint::Comparision comparision, double compared_to);

            /* Reading from CSV */

            void readVariables(ifstream &file);
            void readObjective(ifstream &file);
            void readConstraints(ifstream &file);

            /* Solving */

            void setObjective(glp_prob *problem);
            void setVariables(glp_prob *problem);
            void setConstraints(glp_prob *problem);

            void printDebugInformation(glp_prob *problem);

        public:
            Model() = default;
            ~Model() = default;

            void readCsv(ifstream &file);
            void solve();
    };

}  // namespace Model

#endif  // __MODEL_HPP__
