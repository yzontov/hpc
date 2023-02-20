#include "include/definitions.h"
#include "include/math.h"
#include "include/util.h"
#include "include/profiles.h"
#include "include/rules.h"
#include "include/ep.h"

using namespace math;

std::vector<unsigned int*> testset;

int calc_fun(int start, int stop, int perm, int fun, int agents, int alt = 3, int id = 0) {
    ExtendedPreference::Choice epc(alt);
    Rule rules(agents, alt);
    int cnt = 0;

    unsigned int* tmp = new unsigned int[agents];

    CC(Rule:: * ccfun)(unsigned int*) =  nullptr;

    switch (fun) {

        //scoring rules
    case 1: //plurality
        ccfun = &Rule::plurality;
        break;
    case 2: //hare
        ccfun = &Rule::hare;
        break;
    case 3: //approval2
        ccfun = &Rule::approval2;
        break;
    case 4: //borda
        ccfun = &Rule::borda;
        break;
    case 5: //nanson_multy
        ccfun = &Rule::nanson_multy;
        break;
    case 6: //treshold
        ccfun = &Rule::treshold;
        break;
    case 7: //coombs
        ccfun = &Rule::coombs;
        break;
    case 8: //black
        ccfun = &Rule::black;
        break;
    case 9: //inverse_plurality
        ccfun = &Rule::inverse_plurality;
        break;
    case 10: //inverse_borda
        ccfun = &Rule::inverse_borda;
        break;
        //
        //
    case 11: //approval3
        ccfun = &Rule::approval3;
        break;
    }

    for (int i = (start == 0 ? 0 : start - 1); i < stop; i++) {

        CC res = (rules.*ccfun)(testset[i]);
       
        bool manipulable = false;
        for (int k = 0; k < agents; k++) {
            for (unsigned int j = 1; j <= perm; j++) {
                if (testset[i][k] == j)
                    continue;
                std::memcpy(tmp, testset[i], agents * sizeof(unsigned int));
                tmp[k] = j;

                CC res_new = (rules.*ccfun)(tmp);

                if (epc.is_better(testset[i][k], res_new, res)) {
                    manipulable = true;
                    break;
                }

            }

            if (manipulable) {
                break;
            }
        }

        if (manipulable) {
            cnt++;
        }

    }
    delete[] tmp;

    return cnt;
}

bool load = true;

int main(int argc, char** argv) {

    int agents = atoi(argv[1]);

    int rule = atoi(argv[2]);

    int alt = atoi(argv[3]);;

    int cores = std::thread::hardware_concurrency();
    Permutation permutations(alt);
    long double N = std::pow(math::factorial2(alt), agents);

    if (load) {

        if (N >= 1000000)
            N = 1000000;
        testset.reserve(N);
        std::stringstream fname;
        fname << "./profiles" << alt << "/profiles_alt" << alt << "_ag" << agents << ".bin";
        std::ifstream inp(fname.str());
        if (inp.is_open())
            
            for (int i = 0; i < N; i++) {
                unsigned int* dd = new unsigned int[agents];
                inp.read((char*)dd, sizeof(unsigned int) * agents);
                testset.push_back(dd);
            }
        else
            return 1;


    }
    else {

        ProfileGenerator::IC pp1(agents, alt, N < 1000000);

        if (N >= 1000000)
        {
            N = 1000000;

            testset.reserve(N);
            for (int h = 0; h < N; h++) {
                unsigned int* dd43 = pp1.random();

                testset.push_back(dd43);
            }
        }
        else
        {

            testset = pp1.set();
        }
    }

    //util::print(testset, agents);

    auto intr = math::getIntervals(N, cores);
/*
    for (auto aa : testset) {
        for (int a = 0; a < agents; a++) {
            std::cout << aa[a] << " ";
        }
        std::cout << std::endl;
    }
 */
    
    std::vector<std::future<int>> thsq;

    //std::cout << std::thread::hardware_concurrency() << std::endl;

    for (int gg = 0; gg < cores; gg++) {
        thsq.push_back( std::async(calc_fun, intr[gg].first, intr[gg].second, permutations.count(), rule, agents, alt, gg));
    }
   
    int cnt = 0;// calc_fun(intr[cores - 1].first, intr[cores - 1].second, permutations.count(), rule, agents, alt);
    for (auto t = 0; t < thsq.size(); t++ )
       cnt+= thsq[t].get();

    std::cout << "agents = " << agents << ", manipulable = " << cnt << "/" << testset.size() << " = " << ((double)cnt) / testset.size() << std::endl;

    if(N >= 1000000 || load)
        for (auto dd : testset) {
            delete[] dd;
        }

    return 0;
}

int main_profile_gen(int argc, char** argv) {

    const int alt = 3;

    for (int agents = 1; agents <= 100; agents++) {

        std::vector<unsigned int*> testset1;
        long double N = std::pow(math::factorial2(alt), agents);

        ProfileGenerator::IC pp1(agents, alt, N < 1000000);

        if (N >= 1000000)
        {
            N = 1000000;

            testset1.reserve(N);
            for (int h = 0; h < N; h++) {
                unsigned int* dd43 = pp1.random();

                testset1.push_back(dd43);
            }
        }
        else
        {
            testset1 = pp1.set();
        }

        std::stringstream s;
        s << "profiles_alt" << alt << "_ag" << agents << ".bin";
        std::ofstream ff(s.str());
        for (unsigned int* rec : testset1) {
            ff.write((const char*)rec, sizeof(unsigned int) * agents);
        }
        ff.close();

        if (N >= 1000000)
            for (auto dd : testset1) {
                delete[] dd;
            }

    }


    return 0;

}