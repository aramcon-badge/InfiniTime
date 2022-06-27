#include "components/ctf/CtfController.h"

using namespace Pinetime::Controllers;

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

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

    memcpy(out_arr, solved, MIN(static_cast<unsigned long int>(getNumOfLevels()), sizeof(out_arr)));
}

void Ctf::addSolve(int index) {
    if (index >= 0 && index < getNumOfLevels() && solved[index] != 'F') {
        solved[index] = 'F';
    }
}

bool Ctf::checkSolve(int index) {
    return index >= 0 && index < getNumOfLevels() && solved[index] == 'F';
}