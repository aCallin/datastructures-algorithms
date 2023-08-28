#pragma once

#include <string>
#include <stdexcept>
#include <iostream>

/* 
 * Problem: Represent a set that can only contain the lowercase alphabet letters (a..z). Implement set operations such 
 * as complement, union, intersection, and difference.
 *
 * Solution: Pack the 26 letters into a 32-bit data type, where each bit represents the presence or absence of its 
 * corresponding letter. This solution is very efficient in both space and time, because the entire set is stored in 
 * 4 bytes and the set operations are performed in constant time.
 * 
 * Example: A set containing the letters [a, b, c, d, y, z] would be represented as follows:
 *     0000 0011 0000 0000 0000 0000 0000 1111 --> 0x0300000F
 * Letters a..z are stored in bits 0..25, so bits 26..31 are not used for this problem.
*/

// Set operations.
int setComplement(int set);
int setUnion(int setA, int setB);
int setIntersection(int setA, int setB);
int setDifference(int setA, int setB);

// Other operations.
int setAdd(int set, char letter);
int setRemove(int set, char letter);
bool setContains(int set, char letter);
std::string setContents(int set);
