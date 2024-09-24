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

string Util::getFormattedBool(bool value) { return value ? "TRUE" : "FALSE"; }

string Util::getTextBetween(string text, optional<string> start,
                            optional<string> end) {
    size_t start_position = 0;
    if (start.has_value()) {
        start_position = text.find(start.value());
        if (start_position == string::npos) {
            return "";
        }
        start_position += start.value().length();
    }

    size_t end_position = text.length();
    if (end.has_value()) {
        end_position = text.find(end.value(), start_position);
        if (end_position == string::npos) {
            return "";
        }
    }

    return text.substr(start_position, end_position - start_position);
}

string Util::getLineContent(int line, string content) {
    istringstream content_stream(content);
    string line_content;
    for (int i = 0; i < line; i++) {
        getline(content_stream, line_content);
    }
    return line_content;
}

string Util::getExecutableDirectory() {
#if defined(_WIN32) || defined(_WIN64)
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
#elif defined(__linux__)
    return std::filesystem::canonical("/proc/self/exe").parent_path().string();
#endif
}

vector<string> Util::rowTokenizer(const string& row) {
    char separator = ',';
    stringstream ss(row);
    string token;
    vector<string> tokens;

    while (getline(ss, token, separator)) {
        tokens.push_back(token);
    }

    return tokens;
}

void Util::printColsData(const unordered_map<string, vector<string>>& cols_data,
                         const vector<string>& cols_names) {
    for (const string& col_name : cols_names) {
        cout << "Dados da coluna: " << col_name << ":" << endl;
        for (const string& dado : cols_data.at(col_name)) {
            cout << dado << " ";
        }
        cout << "\n\n";
    }
}

unordered_map<string, vector<string>> Util::loadCSVData(
    ifstream& target_file, vector<string>& cols_names) {
    unordered_map<string, vector<string>> cols_data;
    string row;
    bool header_row = true;

    while (getline(target_file, row)) {
        vector<string> row_cells = rowTokenizer(row);

        if (header_row) {
            cols_names = row_cells;
            for (const string& name : cols_names) {
                cols_data[name] = vector<string>();
            }
            header_row = false;
            continue;
        }

        if (row_cells.size() != cols_names.size()) {
            cerr << "A linha: " << row << " tem um campo não preenchido"
                 << endl;
            exit(1);
        }

        for (size_t i = 0; i < row_cells.size(); i++) {
            cols_data[cols_names[i]].push_back(row_cells[i]);
        }
    }

    return cols_data;
}
