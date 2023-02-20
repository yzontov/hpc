#ifndef EP_H
#define EP_H

#include "definitions.h"
#include "math.h"

using namespace math;

namespace ExtendedPreference {
    class Algorithm {
    public:
        virtual bool operator () (const CC& aa, const CC& bb) = 0;
    };

    class Leximin : public Algorithm {
    public:
        bool operator () (const CC& aa, const CC& bb);
    };

    class Leximax : public Algorithm {
    public:
        bool operator () (const CC& a, const CC& b);
    };

    class Choice {
        std::vector<CC> v;
        Permutation m;
        Algorithm* e;
    public:
        Choice(unsigned char Alternatives = 3, Algorithm* alg = new Leximin());
        ~Choice();

        //cba = 321
        //1=3
        //2=2
        //3=1
        // cc = 1 => 3
        // nn = 3 => 1
        bool is_better(unsigned int permutationNumber, const CC& new_, const CC& orig);
    };
}


#endif
