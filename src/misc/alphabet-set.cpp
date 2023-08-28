#include "alphabet-set.h"

int setComplement(int set) {
    return ~set;
}

int setUnion(int setA, int setB) {
    return setA | setB;
}

int setIntersection(int setA, int setB) {
    return setA & setB;
}

int setDifference(int setA, int setB) {
    return setA & ~setB;
}

void assertLetterInRange(char letter) {
    if (letter < 'a' || letter > 'z')
        throw std::invalid_argument("Parameter letter is out of range. Letter must be between a-z lowercase.");
}

int setAdd(int set, char letter) {
    assertLetterInRange(letter);
    int mask = 0x00000001 << (letter - 'a');
    return set | mask;
}

int setRemove(int set, char letter) {
    assertLetterInRange(letter);
    int mask = ~(0x00000001 << (letter - 'a'));
    return set & mask;
}

bool setContains(int set, char letter) {
    assertLetterInRange(letter);
    int mask = 0x00000001 << (letter - 'a');
    return (mask & set) != 0;
}

std::string setContents(int set) {
    std::string result = "";
    for (int i = 0; i < 26; i++) {
        if (setContains(set, 'a' + i))
            result += (char)('a' + i);
    }
    return result;
}
