#ifndef __OBJECTIVE_HPP__
#define __OBJECTIVE_HPP__

#include <vector>

#include "../definitions.hpp"

using namespace std;

namespace Model {

    namespace Objective {

        constexpr Id id = 0;

        enum class Direction { MINIMIZE,
                               MAXIMIZE };

        class Objective {
            private:
                DataType data_type;
                Direction direction;
                vector<Coefficient> coefficients;

            public:
                Objective(DataType data_type, Direction direction, vector<Coefficient> coefficients)
                    : data_type(data_type), direction(direction), coefficients(coefficients) {
                }

                ~Objective() = default;

                DataType getDataType() const { return data_type; }

                Direction getDirection() const { return direction; }

                Coefficient getCoefficient(Id variable_id) {
                    return coefficients[variable_id - 1];
                }
        };

    }  // namespace Objective

}  // namespace Model

#endif  // __OBJECTIVE_HPP__
