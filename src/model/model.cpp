#include "model.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "../util/util.hpp"
#include "constraint/constraint.hpp"
#include "objective/objective.hpp"

using namespace std;

namespace Model {

    void Model::addVariable(string name, DataType data_type, optional<double> minimum, optional<double> maximum) {
        if (this->has_set_all_variables) {
            throw invalid_argument("All variables have already been set!");
        }

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

    void Model::addConstraint(string name, DataType data_type, Coefficients coefficients, Constraint::Comparision comparision, double compared_value) {
        if (!this->has_set_all_variables) {
            throw invalid_argument("All variables must be set before adding constraints!");
        }
        Constraint::Constraint constraint(next_constraint_id++, name, data_type, coefficients, comparision, compared_value);
    }

    void Model::readCsv(ifstream &file) {
        if (!file.is_open()) {
            cerr << "Erro ao abrir o arquivo!" << endl;
            return;
        }

        string line;
        this->readVariables(file);
        getline(file, line);  // Skip header row
        this->readObjective(file);

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

        function<bool(const string &)> should_stop_on_empty_column =
            [&headers_to_read_on_current_row](const string &token) {
                return headers_to_read_on_current_row == 0 && token.empty();
            };

        getline(file, line);
        Util::Row names = Util::splitIntoTokens(line, ',', should_skip_header_column, should_stop_on_empty_column);
        headers_to_read_on_current_row = header_columns;

        unsigned int number_of_variables = names.size();
        unsigned int variables_to_read_on_current_row = number_of_variables;

        function<bool(const string &)> should_stop_when_no_more_variables =
            [&variables_to_read_on_current_row](const string &token) {
                return variables_to_read_on_current_row-- == 0;
            };

        getline(file, line);
        Util::Row data_types =
            Util::splitIntoTokens(line, ',', should_skip_header_column, should_stop_when_no_more_variables);
        if (data_types.size() != number_of_variables) {
            cerr << "Error reading variable data types!" << endl;
            exit(1);
        }
        headers_to_read_on_current_row = header_columns;
        variables_to_read_on_current_row = number_of_variables;

        getline(file, line);
        Util::Row minimum_values =
            Util::splitIntoTokens(line, ',', should_skip_header_column, should_stop_when_no_more_variables);
        if (minimum_values.size() != number_of_variables) {
            cerr << "Error reading variable minimum values!" << endl;
            exit(1);
        }
        headers_to_read_on_current_row = header_columns;
        variables_to_read_on_current_row = number_of_variables;

        getline(file, line);
        Util::Row maximum_values =
            Util::splitIntoTokens(line, ',', should_skip_header_column, should_stop_when_no_more_variables);
        if (maximum_values.size() != number_of_variables) {
            cerr << "Error reading variable maximum values!" << endl;
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

    void Model::readObjective(ifstream &file) {
        if (!this->has_set_all_variables) {
            throw invalid_argument("All variables must be set before adding the objective!");
        }

        string line;
        constexpr int header_columns = 5;
        unsigned int number_of_variables = this->variables.size();
        unsigned int tokens_to_read_on_current_row = header_columns + number_of_variables;

        function<bool(const string &)>
            should_never_skip = [](const string &token) { return false; };

        function<bool(const string &)> should_stop_when_no_more_tokens =
            [&tokens_to_read_on_current_row](const string &token) { return tokens_to_read_on_current_row-- == 0; };

        getline(file, line);
        Util::Row tokens = Util::splitIntoTokens(line, ',', should_never_skip, should_stop_when_no_more_tokens);
        if (tokens.size() != header_columns + number_of_variables) {
            cerr << "Error reading objective!" << endl;
            exit(1);
        }

        DataType data_type = tokens[1] == "Real"      ? DataType::DOUBLE
                             : tokens[1] == "Inteiro" ? DataType::INTEGER
                                                      : DataType::BINARY;
        Objective::Direction direction =
            tokens[3] == "Max" ? Objective::Direction::MAXIMIZE : Objective::Direction::MINIMIZE;

        Coefficients coefficients;
        for (unsigned int i = 0; i < number_of_variables; i++) {
            coefficients.push_back(stod(tokens[header_columns + i]));
        }

        Objective::Objective objective(data_type, direction, coefficients);
        this->setObjective(objective);
    }

}  // namespace Model
