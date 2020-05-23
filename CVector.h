#ifndef CVECTOR_H
#define CVECTOR_H

#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// CVector type
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define TYPE int

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Typedef
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct CVectorStruct *CVector;

//TODO: Is this really the best ? It is (almost) impossible to have a const CVector...

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Prototypes
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * CVector structure
 */
struct CVectorStruct {
    TYPE *first_elem;
    size_t capacity;
    size_t size;
};

/**
 * Retrieves the value stored at the given index in the CVector.
 * @param v The CVector to perform the operation on.
 * @param index
 * @return
 */
TYPE *getIndex(CVector v, size_t index);

/**
 * Sets the value of the given index in the CVector.
 * @param v The CVector to perform the operation on.
 * @param index
 * @param element
 */
void setIndex(CVector v, size_t index, TYPE element);

/**
 * Pushes an element at the end of the CVector. Increases capacity if required.
 * @param v The CVector to perform the operation on.
 * @param element
 */
void push_back(CVector v, TYPE element);

/**
 * Adjusts the capacity of the CVector to be able to store at least `n` elements.
 * @param v The CVector to perform the operation on.
 * @param n
 */
void reserve(CVector v, size_t n);

/**
 * Creates a new CVector with a given capacity.
 * @param capacity The initial capacity of the CVector
 * @return The CVector
 */
CVector newCVector(size_t capacity);

/**
 * Frees the memory used by the CVector.
 * @param v The CVector to perform the operation on.
 */
void deleteCVector(CVector v);

/**
 * Allocates a new memory space.
 * @param size The size of the memory space.
 * @return A pointer to the beginning of the memory space.
 * @private This function should not be called when using CVector, only here for internal uses.
 */
TYPE *allocateNewMemorySpace(size_t size);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Implementations
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TYPE *getIndex(CVector v, size_t index) {
    if (index < 0 || index >= v->capacity){
        exit(1);
    }


    return v->first_elem + index;
}

void setIndex(CVector v, size_t index, TYPE element) {
    if (index < 0 || index >= v->capacity){
        exit(1);
    }


    // If we run out of capacity, we double it
    if (v->size + 1 > v->capacity) {
        reserve(v, (v->capacity << (size_t) 1));
    }

    *(v->first_elem + index) = element;
    ++(v->size);
}


void push_back(CVector v, TYPE element) {
    // If we run out of capacity, we double it
    if (v->size + 1 > v->capacity) {
        reserve(v, (v->capacity << (size_t) 1));
    }

    *(v->first_elem + v->size) = element;
    ++(v->size);
}

void reserve(CVector v, size_t n) {
    if (n < v->capacity)
        n += v->capacity;

    TYPE *tempMemorySpace = allocateNewMemorySpace(n);
    //Copying data
    TYPE *i = v->first_elem;
    size_t j = 0;
    for (; i < v->first_elem + v->size; ++i, ++j) {
        *(tempMemorySpace + j) = *i;
    }

    //Swapping addresses
    TYPE *swapTemp = v->first_elem;
    v->first_elem = tempMemorySpace;
    v->capacity = n;
    tempMemorySpace = swapTemp;

    // Freeing the temp memory space
    free(tempMemorySpace);
}

CVector newCVector(size_t capacity) {
    TYPE *first = allocateNewMemorySpace(capacity);

    CVector v = malloc(sizeof(struct CVectorStruct));

    v->first_elem = first;
    v->capacity = capacity;
    v->size = 0;

    return v;
}

void deleteCVector(CVector v) {
    free(v->first_elem);
    free(v);
}

TYPE *allocateNewMemorySpace(size_t size) {
    TYPE *p = (TYPE *) malloc(size * sizeof(TYPE));
    return p;
}

#endif //CVECTOR_H