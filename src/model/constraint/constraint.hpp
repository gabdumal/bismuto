#ifndef __CONSTRAINT_HPP__
#define __CONSTRAINT_HPP__

#include <memory>
#include <string>
#include <vector>

#include "../data_type.hpp"
#include "../variable/variable.hpp"

using namespace std;

namespace Model {

    struct Coefficient {
            shared_ptr<Variable::Variable> variable;
            double value;
    };

    using Coefficients = vector<Coefficient>;

    namespace Constraint {

        enum Comparision { EQUAL, LESS_THAN, GREATER_THAN, LESS_THAN_OR_EQUAL, GREATER_THAN_OR_EQUAL };

        using Variables = shared_ptr<vector<shared_ptr<Variable::Variable>>>;

        class Constraint {
            private:
                long id;
                string name;
                DataType data_type;
                Coefficients coefficients;
                Comparision comparision;
                double compared_value;

            public:
                Constraint(long id, string name, DataType data_type, Variables variables, vector<double> coefficients,
                           Comparision comparision, double compared_value)
                    : id(id),
                      name(name),
                      data_type(data_type),
                      comparision(comparision),
                      compared_value(compared_value) {
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

                ~Constraint() = default;
        };

    }  // namespace Constraint

}  // namespace Model

#endif  // __CONSTRAINT_HPP__
