#ifndef PROFILES_H
#define PROFILES_H

#include "definitions.h"
#include "math.h"

namespace ProfileGenerator {
    class IAC {
        int Alternatives;
        int mmax, k;
        unsigned int* ddata;
        long double cnt = 0;

        std::random_device rd;
        std::mt19937 gen;


        bool NextSet(unsigned int* a, int n, int m);

    public:
        IAC(int Agents, int Alternatives = 3);
        ~IAC();

        void list();

        unsigned int* random();
    };
    //IC
    class IC {
        int Alternatives;
        int mmax, k;
        unsigned int* ddata;
        long double cnt = 0;

        std::vector<unsigned int*> vv;

        std::random_device rd;
        std::mt19937 gen;
        std::uniform_int_distribution<unsigned int> distrib;

        /*
        * mmax = 3
           cnt <= 36 -> p(0) = 1    m^(n-1)    z-1
           cnt <= 72 -> p(0) = 2
           cnt <= 108 -> p(0) = 3
           cnt <= 144 -> p(0) = 4
           cnt <= 180 -> p(0) = 5
           cnt <= 216 -> p(0) = 6

           cnt <= 6, [37,42], [73,78], ... -> p(1) = 1    m^(n-2)    z-1
           cnt <= 12, [43,48], [79,84], ... -> p(1) = 2
           cnt <= 18, [49,54], [85,90], ... -> p(1) = 3
           cnt <= 24, [55,60], [91,96], ... -> p(1) = 4
           cnt <= 30, [61,66], [97,102], ... -> p(1) = 5
           cnt <= 36, [67,72], [103,108], ... -> p(1) = 6

           a = 3;//alternatives
           n = 3;//voters
           m = perm(a)

           int d = 0;
           int p[n] = {1, 1, 1};

           for(int i = 1; i < n; i++)
              d += p[i-1]*pow(m, n-i);
           d += p[n-1];

           Грэхем, Кнут, Паташник. Конкретная математика.
           Решение рекуррентных соотношений.

           //(p[0]-1) * m^(n-1) + (p[1]-1) * m^(n-2) + ... + (p[n-2]-1)*m^(n-(n-1)) + p[n-1] * m^0

           Профиль в IC, сгенерированный определенным образом (в лексикографическом порядке? как n вложенных циклов или эквивалентный рекурсивный алгоритм)
           есть представление своего натурального порядкого номера в смешанной системе счисления.
           Между ними существует однозначное соответствие. Вычисляется за линейное время (от количества агентов).

           https://ru.wikipedia.org/wiki/%D0%A1%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D0%B0_%D1%81%D1%87%D0%B8%D1%81%D0%BB%D0%B5%D0%BD%D0%B8%D1%8F
        */

        /*
        *
        Соображение:
        При манипулировании новый измененный профиль входит в множество всех профилей

        Для сравнения не требуется знать все расширенное предпочтение целиком, только правило сравнения

        */

        //http://corysimon.github.io/articles/recursion/
        void loop(int loop_level = 0, bool printout = true, bool precalc = false);

        bool precalc_ = false;

    public:
        IC(int Agents, int Alternatives = 3, bool precalc = false);
        ~IC();

        long double seq2num(unsigned int p[]);

        unsigned int* num2seq(long double num);

        unsigned int* random();

        std::vector<unsigned int*>& set();

        void list();
    };
}

#endif