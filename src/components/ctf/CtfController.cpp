#include "components/ctf/CtfController.h"

using namespace Pinetime::Controllers;

Ctf::Ctf() : solved {0} {
    memset(solved, '.', NUM_OF_CTF_LVLS);
}

Ctf* Ctf::getInstance() {
    static Ctf* instance = new Ctf();
    return instance;
}

int Ctf::getNumOfLevels() {
    return NUM_OF_CTF_LVLS;
}

void Ctf::getSolved(char* out_arr) {

    memcpy(out_arr, solved, std::min(static_cast<unsigned long int>(getNumOfLevels()), sizeof(out_arr)));
}

void Ctf::addSolve(int index) {
    if (index >= 0 && index < getNumOfLevels()) {
        solved[index] = 'F';
    }
}