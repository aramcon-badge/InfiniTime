#include "components/ctf/CtfController.h"

using namespace Pinetime::Controllers;

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

Ctf::Ctf() : solved {std::string(NUM_OF_CTF_LVLS, '.')} {
}

Ctf* Ctf::getInstance() {
    static Ctf* instance = new Ctf();
    return instance;
}

int Ctf::getNumOfLevels() {
    return NUM_OF_CTF_LVLS;
}

void Ctf::getSolved(std::string& out_str) {

    out_str = solved;
}

void Ctf::addSolve(int index) {
    if (index >= 0 && index < getNumOfLevels() && solved[index] != 'F') {
        solved[index] = 'F';
    }
}

bool Ctf::checkSolve(int index) {
    return index >= 0 && index < getNumOfLevels() && solved[index] == 'F';
}