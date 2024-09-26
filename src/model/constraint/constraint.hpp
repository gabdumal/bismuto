#ifndef __CONSTRAINT_HPP__
#define __CONSTRAINT_HPP__

#include <memory>
#include <string>
#include <vector>

#include "../data_type.hpp"
#include "../variable/variable.hpp"

using namespace std;

namespace Model {

    using Coefficients = vector<double>;

    namespace Constraint {

        enum Comparision { EQUAL,
                           LESS_THAN,
                           GREATER_THAN,
                           LESS_THAN_OR_EQUAL,
                           GREATER_THAN_OR_EQUAL };

        class Constraint {
            private:
                long id;
                string name;
                DataType data_type;
                Coefficients coefficients;
                Comparision comparision;
                double compared_to;

            public:
                Constraint(long id, string name, DataType data_type, Coefficients coefficients, Comparision comparision, double compared_to)
                    : id(id),
                      name(name),
                      data_type(data_type),
                      coefficients(coefficients),
                      comparision(comparision),
                      compared_to(compared_to) {
                }

                ~Constraint() = default;

                long getId() const { return id; }

                string getName() const { return name; }

                DataType getDataType() const { return data_type; }

                Comparision getComparision() const { return comparision; }

                double getComparedValue() const { return compared_to; }
        };

    }  // namespace Constraint

}  // namespace Model

#endif  // __CONSTRAINT_HPP__
