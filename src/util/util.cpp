#include "util.hpp"

#include <filesystem>
#include <sstream>
#include <string>

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
    return filesystem::canonical("/proc/self/exe").parent_path().string();
}
