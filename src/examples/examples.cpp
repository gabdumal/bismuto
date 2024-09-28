#include "examples.hpp"

#include <iostream>

void Examples::run(Example example) {
    switch (example) {
        case BOOK_C1_S3_SC1:
            bookC1S3Sc1();
            break;
        case BOOK_C3_S1_SC5:
            bookC3S1Sc5();
            break;
        case READ_CSV:
            readCsv();
            break;
        case LIVESTOCK_DIET:
            livestockDiet();
            break;
    }
}

void Examples::run(string name) {
    unsigned int i = 0;
    for (const auto &example_name : examples_names) {
        if (name == example_name) {
            auto example = static_cast<Example>(i);
            run(example);
            return;
        }
        i++;
    }
    cout << "Example not found!" << endl;
}
