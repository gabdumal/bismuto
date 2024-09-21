#include <iostream>
#include <pretty_console.hpp>

#include "examples/examples.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    PrettyConsole::print(
        "Bismuto Optimizer\n",
        PrettyConsole::Decoration(PrettyConsole::Color::YELLOW,
                                  PrettyConsole::Color::DEFAULT,
                                  PrettyConsole::Format::BOLD),
        cout);

    Examples::run(Examples::Example::NEIGHBOURHOOD_PLANNING);

    return 0;
}
