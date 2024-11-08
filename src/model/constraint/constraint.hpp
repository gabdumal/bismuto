#ifndef __CONSTRAINT_HPP__
#define __CONSTRAINT_HPP__

#include <string>
#include <vector>

#include "../definitions.hpp"

using namespace std;

namespace Model {

    namespace Constraint {

        enum Comparision {
            EQUAL,
            LESS_THAN_OR_EQUAL,
            GREATER_THAN_OR_EQUAL
        };

        class Constraint {
            private:
                Id id;
                string name;
                DataType data_type;
                vector<double> coefficients;
                Comparision comparision;
                double compared_to;

            public:
                Constraint(Id id, string name, DataType data_type, vector<double> coefficients, Comparision comparision, double compared_to)
                    : id(id),
                      name(name),
                      data_type(data_type),
                      coefficients(coefficients),
                      comparision(comparision),
                      compared_to(compared_to) {
                }

                ~Constraint() = default;

                Id getId() const { return id; }

                string getName() const { return name; }

                DataType getDataType() const { return data_type; }

                Comparision getComparision() const { return comparision; }

                double getComparedTo() const { return compared_to; }

                double getCoefficient(Id variable_id) const {
                    return coefficients[variable_id - 1];
                }
        };

    }  // namespace Constraint

}  // namespace Model

#endif  // __CONSTRAINT_HPP__
