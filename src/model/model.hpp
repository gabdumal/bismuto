#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include <string>
#include <vector>

#include "constraint/constraint.hpp"
#include "objective/objective.hpp"
#include "variable/variable.hpp"

using namespace std;

namespace Model {

    class Model {
        private:
            string name;
            vector<Variable::Variable> variables;
            vector<Constraint::Constraint> constraints;
            Objective::Objective objective;

        public:
            Model(string name, vector<Variable::Variable> variables);
            ~Model() {};
    };

}  // namespace Model

#endif  // __MODEL_HPP__
