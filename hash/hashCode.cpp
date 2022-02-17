//
// Created by shea on 1/20/22.
//
#include "hashCode.h"

int hashCode(bool key) {
    return (int) key;
}

int hashCode(char key) {
    return key;
}

//use linear congruence to create pseudo-random number generator
static const int HASH_SEED = 5381;               // Starting point for first cycle
static const int HASH_MULTIPLIER = 33;           // Multiplier for each cycle
static const int HASH_MASK = unsigned(-1) >> 1;  // All 1 bits except the sign

int hashCode(double key) {
    char* byte = (char *) &key;
    int hash = HASH_SEED;
    for (int i = 0; i < sizeof(double); ++i) {
        hash = HASH_MULTIPLIER * hash + *byte++;
    }
    return hash & HASH_MASK;
}

int hashCode(float key) {
    char* byte = (char*) &key;
    int hash = HASH_SEED;
    for (int i = 0; i < sizeof(float); i++) {
        hash = HASH_MULTIPLIER * hash + *byte++;
    }
    return hash & HASH_MASK;
}

int hashCode(int key) {
    return key & HASH_MASK;
}

int hashCode(long key) {
    return int(key) & HASH_MASK;
}

int hashCode(const char *str) {
    int hash = HASH_SEED;
    for (int i = 0; str && str[i] != 0; i++) {
        hash = HASH_MULTIPLIER * hash + str[i];
    }
    return int(hash & HASH_MASK);
}

int hashCode(const std::string &str) {
    int hash = HASH_SEED;
    size_t n = str.length();
    for (int i = 0; i < n; i++) {
        hash = HASH_MULTIPLIER * hash + str[i];
    }
    return int(hash & HASH_MASK);
}

int hashCode(void *key) {
    return hashCode(reinterpret_cast<long>(key));
}

//get member value
int hashSeed() {
    return HASH_SEED;
}

int hashMultiplier() {
    return HASH_MULTIPLIER;
}

int hashMask() {
    return HASH_MASK;
}

