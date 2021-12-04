#include "bv.h"
//The above header file included by Professor Long in the resources repository (Professor Long 2021)
#include <stdio.h>
#include <stdlib.h>
struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

//This function initializes a bit vector of a given length and returns it.
BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) calloc(1, sizeof(BitVector)); //Allocate memory for the struct
    if (bv) {
        bv->length = length;
        if ((length % 8)
            == 0) { //If the length is divisible by 8, we do not need to worry ahout int division truncating, so make it length/8 list.
            bv->vector = (uint8_t *) calloc(length / 8, sizeof(uint8_t));
        } else { //If the length is not divisible by 8, make an array of length/8+1 to store the bits.
            bv->vector = (uint8_t *) calloc(length / 8 + 1, sizeof(uint8_t));
        }
    }
    return bv;
}

//Delete the bit vector and set the pointer of the bit vector delete to Null.
void bv_delete(BitVector **bv) {
    free((*bv)->vector);
    free(*bv);
    *bv = NULL;
    return;
}

//Takes a bit vector, and returns the length of the bit vector.
uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

//sets the ith bit in bit vector bv, and returns a boolean indicating if the bit was successfully set.
bool bv_set_bit(BitVector *bv, uint32_t i) {
    if (i >= bv->length) { //return false if out of range.
        return false;
    }
    bv->vector[(i / 8)]
        = (bv->vector[(i / 8)]
            | (1 << (i
                     % 8))); //set the i/8th uint8_t of the bit vector to itself or 1 shifted right by i modulo 8.
    return true;
}
//clears the ith bit in the bit vector bv and returns a boolean indicating if the bit was successfully cleared.
bool bv_clr_bit(BitVector *bv, uint32_t i) {
    if (i >= bv->length) { //return false if out of range.
        return false;
    }
    bv->vector[(i / 8)]
        = (bv->vector[(i / 8)]
            & ~(1 << (i
                      % 8))); //set the i/8th bit of uint8_t equal to itself and not(1 shifted right by i modulo 8).
    return true;
}

//gets the ith bit in the bit vector bv and returns a boolean which is true if the bit is 1, and false if bit is 0
bool bv_get_bit(BitVector *bv, uint32_t i) {
    if (i >= bv->length) { //If out of range return false.
        return false;
    }
    return (
        bv->vector[(i / 8)] >> (i % 8)
        & 1); //return the uint8_t at i/8 shifter right by i mod 8, and 1. This evaluates the desired bit and 1.
}

//Takes a bit vector bv and prints it, by iterating over the vector and printing the bit with bv_get_bit.
void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv->length; i++) {
        printf("%u", bv_get_bit(bv, i));
    }
    printf("\n");
    return;
}
