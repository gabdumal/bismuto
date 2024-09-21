#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <optional>
#include <string>
using namespace std;

namespace Util {
    string getFormattedBool(bool value);

    string getTextBetween(string text, optional<string> start,
                          optional<string> end);
    string getLineContent(int line, string content);

    string getExecutableDirectory();
}  // namespace Util

#endif  // __UTIL_HPP__
