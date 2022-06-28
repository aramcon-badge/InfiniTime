#pragma once

#include <cstring>
#include <string>
#include <algorithm>


namespace Pinetime::Controllers {
    class Ctf {
        protected:
            Ctf();

            static Ctf* instance;
            static const unsigned int NUM_OF_CTF_LVLS = 5;
            std::string solved;

        public:
            Ctf(Ctf& other) = delete;
            void operator=(const Ctf&) = delete;
            static Ctf* getInstance();

            int getNumOfLevels();
            void getSolved(std::string& out_str);
            void addSolve(int index);
            bool checkSolve(int index);
    };
}