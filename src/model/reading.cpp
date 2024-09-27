#include <glpk.h>

#include <fstream>
#include <functional>
#include <iostream>

#include "../util/util.hpp"
#include "definitions.hpp"
#include "model.hpp"
#include "objective/objective.hpp"

namespace Model {

    constexpr int header_columns = 5;

    /* Auxiliary */

    DataType getDataType(const string &data_type) {
        return data_type == "Real"      ? DataType::DOUBLE
               : data_type == "Inteiro" ? DataType::INTEGER
                                        : DataType::BINARY;
    }

    string readProblemName(string line) {
        unsigned int columns_to_read_on_current_row = 1;

        function<bool(const string &)> should_never_skip =
            [](const string &) { return false; };

        function<bool(const string &)> should_read_only_first_column =
            [&columns_to_read_on_current_row](const string &) {
                return columns_to_read_on_current_row-- == 0;
            };

        Util::Row name = Util::splitIntoTokens(line, '\t', should_never_skip, should_read_only_first_column);

        return name[0];
    }

    Util::Row readVariablesNames(string line) {
        unsigned int headers_to_skip_on_current_row = 5;

        function<bool(const string &)> should_skip_header_column =
            [&headers_to_skip_on_current_row](const string &) {
                if (headers_to_skip_on_current_row == 0) {
                    return false;
                }
                headers_to_skip_on_current_row--;
                return true;
            };

        function<bool(const string &)> should_stop_on_empty_column =
            [&headers_to_skip_on_current_row](const string &token) {
                return headers_to_skip_on_current_row == 0 && token.empty();
            };

        return Util::splitIntoTokens(line, '\t', should_skip_header_column, should_stop_on_empty_column);
    }

    Util::Row readVariablesRow(ifstream &file, unsigned int columns_to_read) {
        string line;
        unsigned int headers_to_skip_on_current_row = 5;

        getline(file, line);

        function<bool(const string &)> should_skip_header_column =
            [&headers_to_skip_on_current_row](const string &) {
                if (headers_to_skip_on_current_row == 0) {
                    return false;
                }
                headers_to_skip_on_current_row--;
                return true;
            };

        function<bool(const string &)> should_stop_when_no_more_columns =
            [&columns_to_read](const string &) {
                return columns_to_read-- == 0;
            };

        return Util::splitIntoTokens(line, '\t', should_skip_header_column, should_stop_when_no_more_columns);
    }

    /* Reading */

    void Model::readCsv(ifstream &file) {
        if (!file.is_open()) {
            cerr << "Erro ao abrir o arquivo!" << endl;
            return;
        }

        string line;
        this->readVariables(file);
        getline(file, line);  // Skip header row
        this->readObjective(file);
        this->readConstraints(file);

        file.close();
    }

    void Model::readVariables(ifstream &file) {
        string line;
        getline(file, line);

        this->setName(readProblemName(line));

        Util::Row names = readVariablesNames(line);
        unsigned int number_of_variables = names.size();

        Util::Row data_types = readVariablesRow(file, names.size());
        if (data_types.size() != number_of_variables) {
            cerr << "Error reading variable data types!" << endl;
            exit(1);
        }

        Util::Row minimum_values = readVariablesRow(file, names.size());
        if (minimum_values.size() != number_of_variables) {
            cerr << "Error reading variable minimum values!" << endl;
            exit(1);
        }

        Util::Row maximum_values = readVariablesRow(file, names.size());
        if (maximum_values.size() != number_of_variables) {
            cerr << "Error reading variable maximum values!" << endl;
            exit(1);
        }

        for (unsigned int i = 0; i < number_of_variables; i++) {
            string name = names[i];
            DataType data_type = getDataType(data_types[i]);
            optional<double> minimum = minimum_values[i].empty() ? nullopt : optional<double>(Util::stringToDouble(minimum_values[i]));
            optional<double> maximum = maximum_values[i].empty() ? nullopt : optional<double>(Util::stringToDouble(maximum_values[i]));

            this->addVariable(name, data_type, minimum, maximum);
        }

        this->allVariablesHaveBeenSet();
    }

    Util::Row readConstraint(ifstream &file, unsigned int number_of_variables) {
        string line;
        getline(file, line);

        unsigned int tokens_to_read_on_current_row = header_columns + number_of_variables;

        function<bool(const string &)>
            should_never_skip = [](const string &) { return false; };

        function<bool(const string &)> should_stop_when_no_more_tokens =
            [&tokens_to_read_on_current_row](const string &) { return tokens_to_read_on_current_row-- == 0; };

        return Util::splitIntoTokens(line, '\t', should_never_skip, should_stop_when_no_more_tokens);
    }

    void Model::readObjective(ifstream &file) {
        if (!this->has_set_all_variables) {
            throw invalid_argument("All variables must be set before adding the objective!");
        }

        unsigned int number_of_variables = this->variables.size();

        Util::Row tokens = readConstraint(file, this->variables.size());
        if (tokens.size() != header_columns + number_of_variables) {
            cerr << "Error reading objective!" << endl;
            exit(1);
        }

        string name = tokens[0];
        DataType data_type = getDataType(tokens[1]);
        Objective::Direction direction =
            tokens[3] == "Max" ? Objective::Direction::MAXIMIZE : Objective::Direction::MINIMIZE;

        vector<double> coefficients;
        for (unsigned int i = 0; i < number_of_variables; i++) {
            string token = tokens[header_columns + i];
            double coefficient = Util::stringToDouble(token);
            coefficients.push_back(coefficient);
        }

        Objective::Objective objective(name, data_type, direction, coefficients);
        this->setObjective(objective);
    }

    void Model::readConstraints(ifstream &file) {
        if (!this->has_set_all_variables) {
            throw invalid_argument("All variables must be set before adding constraints!");
        }

        unsigned int number_of_variables = this->variables.size();
        unsigned int columns_to_read = header_columns + number_of_variables;

        do {
            Util::Row tokens = readConstraint(file, number_of_variables);
            string name = tokens[0];
            if (name.empty()) {
                // Stop reading constraints when an empty line is found
                break;
            }
            if (tokens.size() != columns_to_read) {
                cerr << "Error reading constraints!" << endl;
                exit(1);
            }

            DataType data_type = getDataType(tokens[1]);
            string comparision_as_string = tokens[3];
            Constraint::Comparision comparision =
                comparision_as_string == "="
                    ? Constraint::Comparision::EQUAL
                : comparision_as_string == "<="
                    ? Constraint::Comparision::LESS_THAN_OR_EQUAL
                    : Constraint::Comparision::GREATER_THAN_OR_EQUAL;
            double compared_to = Util::stringToDouble(tokens[4]);

            vector<double> coefficients;
            for (unsigned int i = 0; i < number_of_variables; i++) {
                string token = tokens[header_columns + i];
                double coefficient = Util::stringToDouble(token);
                coefficients.push_back(coefficient);
            }

            this->addConstraint(name, data_type, coefficients, comparision, compared_to);
        } while (!file.eof());
    }

}  // namespace Model
