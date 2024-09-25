#ifndef __OBJECTIVE_HPP__
#define __OBJECTIVE_HPP__

#include <memory>
#include <string>
#include <vector>

#include "../variable/variable.hpp"

using namespace std;

namespace Model {

    namespace Objective {

        enum class Direction { MINIMIZE, MAXIMIZE };

        struct Coefficient {
                shared_ptr<Variable::Variable> variable;
                Value::Value value;
        }

        class Objective {
            private:
                string name;
                Direction direction;
                vector<Coefficient> coefficients;

            public:
                Objective(string name, Direction direction,
                          shared_ptr<vector<shared_ptr<Variable::Variable>>> variables, vector<Value::Value> *values)
                    : name(name), direction(direction) {
                    if (variables->size() != values->size()) {
                        throw invalid_argument("Number of variables and values must be equal");
                    }

                    for (size_t i = 0; i < variables->size(); i++) {
                        Coefficient coefficient = make_pair(variables->at(i), values->at(i));
                        coefficients.push_back(coefficient);
                    }
                }

                ~Objective() = default;

                Direction getDirection() const { return direction; }

                string getName() const { return name; }
        };

    }  // namespace Objective

}  // namespace Model

#endif  // __OBJECTIVE_HPP__
