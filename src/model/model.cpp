#include "model.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "../util/util.hpp"

using namespace std;

namespace Model {

    void Model::addVariable(string name, DataType data_type, optional<double> minimum, optional<double> maximum) {
        if (data_type == DataType::BINARY) {
            auto variable = Variable::Binary(this->next_variable_id++, name);
            variables.push_back(variable);
            return;
        }

        if (minimum.has_value() && maximum.has_value()) {
            if (minimum.value() > maximum.value()) {
                throw invalid_argument("Minimum value must be less than or equal to maximum value!");
            }
        }

        if (data_type == DataType::INTEGER) {
            auto variable = Variable::Integer(this->next_variable_id++, name, minimum, maximum);
            variables.push_back(variable);
            return;
        }

        auto variable = Variable::Double(this->next_variable_id++, name, minimum, maximum);
        variables.push_back(variable);
    }

    void Model::allVariablesHaveBeenSet() {
        if (this->variables.empty()) {
            throw invalid_argument("At least one variable must be added to the model!");
        }
        this->has_set_all_variables = true;
    }

    void Model::addConstraint(string name, DataType data_type, vector<double> coefficients,
                              Constraint::Comparision comparision, double compared_value) {
        if (!this->has_set_all_variables) {
            throw invalid_argument("All variables must be set before adding constraints!");
        }
        auto shared_variables = make_shared<vector<shared_ptr<Variable::Variable>>>();
        Constraint::Constraint constraint(next_constraint_id++, name, data_type, shared_variables, coefficients,
                                          comparision, compared_value);
    }

    void Model::readCsv(ifstream &file) {
        if (!file.is_open()) {
            cerr << "Erro ao abrir o arquivo!" << endl;
            return;
        }

        this->readVariables(file);

        file.close();
    }

    void Model::readVariables(ifstream &file) {
        string line;
        constexpr unsigned int header_columns = 5;
        unsigned int headers_to_read_on_current_row = header_columns;

        function<bool(const string &)> should_skip_header_column =
            [&headers_to_read_on_current_row](const string &token) {
                if (headers_to_read_on_current_row == 0) {
                    return false;
                }
                headers_to_read_on_current_row--;
                return true;
            };

        function<bool(const string &)> should_break_on_empty_column =
            [&headers_to_read_on_current_row](const string &token) {
                return headers_to_read_on_current_row == 0 && token.empty();
            };

        getline(file, line);
        Util::Row names = Util::splitIntoTokens(line, ',', should_skip_header_column, should_break_on_empty_column);
        headers_to_read_on_current_row = header_columns;

        unsigned int number_of_variables = names.size();
        unsigned int variables_to_read_on_current_row = number_of_variables;

        function<bool(const string &)> should_break_when_no_more_variables =
            [&variables_to_read_on_current_row](const string &token) {
                return variables_to_read_on_current_row-- == 0;
            };

        getline(file, line);
        Util::Row data_types =
            Util::splitIntoTokens(line, ',', should_skip_header_column, should_break_when_no_more_variables);
        if (data_types.size() != number_of_variables) {
            cerr << "Erro ao ler os tipos das variáveis!" << endl;
            exit(1);
        }
        headers_to_read_on_current_row = header_columns;
        variables_to_read_on_current_row = number_of_variables;

        getline(file, line);
        Util::Row minimum_values =
            Util::splitIntoTokens(line, ',', should_skip_header_column, should_break_when_no_more_variables);
        if (minimum_values.size() != number_of_variables) {
            cerr << "Erro ao ler os valores mínimos das variáveis!" << endl;
            exit(1);
        }
        headers_to_read_on_current_row = header_columns;
        variables_to_read_on_current_row = number_of_variables;

        getline(file, line);
        Util::Row maximum_values =
            Util::splitIntoTokens(line, ',', should_skip_header_column, should_break_when_no_more_variables);
        if (maximum_values.size() != number_of_variables) {
            cerr << "Erro ao ler os valores máximos das variáveis!" << endl;
            exit(1);
        }

        for (unsigned int i = 0; i < number_of_variables; i++) {
            string name = names[i];
            DataType data_type = data_types[i] == "Real"      ? DataType::DOUBLE
                                 : data_types[i] == "Inteiro" ? DataType::INTEGER
                                                              : DataType::BINARY;
            optional<double> minimum = minimum_values[i].empty() ? nullopt : optional<double>(stod(minimum_values[i]));
            optional<double> maximum = maximum_values[i].empty() ? nullopt : optional<double>(stod(maximum_values[i]));

            this->addVariable(name, data_type, minimum, maximum);
        }
        this->allVariablesHaveBeenSet();
    }

}  // namespace Model
