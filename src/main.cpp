#include <iostream>

#include "examples/examples.hpp"
#include "pretty_console.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    PrettyConsole::print(
        "DCC163 - Operational Research",
        PrettyConsole::Decoration(PrettyConsole::Color::YELLOW,
                                  PrettyConsole::Color::DEFAULT,
                                  PrettyConsole::Format::BOLD),
        cout);

    Examples::run(Examples::Example::BOOK_C3_S1_SC5);

    return 0;
}
