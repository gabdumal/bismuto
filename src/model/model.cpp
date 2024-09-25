#include "model.hpp"

namespace Model {

    Model::Model(string name, vector<Variable::Variable> variables) {
        this->name = name;
        this->variables = variables;
    }

}  // namespace Model
