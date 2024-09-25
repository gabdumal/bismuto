#ifndef __OBJECTIVE_HPP__
#define __OBJECTIVE_HPP__

#include <memory>
#include <string>
#include <vector>

#include "../constraint/constraint.hpp"
#include "../variable/variable.hpp"

using namespace std;

namespace Model {

    namespace Objective {

        enum class Direction { MINIMIZE, MAXIMIZE };

        class Objective {
            private:
                string name;
                Direction direction;
                Coefficients coefficients;

            public:
                Objective(string name, Direction direction,
                          shared_ptr<vector<shared_ptr<Variable::Variable>>> variables, vector<double> coefficients)
                    : name(name), direction(direction) {
                    if (variables->size() != coefficients.size()) {
                        throw invalid_argument("Number of variables and coefficients must be equal!");
                    }

                    // TODO: Check this later
                    this->coefficients.reserve(variables->size());
                    for (size_t i = 0; i < variables->size(); i++) {
                        Coefficient coefficient{variables->at(i), coefficients.at(i)};
                        this->coefficients.push_back(coefficient);
                    }
                }

                ~Objective() = default;

                Direction getDirection() const { return direction; }

                string getName() const { return name; }
        };

    }  // namespace Objective

}  // namespace Model

#endif  // __OBJECTIVE_HPP__
