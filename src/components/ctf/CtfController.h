#pragma once

#include <cstring>
#include <algorithm>


namespace Pinetime::Controllers {
    class Ctf {
        protected:
            Ctf();

            static Ctf* instance;
            static const unsigned int NUM_OF_CTF_LVLS = 5;
            char solved[Ctf::NUM_OF_CTF_LVLS];

        public:
            Ctf(Ctf& other) = delete;
            void operator=(const Ctf&) = delete;
            static Ctf* getInstance();

            int getNumOfLevels();
            void getSolved(char* out_arr);
            void addSolve(int index);
            bool checkSolve(int index);
    };
}