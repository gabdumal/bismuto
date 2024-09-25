#include <iostream>
#include <string>

#include "../external/pretty_console/pretty_console.hpp"
#include "examples/examples.hpp"

int main() {
    PrettyConsole::print(
        "Bismuto Optimizer\n",
        PrettyConsole::Decoration(PrettyConsole::Color::YELLOW,
                                  PrettyConsole::Color::DEFAULT,
                                  PrettyConsole::Format::BOLD),
        cout);
    Examples::run(Examples::Example::LIVESTOCK_DIET);

    return 0;
}
