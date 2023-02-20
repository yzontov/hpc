#ifndef RULES_H
#define RULES_H

#include "definitions.h"
#include "math.h"

using namespace math;

class Rule {
    unsigned char Alternatives;
    Permutation m;
    unsigned char Agents;
public:
    Rule(unsigned char Agents, unsigned char Alternatives = 3);

    CC plurality(unsigned int profile[]);

    CC hare(unsigned int profile[]);

    CC approval2(unsigned int profile[]);

    CC borda(unsigned int profile[]);

    CC nanson_multy(unsigned int profile[]);

    CC treshold(unsigned int profile[]);

    CC approval3(unsigned int profile[]);

    CC condorcet(unsigned int profile[]);

    CC black(unsigned int profile[]);

    CC inverse_plurality(unsigned int profile[]);

    CC inverse_borda(unsigned int profile[]);

    CC coombs(unsigned int profile[]);

};


#endif
