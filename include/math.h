#ifndef MATH_H
#define MATH_H

#include "definitions.h"

namespace math {
    
    int factorial(int n);

    long double factorial2(int n);

    long double combrep(int k, int n);

    std::vector<std::pair<unsigned int, unsigned int>> getIntervals(unsigned int max, unsigned int nInt);

    //https://prog-cpp.ru/permutation/
//Перестановки
    class Permutation {
        int n;
        char* a1;
        int num = 1;
        char* A;
        bool alpha;

        void swap(char* a, int i, int j);

        bool NextSet();

    public:
        Permutation(int numberOfOptions = 3, bool showOptionsAsLetters = false);

        ~Permutation();

        unsigned long count();

        std::vector<char> operator[](unsigned int index);

        void list(bool alpha_ = false);
    };

    //https://prog-cpp.ru/combinations/
//Сочетания без повторений - результаты голосования
class Combination {
    bool alpha;
    std::vector<CC> v;
    int N;


    bool NextSet(char* a, int n, int m);

public:
    Combination(int numberOfOptions, bool showOptionsAsLetters = false);

    std::vector<CC>& choices();

    void list(bool alpha_ = false);
};

  
}

#endif