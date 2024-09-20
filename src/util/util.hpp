#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <pretty_console.hpp>

using namespace std;

namespace Util {
    string getFormattedBool(bool value);

    string getTextBetween(string text, optional<string> start,
                          optional<string> end);
    string getLineContent(int line, string content);
}  // namespace Util

#endif  // UTIL_HPP_
