#ifndef __EXAMPLE_HPP__
#define __EXAMPLE_HPP__

#include <string>
using namespace std;

class Examples {
    public:
        enum Example {
            BOOK_C1_S3_SC1,
            BOOK_C3_S1_SC5,
            READ_CSV,
            LIVESTOCK_DIET,
        };

        static constexpr const char* examples_names[] = {
            "book_c1_s3_sc1",
            "book_c3_s1_sc5",
            "read_csv",
            "livestock_diet",
        };

    private:
        static void bookC1S3Sc1();
        static void bookC3S1Sc5();
        static void livestockDiet();
        static void readCsv();

    public:
        static void run(Example example);
        static void run(string name);
};

#endif  // __EXAMPLE_HPP__
