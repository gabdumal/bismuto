#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

namespace Util {

    namespace Project {

        string getVersion();

    }  // namespace Project

    namespace System {

        string getResourcesDirectory();
        string getTempDirectory();

        string getStem(const string& path);
        string getExtension(const string& path);

        void createDirectory(const string& path);

    }  // namespace System

    namespace Csv {

        using Row = vector<string>;

        unordered_map<string, vector<string>> loadCsvData(ifstream& target_file, vector<string>& cols_names);

        Row splitIntoTokens(
            const string& line, char separator = '\t',
            function<bool(const string&)> should_skip = [](const string&) { return false; },
            function<bool(const string&)> should_stop = [](const string&) { return false; });

    }  // namespace Csv

    namespace Conversion {

        double stringToDouble(const string& token);

        string doubleToString(double value);

    }  // namespace Conversion

    void printColsData(const unordered_map<string, vector<string>>& cols_data,
                       const vector<string>& cols_names);

};  // namespace Util

#endif  // __UTIL_HPP__
