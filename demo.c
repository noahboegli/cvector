#include <stdio.h>
#include "CVector.h"

// The reserve method is adaptive:
// Current size = 10, reserve(20) => new capacity = 20;
// Current size = 50, reserve(20) => new capacity = 70;
// Thus the "at least" n elements

int main() {

    // creation
    CVector v = newCVector(10);

    // reserve
    reserve(v, 30);

    // setindex
    for (int i = 0; i < 30; ++i) {
        setIndex(v, i, i);
    }

    // push_back
    for (int i = 30; i < 60; ++i) {
        push_back(v, i);
    }

    // looping
    for (int i = 0; i < 60; ++i) {
        printf("%d ", *getIndex(v, i));
    }

    // These will cause the program to exit with a code 1
    // setIndex(v, 158, 30);  //Since the index 158 is out of bounds
    // getIndex(v, 284);      //Since the index 284 is out of bounds


    // deletion
    deleteCVector(v);

    return 0;
}

