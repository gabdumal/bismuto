#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <functional>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Util {
    public:
        using Row = vector<string>;

        static string getFormattedBool(bool value);

        static string getTextBetween(string text, optional<string> start, optional<string> end);
        static string getLineContent(int line, string content);

        static string getExecutableDirectory();

        static void printColsData(const unordered_map<string, vector<string>>& cols_data,
                                  const vector<string>& cols_names);

        static unordered_map<string, vector<string>> loadCsvData(ifstream& target_file, vector<string>& cols_names);

        static Row splitIntoTokens(
            const string& line, char separator = '\t',
            function<bool(const string&)> should_skip = [](const string&) { return false; },
            function<bool(const string&)> should_stop = [](const string&) { return false; });
};

#endif  // __UTIL_HPP__
