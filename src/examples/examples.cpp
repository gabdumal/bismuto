#include "examples.hpp"

void Examples::run(Example example) {
    switch (example) {
        case BOOK_C1_S3_SC1:
            bookC1S3Sc1();
            break;
        case BOOK_C3_S1_SC5:
            bookC3S1Sc5();
            break;
    }
}