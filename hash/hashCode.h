//
// Created by shea on 1/20/22.
//

#ifndef MAINPROJ_HASHCODE_H
#define MAINPROJ_HASHCODE_H

#include <string>

/*
 * Function: hashCode
 * Usage: int hash = hashCode(key);
 * --------------------------------
 * Returns a hash code for the specified key, which is always a
 * non-negative integer.  This function is overloaded to support
 * all of the primitive types and the C++ <code>string</code> type.
 */
int hashCode(bool key);
int hashCode(char key);
int hashCode(double key);
int hashCode(float key);
int hashCode(int key);
int hashCode(long key);
int hashCode(const char* str);
int hashCode(const std::string& str);
int hashCode(void* key);

/*
 * Constants that are used to help implement these functions
 * (see hashcode.h for example usage)
 */
int hashSeed();         // Starting point for first cycle
int hashMultiplier();   // Multiplier for each cycle
int hashMask();         // All 1 bits except the sign

/*
 * Template hash function for arbitrary types.
 * Hashes based on memory address.
 */
//template <typename T>
//int hashCode(const T& t) {
//    return hashCode(reinterpret_cast<long>(&t));
//}

#endif //MAINPROJ_HASHCODE_H
