#include <functional>
#if defined(_WIN32) || defined(_WIN64)
#    include <windows.h>
#elif defined(__linux__)
#    include <filesystem>
#endif

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "util.hpp"

using namespace std;

string Util::getExecutableDirectory() {
#if defined(_WIN32) || defined(_WIN64)
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    string::size_type pos = string(buffer).find_last_of("\\/");
    return string(buffer).substr(0, pos);
#elif defined(__linux__)
    return filesystem::canonical("/proc/self/exe").parent_path().string();
#endif
}

string Util::getStem(const string& path) {
    filesystem::path fs_path(path);
    return fs_path.stem().string();
}

void Util::createDirectory(const string& path) {
    filesystem::create_directories(path);
}

Util::Row Util::splitIntoTokens(const string& line, char separator, function<bool(const string&)> should_skip,
                                function<bool(const string&)> should_stop) {
    Row tokens;
    size_t current_position = 0;
    unsigned int length = line.length();

    while (current_position < length) {
        size_t next_position = line.find_first_of(separator, current_position);

        string token = line.substr(current_position, next_position - current_position);
        current_position = next_position + 1;

        if (should_skip(token)) {
            continue;
        }
        if (should_stop(token)) {
            break;
        }

        tokens.push_back(token);

        if (next_position == string::npos) {
            break;
        }
    }

    return tokens;
}

unordered_map<string, vector<string>> Util::loadCsvData(ifstream& target_file, vector<string>& cols_names) {
    unordered_map<string, vector<string>> cols_data;
    string row;
    bool header_row = true;

    while (getline(target_file, row)) {
        vector<string> row_cells = splitIntoTokens(row, ',');

        if (header_row) {
            cols_names = row_cells;
            for (const string& name : cols_names) {
                cols_data[name] = vector<string>();
            }
            header_row = false;
            continue;
        }

        if (row_cells.size() != cols_names.size()) {
            cerr << "A linha: " << row << " tem um campo não preenchido" << endl;
            exit(1);
        }

        for (size_t i = 0; i < row_cells.size(); i++) {
            cols_data[cols_names[i]].push_back(row_cells[i]);
        }
    }

    return cols_data;
}

void Util::printColsData(const unordered_map<string, vector<string>>& cols_data, const vector<string>& cols_names) {
    for (const string& col_name : cols_names) {
        cout << "Dados da coluna " << col_name << ":" << endl;
        for (const string& dado : cols_data.at(col_name)) {
            cout << dado << " ";
        }
        cout << "\n\n";
    }
}

/**
 * @brief Converts a string to a double.
 *
 * This function takes a string representation of a number and converts it to a double.
 * It handles strings with spaces and commas, replacing commas with periods to ensure proper conversion.
 *
 * @param token The string to be converted to a double. It must be in the european format, with a comma as the decimal separator.
 * @return The double representation of the input string. Returns 0 if the input string is empty.
 */
double Util::stringToDouble(const string& token) {
    if (token.empty()) {
        return 0;
    }

    string copy = token;
    copy.erase(remove(copy.begin(), copy.end(), ' '), copy.end());

    size_t pos = copy.find(',');
    if (pos != string::npos) {
        copy.replace(pos, 1, ".");
    }

    return stod(copy);
}

string Util::doubleToString(double value) {
    ostringstream oss;
    oss << scientific << value;
    return oss.str();
}
