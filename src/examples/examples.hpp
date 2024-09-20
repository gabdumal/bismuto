#ifndef __EXAMPLE_HPP__
#define __EXAMPLE_HPP__

#include <glpk.h>

class Examples {
   public:
    enum Example { BOOK_C1_S3_SC1, BOOK_C3_S1_SC5 };

   private:
    static void bookC1S3Sc1();
    static void bookC3S1Sc5();

   public:
    static void run(Example example);
};

#endif  // __EXAMPLE_HPP__
