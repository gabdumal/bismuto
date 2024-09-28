#include <glpk.h>

#include <format>
#include <fstream>

#include "../util/util.hpp"
#include "constraint/constraint.hpp"
#include "definitions.hpp"
#include "model.hpp"

using namespace std;

namespace Model {

    int getGlpDataType(DataType data_type) {
        return data_type == DataType::DOUBLE
                   ? GLP_CV
               : data_type == DataType::INTEGER
                   ? GLP_IV
                   : GLP_BV;
    }

    void writeSolutionToCsv(glp_prob *problem, string output_csv_path) {
        printf("Writing basic solution to '%s'...\n", output_csv_path.c_str());

        int number_of_columns = glp_get_num_cols(problem);

        ofstream output_csv(output_csv_path);
        output_csv << "Variable\tValue\n";

        string objective_name = glp_get_obj_name(problem);
        double objective_value = glp_get_obj_val(problem);
        output_csv << format("{}\t{}\n", objective_name, objective_value);

        for (int i = 1; i <= number_of_columns; i++) {
            string variable_name = glp_get_col_name(problem, i);
            double variable_value = glp_get_col_prim(problem, i);
            output_csv << format("{}\t{}\n", variable_name, variable_value);
        }

        output_csv.close();
    }

    void Model::setObjective(glp_prob *problem) {
        // Set objective function parameters
        glp_set_obj_name(problem, this->objective->getName().c_str());
        glp_set_obj_dir(problem, this->objective->getDirection() == Objective::Direction::MINIMIZE ? GLP_MIN : GLP_MAX);
    }

    void Model::setVariables(glp_prob *problem) {
        glp_add_cols(problem, this->variables.size());
        for (auto variable : this->variables) {
            Id variable_id = variable.getId();

            glp_set_col_name(problem, variable_id, variable.getName().c_str());

            auto glp_data_type = getGlpDataType(variable.getDataType());
            glp_set_col_kind(problem, variable_id, glp_data_type);

            auto minimum = variable.getMinimum();
            auto maximum = variable.getMaximum();
            auto bounds_type = minimum.has_value() && maximum.has_value()
                                   ? GLP_DB
                               : minimum.has_value()
                                   ? GLP_LO
                               : maximum.has_value()
                                   ? GLP_UP
                                   : GLP_FR;
            glp_set_col_bnds(problem, variable_id, bounds_type, minimum.value_or(0), maximum.value_or(0));

            // Set the coefficients of the objective function
            double coefficient = this->getVariableCoefficient(variable_id, Objective::id);
            glp_set_obj_coef(problem, variable_id, coefficient);
        }
    }

    void Model::setConstraints(glp_prob *problem) {
        unsigned int number_of_variables = this->variables.size();
        glp_add_rows(problem, this->constraints.size());

        for (auto constraint : this->constraints) {
            Id constraint_id = constraint.getId();

            glp_set_row_name(problem, constraint_id, constraint.getName().c_str());

            auto comparision = constraint.getComparision();
            auto glp_comparision =
                comparision == Constraint::Comparision::EQUAL
                    ? GLP_FX
                : comparision == Constraint::Comparision::LESS_THAN_OR_EQUAL
                    ? GLP_UP
                    : GLP_LO;

            double compared_to = constraint.getComparedTo();
            glp_set_row_bnds(problem, constraint_id, glp_comparision, compared_to, compared_to);

            // Set the coefficients of the constraint
            int *glp_variables = new int[number_of_variables + 1];
            double *glp_coefficients = new double[number_of_variables + 1];
            glp_variables[0] = 0;
            glp_coefficients[0] = 0;

            for (unsigned int i = 1; i <= number_of_variables; i++) {
                auto variable = this->variables[i - 1];

                Id variable_id = variable.getId();
                double coefficient = constraint.getCoefficient(variable_id);

                glp_variables[i] = variable_id;
                glp_coefficients[i] = coefficient;
            }

            glp_set_mat_row(problem, constraint_id, number_of_variables, glp_variables, glp_coefficients);

            delete[] glp_variables;
            delete[] glp_coefficients;
        }
    }

    void Model::solve(string output_directory) {
        glp_prob *problem = glp_create_prob();

        // Set problem name
        glp_set_prob_name(problem, this->name.c_str());

        this->setObjective(problem);
        this->setVariables(problem);
        this->setConstraints(problem);

        glp_simplex(problem, NULL);
        glp_printf("\n");

        string output_internal_directory = format("{}/{}", output_directory, this->stem);
        Util::createDirectory(output_internal_directory);

        string output_csv_path = format("{}/out.csv", output_internal_directory);
        writeSolutionToCsv(problem, output_csv_path);

        string output_print_path = format("{}/out.txt", output_internal_directory);
        glp_print_sol(problem, output_print_path.c_str());

        double objective_value = glp_get_obj_val(problem);
        glp_printf("\nObjective value: %lf\n", objective_value);

        for (auto variable : this->variables) {
            Id variable_id = variable.getId();
            double variable_value = glp_get_col_prim(problem, variable_id);
            glp_printf("%s: %lf\n", variable.getName().c_str(), variable_value);
        }

        glp_delete_prob(problem);
    }

    void Model::printDebugInformation(glp_prob *problem) {
        int number_of_columns = glp_get_num_cols(problem);
        int number_of_rows = glp_get_num_rows(problem);

        glp_printf("Problem: %s\n\n", glp_get_prob_name(problem));

        glp_printf("Objective: %s\n", glp_get_obj_name(problem));
        glp_printf("Direction: %s\n", glp_get_obj_dir(problem) == GLP_MIN ? "MINIMIZE" : "MAXIMIZE");
        glp_printf("Coefficients: ");
        for (int i = 1; i <= number_of_columns; i++) {
            glp_printf("[%d] %s: %lf; ", i, glp_get_col_name(problem, i), glp_get_obj_coef(problem, i));
        }
        glp_printf("\n\n");

        glp_printf("Variables:\n");
        for (int i = 1; i <= number_of_columns; i++) {
            glp_printf("%s ", glp_get_col_name(problem, i));
            int glp_data_type = glp_get_col_kind(problem, i);

            string data_type = glp_data_type == GLP_CV
                                   ? "DOUBLE"
                               : glp_data_type == GLP_IV
                                   ? "INTEGER"
                                   : "BINARY";
            glp_printf("%s ", data_type.c_str());

            auto bounds_type = glp_get_col_type(problem, i);
            string bounds = bounds_type == GLP_DB
                                ? "DOUBLE BOUNDED"
                            : bounds_type == GLP_LO
                                ? "LOWER BOUNDED"
                            : bounds_type == GLP_UP
                                ? "UPPER BOUNDED"
                                : "FREE";
            glp_printf("%s ", bounds.c_str());

            double minimum = glp_get_col_lb(problem, i);
            double maximum = glp_get_col_ub(problem, i);

            glp_printf("Minimum: %lf; Maximum: %lf;\n", Util::doubleToString(minimum).c_str(), Util::doubleToString(maximum).c_str());
        }
        glp_printf("\n");

        glp_printf("Constraints:\n");
        for (int i = 1; i <= number_of_rows; i++) {
            glp_printf("%s ", glp_get_row_name(problem, i));
            int glp_row_type = glp_get_row_type(problem, i);
            string comparator = glp_row_type == GLP_FX
                                    ? "="
                                : glp_row_type == GLP_UP
                                    ? "<="
                                    : ">=";
            glp_printf("%s ", comparator.c_str());
            double compared_to = glp_get_row_lb(problem, i);
            glp_printf("%s\n", Util::doubleToString(compared_to).c_str());

            int *glp_variables = new int[number_of_columns + 1];
            double *glp_coefficients = new double[number_of_columns + 1];
            int number_of_coefficients = glp_get_mat_row(problem, i, glp_variables, glp_coefficients);

            for (int j = 1; j <= number_of_coefficients; j++) {
                glp_printf("[%d] %s: %lf; ", glp_variables[j], glp_get_col_name(problem, glp_variables[j]), glp_coefficients[j]);
            }
            glp_printf("\n");

            delete[] glp_variables;
            delete[] glp_coefficients;
        }
        glp_printf("\n");
    }

}  // namespace Model
