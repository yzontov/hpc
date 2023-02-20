#include "include/ep.h"

namespace ExtendedPreference {
    
        bool Leximin::operator () (const CC& aa, const CC& bb) {

            if (aa.size() == bb.size())
            {
                for (int i = aa.size() - 1; i >= 0; i--)
                    if (aa[i] < bb[i])
                        return true;
                    else
                        if (aa[i] > bb[i])
                            return false;

                return false;
            }
            else {

                CC a(const_cast<CC&>(aa));
                CC b(const_cast<CC&>(bb));
                std::sort(a.begin(), a.end(), std::greater<char>());
                std::sort(b.begin(), b.end(), std::greater<char>());

                for (size_t i = 0; i < std::min(a.size(), b.size()); i++)
                    if (a[i] < b[i])
                        return true;
                    else
                        if (a[i] > b[i])
                            return false;

                return a.size() > b.size();
            }
        }
     
        bool Leximax::operator () (const CC& a, const CC& b) {

            if (a.size() == b.size())
            {
                for (size_t i = 0; i < a.size(); i++)
                    if (a[i] < b[i])
                        return true;
                    else
                        if (a[i] > b[i])
                            return false;

                return false;
            }
            else {

                for (size_t i = 0; i < std::min(a.size(), b.size()); i++)
                    if (a[i] < b[i])
                        return true;
                    else
                        if (a[i] > b[i])
                            return false;

                return a.size() < b.size();
            }
        }
   

        Choice::Choice(unsigned char Alternatives, Algorithm* alg) : m(Permutation(Alternatives)), e(alg) {
            Combination ss(Alternatives);
            v = std::move(ss.choices());
            std::sort(v.begin(), v.end(), std::ref(*e));
        }
        Choice::~Choice() {
            delete e;
        }

        bool Choice::is_better(unsigned int permutationNumber, const CC& new_, const CC& orig) {
            unsigned int mm = permutationNumber;
            //std::unordered_map<char,char> um;
            std::unordered_map<char, char> um2;

            CC new_1 = new_;
            CC orig1 = orig;

            char hh = '\1';
            for (char i : m[mm]) {
                //um[hh] = i;
                um2[i] = hh;
                hh++;
            }

            for (size_t i = 0; i < orig1.size(); i++)
                orig1[i] = um2[orig1[i]];
            for (size_t i = 0; i < new_1.size(); i++)
                new_1[i] = um2[new_1[i]];

            return e->operator()(new_1, orig1);

        }

}