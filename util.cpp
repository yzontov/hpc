#include "include/util.h"

namespace util {
    
        timer::timer(const char* unit) : unit(unit) {
            start = std::chrono::steady_clock::now();
        }
        timer::~timer() {
            end = std::chrono::steady_clock::now();
            auto d = end - start;
            std::cout << "Elapsed time: "
                << std::chrono::duration_cast<utype>(end - start).count()
                << unit << std::endl;
        }
    

    void print(const unsigned int* dd, int n, int padding, char fsym, bool newline) {

        std::cout << std::setfill(fsym) << std::setw(padding) << "";
        for (int i = 0; i < n; i++)
            std::cout << dd[i] << ' ';

        if (newline)
            std::cout << std::endl;;
    }

    void print(CC s, int padding, char fsym, bool newline) {
        std::cout << std::setfill(fsym) << std::setw(padding) << "";
        for (char cc : s)
            std::cout << char(cc + 0x60);
        std::cout << " ";

        if (newline)
            std::cout << std::endl;
    }

    void print(const std::vector<unsigned int*> profiles, int len) {
        for (auto p : profiles) {
            print(p, len);
        }
    }

}