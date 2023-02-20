#include "include/math.h"

namespace math {
    int factorial(int n) {
        int f = 1;
        for (int i = 1; i <= n; ++i) {
            f *= i;
        }
        return f;
    }

    long double factorial2(int n) {
        long double f = 1;
        for (int i = 1; i <= n; ++i) {
            f *= i;
        }
        return f;
    }

    long double combrep(int k, int n) {
        long double f = 1;
        for (int i = k; i <= k + n - 1; ++i) {
            f *= i;
        }
        long double b = factorial2(n - 1);
        return  f / b;
    }

    std::vector<std::pair<unsigned int, unsigned int>> getIntervals(unsigned int max, unsigned int nInt) {
        std::vector<std::pair<unsigned int, unsigned int>> r;
        int c = std::floor(max / nInt);

        for (int i = 0; i <= max; i += c) {
            int a = i == 0 ? i : i += 1;
            int b = i + c > max ? max : i + c;
            if (a < max)
                r.emplace_back(a, b);
        }
        return r;
    }


        void Permutation::swap(char* a, int i, int j) {
            int s = a[i];
            a[i] = a[j];
            a[j] = s;
        }

        bool Permutation::NextSet() {

            int j = n - 2;
            while (j != -1 && a1[j] >= a1[j + 1])
                j--;
            if (j == -1) {
                return false; // ������ ������������ ���
            }

            int k = n - 1;
            while (a1[j] >= a1[k])
                k--;
            swap(a1, j, k);
            int l = j + 1, r = n - 1; // ��������� ���������� ����� ������������������
            while (l < r)
                swap(a1, l++, r--);
            std::memcpy(A + n * num++, a1, n);
            return true;
        }

    
        Permutation::Permutation(int numberOfOptions, bool showOptionsAsLetters) : n(numberOfOptions), a1(new char[numberOfOptions]), alpha(showOptionsAsLetters) {
            for (int i = 0; i < n; i++)
                a1[i] = i + 1;

            A = new char[math::factorial(n) * n];
            std::memcpy(A, a1, n);
            while (NextSet());
        }
        Permutation::~Permutation() { delete A; delete a1; }

        unsigned long Permutation::count() {
            return num;
        }

        std::vector<char> Permutation::operator[](unsigned int index) {
            std::vector<char> tmp(n);
            std::memcpy(tmp.data(), A + (index - 1) * n, n);
            //for (int i = 0; i < m; i++)
            //    tmp[i] += (alpha ? 0x60 : 0x30);
            return tmp;
        }

        void Permutation::list(bool alpha_) // ����� ������������
        {
            for (int i = 0; i < math::factorial(n); i++) {
                std::cout << i + 1 << " ";
                for (int j = 0; j < n; j++) {
                    char c = A[i * n + j] + (alpha || alpha_ ? 0x60 : 0x30);
                    std::cout << c;
                }
                std::cout << std::endl;
            }
        }


            bool Combination::NextSet(char* a, int n, int m)
            {
                int k = m;
                for (int i = k - 1; i >= 0; --i)
                    if (a[i] < n - k + i + 1)
                    {
                        ++a[i];
                        for (int j = i + 1; j < k; ++j)
                            a[j] = a[j - 1] + 1;
                        return true;
                    }
                return false;
            }

       
            Combination::Combination(int numberOfOptions, bool showOptionsAsLetters) : N(numberOfOptions), alpha(showOptionsAsLetters) {

                for (int jj = 1; jj <= N; jj++)
                {
                    char* aa = new char[jj];

                    for (int i = 0; i < jj; i++)
                        aa[i] = i + 1;

                    CC t(jj);
                    std::memcpy(t.data(), aa, jj);
                    v.push_back(t);

                    while (NextSet(aa, N, jj)) {
                        std::memcpy(t.data(), aa, jj);
                        v.push_back(t);
                    }

                    delete[] aa;
                }
            }

            std::vector<CC>& Combination::choices() {
                return v;
            }

            void Combination::list(bool alpha_) {
                for (auto a : v) {
                    for (auto b : a) {
                        char c = b + (alpha || alpha_ ? 0x60 : 0x30);
                        std::cout << c;
                    }

                    std::cout << std::endl;
                }

            }
      
    
}

