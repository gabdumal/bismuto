#include "pretty_console.hpp"

#include <sstream>

using namespace std;

void PrettyConsole::setForegroundColor(ostream &output_stream,
                                       Color foreground_color) {
    output_stream << "\033[" << foreground_color << "m";
}

void PrettyConsole::resetForegroundColor(ostream &output_stream) {
    setForegroundColor(output_stream);
}

void PrettyConsole::setBackgroundColor(ostream &output_stream,
                                       Color background_color) {
    output_stream << "\033[" << background_color + 10 << "m";
}

void PrettyConsole::resetBackgroundColor(ostream &output_stream) {
    setBackgroundColor(output_stream);
}

void PrettyConsole::setFormat(ostream &output_stream, Format format) {
    output_stream << "\033[" << format << "m";
}

void PrettyConsole::resetFormat(ostream &output_stream) {
    setFormat(output_stream);
}

PrettyConsole::Decoration PrettyConsole::getDecoration(Color foreground_color,
                                                       Color background_color,
                                                       Format format) {
    return Decoration(foreground_color, background_color, format);
}

void PrettyConsole::setDecoration(ostream &output_stream,
                                  Decoration decoration) {
    setFormat(output_stream, decoration.format);
    setBackgroundColor(output_stream, decoration.background_color);
    setForegroundColor(output_stream, decoration.foreground_color);
}

void PrettyConsole::resetDecoration(ostream &output_stream) {
    resetForegroundColor(output_stream);
    resetBackgroundColor(output_stream);
    resetFormat(output_stream);
}

void PrettyConsole::print(string message, Decoration decoration,
                          ostream &output_stream) {
    setFormat(output_stream, decoration.format);
    setBackgroundColor(output_stream, decoration.background_color);
    setForegroundColor(output_stream, decoration.foreground_color);
    output_stream << message;
    resetFormat(output_stream);
    resetBackgroundColor(output_stream);
    resetForegroundColor(output_stream);
    output_stream.flush();
}

void PrettyConsole::printParagraph(
    string title, string content, ostream &output_stream,
    PrettyConsole::Decoration title_decoration,
    PrettyConsole::Decoration content_decoration) {
    ostringstream intermediate_stream;

    PrettyConsole::print(title, title_decoration, intermediate_stream);

    PrettyConsole::setDecoration(intermediate_stream, content_decoration);

    std::istringstream content_stream(content);
    std::string line;
    while (std::getline(content_stream, line)) {
        intermediate_stream << PrettyConsole::tab << line << endl;
    }
    PrettyConsole::resetDecoration(intermediate_stream);

    intermediate_stream << endl;

    output_stream << intermediate_stream.str();
}
