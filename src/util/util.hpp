#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <optional>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

namespace Util {
    string getFormattedBool(bool value);

    string getTextBetween(string text, optional<string> start,
                          optional<string> end);
    string getLineContent(int line, string content);

    string getExecutableDirectory();

    vector<string> rowTokenizer(const string& row);

    void printColsData(const unordered_map<string, vector<string>>& cols_data, const vector<string>& cols_names);
    
    unordered_map<string, vector<string>> loadCSVData(ifstream& target_file, vector<string>& cols_names);
}  // namespace Util

#endif  // __UTIL_HPP__
