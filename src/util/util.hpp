#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Util {
    public:
        using Row = vector<string>;

        static string getExecutableDirectory();

        static string getStem(const string& path);

        static string getExtension(const string& path);

        static void createDirectory(const string& path);

        static void printColsData(const unordered_map<string, vector<string>>& cols_data,
                                  const vector<string>& cols_names);

        static unordered_map<string, vector<string>> loadCsvData(ifstream& target_file, vector<string>& cols_names);

        static Row splitIntoTokens(
            const string& line, char separator = '\t',
            function<bool(const string&)> should_skip = [](const string&) { return false; },
            function<bool(const string&)> should_stop = [](const string&) { return false; });

        static double stringToDouble(const string& token);

        static string doubleToString(double value);
};

#endif  // __UTIL_HPP__
