#if defined(_WIN32) || defined(_WIN64)
#    include <windows.h>
#elif defined(__linux__)
#    include <limits.h>
#    include <unistd.h>

#    include <filesystem>
#endif

#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "util.hpp"
#include "version.h"

using namespace std;

namespace Util {

    namespace Project {

        string getVersion() {
            return to_string(BISMUTO_VERSION_MAJOR) + "." +
                   to_string(BISMUTO_VERSION_MINOR) + "." +
                   to_string(BISMUTO_VERSION_PATCH);
        }

    }  // namespace Project

    namespace System {

        string getResourcesDirectory() {
            char result[PATH_MAX];
            ssize_t count = 0;

#if defined(_WIN32) || defined(_WIN64)
            count = GetModuleFileName(NULL, result, MAX_PATH);
#else
            count = readlink("/proc/self/exe", result, PATH_MAX);
#endif
            string exe_path = string(result, (count > 0) ? count : 0);
            // Get the directory of the executable
            string exe_dir = filesystem::path(exe_path).parent_path().string();

            // Construct the path to the resources directory
            string resources_dir = exe_dir + "/../share/bismuto";
            return resources_dir;
        }

        string getTempDirectory() {
#if defined(_WIN32) || defined(_WIN64)
            char temp_path[MAX_PATH];
            DWORD path_len = GetTempPath(MAX_PATH, temp_path);

            if (path_len == 0 || path_len > MAX_PATH) {
                throw runtime_error("Failed to get the temporary directory path");
            }
            return string(temp_path);
#else
            const char* temp_path = getenv("TMPDIR");
            if (temp_path == nullptr) {
                temp_path = "/tmp";
            }
            return string(temp_path);
#endif
        }

        string getStem(const string& path) {
            filesystem::path fs_path(path);
            return fs_path.stem().string();
        }

        string getExtension(const string& path) {
            filesystem::path fs_path(path);
            return fs_path.extension().string();
        }

        void createDirectory(const string& path) {
            filesystem::create_directories(path);
        }

    }  // namespace System

    namespace Csv {

        Csv::Row splitIntoTokens(const string& line, char separator, function<bool(const string&)> should_skip,
                                 function<bool(const string&)> should_stop) {
            Csv::Row tokens;
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

        unordered_map<string, vector<string>> loadCsvData(ifstream& target_file, vector<string>& cols_names) {
            unordered_map<string, vector<string>> cols_data;
            string row;
            bool header_row = true;

            while (getline(target_file, row)) {
                vector<string> row_cells = Csv::splitIntoTokens(row, ',');

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

    }  // namespace Csv

    namespace Conversion {

        /**
         * @brief Converts a string to a double.
         *
         * This function takes a string representation of a number and converts it to a double.
         * It handles strings with spaces and commas, replacing commas with periods to ensure proper conversion.
         *
         * @param token The string to be converted to a double. It must be in the european format, with a comma as the decimal separator.
         * @return The double representation of the input string. Returns 0 if the input string is empty.
         */
        double stringToDouble(const string& token) {
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

        string doubleToString(double value) {
            ostringstream oss;
            oss << scientific << value;
            return oss.str();
        }

    }  // namespace Conversion

    void printColsData(const unordered_map<string, vector<string>>& cols_data, const vector<string>& cols_names) {
        for (const string& col_name : cols_names) {
            cout << "Dados da coluna " << col_name << ":" << endl;
            for (const string& dado : cols_data.at(col_name)) {
                cout << dado << " ";
            }
            cout << "\n\n";
        }
    }

}  // namespace Util
