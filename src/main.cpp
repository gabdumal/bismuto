#include <iostream>

#include "../external/pretty_console/pretty_console.hpp"
#include "examples/examples.hpp"

using namespace std;

int main() {
    PrettyConsole::print(
        "Bismuto Optimizer\n",
        PrettyConsole::Decoration(PrettyConsole::Color::YELLOW,
                                  PrettyConsole::Color::DEFAULT,
                                  PrettyConsole::Format::BOLD),
        cout);

    Examples::run(Examples::Example::NEIGHBOURHOOD_PLANNING);

    return 0;
}
