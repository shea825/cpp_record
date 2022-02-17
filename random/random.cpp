//
// Created by shea on 1/21/22.
//

#include <queue>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "random.h"

#define UNUSED(x) (void)(x)
/* internal buffer of fixed random numbers to return; used by autograders */
namespace autograder {
    std::queue<bool> fixedBools;
    std::queue<int> fixedInts;
    std::queue<double> fixedReals;
    void randomFeedBool(bool value) {
        UNUSED(value);
        fixedBools.push(value);
    }
    void randomFeedInteger(int value) {
        UNUSED(value);
        fixedInts.push(value);
    }
    void randomFeedReal(double value) {
        UNUSED(value);
        fixedReals.push(value);
    }
}

/*
 * Implementation notes: initRandomSeed
 * ------------------------------------
 * The initRandomSeed function declares a static variable that keeps track
 * of whether the seed has been initialized.  The first time initRandomSeed
 * is called, initialized is false, so the seed is set to the current time.
 */
static void initRandomSeed() {
    static bool initialized = false;
    if (!initialized) {
        srand(int(time(nullptr)));
        rand();   // BUGFIX: throwaway call to get randomness going
        initialized = true;
    }
}

bool randomBool() {
    return randomChance(0.5);
}

/*
 * Implementation notes: randomChance
 * ----------------------------------
 * The code for randomChance calls randomReal(0, 1) and then checks
 * whether the result is less than the requested probability.
 */
bool randomChance(double p) {
    if (!autograder::fixedBools.empty()) {
        bool top = autograder::fixedBools.front();
        autograder::fixedBools.pop();
        return top;
    }
    initRandomSeed();
    return randomReal(0, 1) < p;
}

int randomColor() {
    if (!autograder::fixedInts.empty()) {
        int top = autograder::fixedInts.front();
        autograder::fixedInts.pop();
        return top & 0x00ffffff;
    }
    initRandomSeed();
    return rand() & 0x00ffffff;
}

std::string randomColorString() {
    int rgb = randomColor();
    if (rgb == -1) return "";
    std::ostringstream os;
    os << std::hex << std::setfill('0') << std::uppercase << "#";
    os << std::setw(2) << (rgb >> 16 & 0xFF);
    os << std::setw(2) << (rgb >> 8 & 0xFF);
    os << std::setw(2) << (rgb & 0xFF);
    return os.str();
}

int randomInteger(int low, int high) {
    if (!autograder::fixedInts.empty()) {
        int top = autograder::fixedInts.front();
        autograder::fixedInts.pop();
        return top;
    }
    initRandomSeed();
    double d = rand() / (double(RAND_MAX) + 1);
    double s = d * (double(high) - low + 1);
    return int(floor(low + s));
}

double randomReal(double low, double high) {
    if (!autograder::fixedReals.empty()) {
        double top = autograder::fixedReals.front();
        autograder::fixedReals.pop();
        return top;
    }
    initRandomSeed();
    double d = rand() / (double(RAND_MAX) + 1);
    double s = d * (high - low);
    return low + s;
}

void setRandomSeed(int seed) {
    initRandomSeed();
    srand(seed);
}

int main() {

}