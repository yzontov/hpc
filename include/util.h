#ifndef UTIL_H
#define UTIL_H

#include "definitions.h"

namespace util {
    class timer {
        using utype = std::chrono::nanoseconds;

        std::chrono::steady_clock::time_point start;
        std::chrono::steady_clock::time_point end;
        const char* unit;
    public:
        timer(const char* unit = " ns");
        ~timer();
    };

    void print(const unsigned int* dd, int n, int padding = 0, char fsym = ' ', bool newline = true);

    void print(CC s, int padding = 0, char fsym = ' ', bool newline = true);

    void print(const std::vector<unsigned int*> profiles, int len);

}

#endif