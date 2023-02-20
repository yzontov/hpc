#include "include/profiles.h"

namespace ProfileGenerator {
    
        bool IAC::NextSet(unsigned int* a, int n, int m)
        {
            int j = m - 1;
            while (a[j] == n && j >= 0) j--;
            if (j < 0) return false;
            if (a[j] >= n)
                j--;
            a[j]++;
            if (j == m - 1) return true;
            for (int k = j + 1; k < m; k++)
                a[k] = a[j];
            return true;
        }

        IAC::IAC(int Agents, int Alternatives) : mmax(Agents), Alternatives(Alternatives), k(math::factorial(Alternatives)), gen(rd()) {
            ddata = new unsigned int[mmax];
        }
        IAC::~IAC() {
            delete ddata;
        }

        void IAC::list() {
            for (int i = 0; i < mmax; i++)
                ddata[i] = 1;

            std::cout << ++cnt << "| ";
            for (int j = 0; j < mmax; j++)
                std::cout << ddata[j] << " ";
            std::cout << std::endl;

            while (NextSet(ddata, k, mmax)) {
                std::cout << ++cnt << "| ";
                for (int j = 0; j < mmax; j++)
                    std::cout << ddata[j] << " ";
                std::cout << std::endl;
            }

            std::cout << "total: " << cnt << std::endl;
        }

        unsigned int* IAC::random() {

            unsigned int* seq = new unsigned int[mmax];
            for (int j = 0; j < mmax; j++) {
                std::uniform_int_distribution<unsigned int> distrib(1, k + j);
                unsigned int pp = distrib(gen);
                if (pp < k)
                    seq[j] = pp;
                else
                    seq[j] = seq[pp - k];
            }

            return seq;
        }
    

        void IC::loop(int loop_level, bool printout, bool precalc) {
            if (loop_level > mmax - 1)
            {
                ++cnt;
                if (printout) {
                    std::cout << cnt << "| ";
                    for (int j = 0; j < mmax; j++)
                        std::cout << ddata[j] << " ";
                    std::cout << std::endl;
                }

                if (precalc) {
                    auto v = new unsigned int[mmax];
                    std::memcpy(v, ddata, mmax * sizeof(unsigned int));
                    vv.push_back(v);
                }


                return;
            }

            for (int i = 1; i <= k; i++)
            {
                ddata[loop_level] = i;
                loop(loop_level + 1, printout, precalc);
            }
        }


        IC::IC(int Agents, int Alternatives, bool precalc) : mmax(Agents), Alternatives(Alternatives), k(math::factorial(Alternatives)), gen(rd()), distrib(1, k), precalc_(precalc) {
            ddata = new unsigned int[mmax];

            if (precalc)
                loop(0, false, true);
        }
        IC::~IC() {

            if (precalc_)
                for (auto v : vv)
                    delete[] v;

            delete[] ddata;
        }

        long double IC::seq2num(unsigned int p[]) {
            long double d = 0;
            for (int i = 1; i < mmax; i++)
                d += (p[i - 1] - 1) * pow(k, mmax - i);

            d += p[mmax - 1];

            return d;
        }

        unsigned int* IC::num2seq(long double num) {
            long double nn = num;
            unsigned int* seq = new unsigned int[mmax];
            for (int i = mmax - 2; i > 0; i--) {
                double hh = pow(k, i);
                unsigned int jj = nn / hh + 1;
                seq[mmax - 1 - i] = jj;
                nn -= (jj - 1) * hh;
            }
            seq[mmax - 1] = (unsigned int)nn;

            return seq;
        }

        unsigned int* IC::random() {

            unsigned int* seq = new unsigned int[mmax];
            for (int j = 0; j < mmax; j++) {
                seq[j] = distrib(gen);
                if (seq[j] > k)
                    break;
            }

            return seq;
        }

        std::vector<unsigned int*>& IC::set() {
            return vv;
        }

        void IC::list() {
            loop();
            std::cout << "total: " << cnt << std::endl;
        }

}
