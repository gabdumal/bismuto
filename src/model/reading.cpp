#include <fstream>
#include <functional>
#include <iostream>

#include "../util/util.hpp"
#include "model.hpp"
#include "objective/objective.hpp"

namespace Model {

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
        constexpr unsigned int header_columns = 5;
        unsigned int headers_to_read_on_current_row = header_columns;

        function<bool(const string &)> should_skip_header_column =
            [&headers_to_read_on_current_row](const string &) {
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
            [&variables_to_read_on_current_row](const string &) {
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
            should_never_skip = [](const string &) { return false; };

        function<bool(const string &)> should_stop_when_no_more_tokens =
            [&tokens_to_read_on_current_row](const string &) { return tokens_to_read_on_current_row-- == 0; };

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

        vector<Coefficient> coefficients;
        for (unsigned int i = 0; i < number_of_variables; i++) {
            coefficients.push_back(stod(tokens[header_columns + i]));
        }

        Objective::Objective objective(data_type, direction, coefficients);
        this->setObjective(objective);
    }

    void Model::readConstraints(ifstream &file) {
        if (!this->has_set_all_variables) {
            throw invalid_argument("All variables must be set before adding constraints!");
        }

        string line;
        constexpr int header_columns = 5;
        unsigned int number_of_variables = this->variables.size();
        unsigned int tokens_to_read_on_current_row = header_columns + number_of_variables;

        function<bool(const string &)>
            should_never_skip = [](const string &) { return false; };

        function<bool(const string &)> should_stop_when_no_more_tokens =
            [&tokens_to_read_on_current_row](const string &) { return tokens_to_read_on_current_row-- == 0; };

        do {
            getline(file, line);
            Util::Row tokens = Util::splitIntoTokens(line, ',', should_never_skip, should_stop_when_no_more_tokens);

            if (tokens[0].empty()) {
                break;
            }

            if (tokens.size() != header_columns + number_of_variables) {
                cerr << "Error reading constraints!" << endl;
                exit(1);
            }

            string name = tokens[0];
            DataType data_type = tokens[1] == "Real"      ? DataType::DOUBLE
                                 : tokens[1] == "Inteiro" ? DataType::INTEGER
                                                          : DataType::BINARY;
            Constraint::Comparision comparision = tokens[3] == "="    ? Constraint::Comparision::EQUAL
                                                  : tokens[3] == "<"  ? Constraint::Comparision::LESS_THAN
                                                  : tokens[3] == ">"  ? Constraint::Comparision::GREATER_THAN
                                                  : tokens[3] == "<=" ? Constraint::Comparision::LESS_THAN_OR_EQUAL
                                                                      : Constraint::Comparision::GREATER_THAN_OR_EQUAL;
            double compared_to = stod(tokens[4]);

            vector<Coefficient> coefficients;
            for (unsigned int i = 0; i < number_of_variables; i++) {
                coefficients.push_back(stod(tokens[header_columns + i]));
            }

            this->addConstraint(name, data_type, coefficients, comparision, compared_to);
            tokens_to_read_on_current_row = header_columns + number_of_variables;
        } while (!file.eof());
    }

}  // namespace Model
