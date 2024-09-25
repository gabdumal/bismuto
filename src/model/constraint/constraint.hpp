#ifndef __CONSTRAINT_HPP__
#define __CONSTRAINT_HPP__

#include <string>
#include <vector>

#include "../variable/variable.hpp"

using namespace std;

namespace Model {

    namespace Constraint {

        enum Comparision { EQUAL, LESS_THAN, GREATER_THAN, LESS_THAN_OR_EQUAL, GREATER_THAN_OR_EQUAL };

        struct Constraint {
                long id;
                string name;
                Value::Value* right_hand_side;
                vector<pair<Variable::Variable*, Value::Value*>> left_hand_side;
        };

        struct Equal: Constraint {
                Comparision comparision = Comparision::EQUAL;
        };

        struct LessThan: Constraint {
                Comparision comparision = Comparision::LESS_THAN;
        };

        struct GreaterThan: Constraint {
                Comparision comparision = Comparision::GREATER_THAN;
        };

        struct LessThanOrEqual: Constraint {
                Comparision comparision = Comparision::LESS_THAN_OR_EQUAL;
        };

        struct GreaterThanOrEqual: Constraint {
                Comparision comparision = Comparision::GREATER_THAN_OR_EQUAL;
        };

    }  // namespace Constraint

}  // namespace Model

#endif  // __CONSTRAINT_HPP__
