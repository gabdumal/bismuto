#ifndef __OBJECTIVE_HPP__
#define __OBJECTIVE_HPP__

#include "../constraint/constraint.hpp"

using namespace std;

namespace Model {

    namespace Objective {

        enum class Direction { MINIMIZE,
                               MAXIMIZE };

        class Objective {
            private:
                DataType data_type;
                Direction direction;
                Coefficients coefficients;

            public:
                Objective(DataType data_type, Direction direction, Coefficients coefficients)
                    : data_type(data_type), direction(direction), coefficients(coefficients) {
                }

                ~Objective() = default;

                DataType getDataType() const { return data_type; }

                Direction getDirection() const { return direction; }
        };

    }  // namespace Objective

}  // namespace Model

#endif  // __OBJECTIVE_HPP__
