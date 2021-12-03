#include "bv.h"
#include <stdio.h>
#include <stdlib.h>
struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) calloc(1, sizeof(BitVector));
    if (bv) {
        bv->length = length;
        if ((length % 8) == 0) {
            bv->vector = (uint8_t *) calloc(length / 8, sizeof(uint8_t));
        } else {
            bv->vector = (uint8_t *) calloc(length / 8 + 1, sizeof(uint8_t));
        }
    }
    return bv;
}

void bv_delete(BitVector **bv) {
    free((*bv)->vector);
    free(*bv);
    *bv = NULL;
    return;
}

uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

bool bv_set_bit(BitVector *bv, uint32_t i) {
    if (i >= bv->length) {
        return false;
    }
    bv->vector[(i / 8)] = (bv->vector[(i / 8)] | (1 << (i % 8)));
    return true;
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
    if (i >= bv->length) {
        return false;
    }
    bv->vector[(i / 8)] = (bv->vector[(i / 8)] & ~(1 << (i % 8)));
    return true;
}

bool bv_get_bit(BitVector *bv, uint32_t i) {
    if (i >= bv->length) {
        return false;
    }
    return (bv->vector[(i / 8)] >> (i % 8) & 1);
}

void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv->length; i++) {
        printf("%u", bv_get_bit(bv, i));
    }
    printf("\n");
}
