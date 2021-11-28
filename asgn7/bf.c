#include "salts.h"
#include <stdlib.h>
#include "speck.h"
#include "bv.h"
#include "bf.h"
#include <stdio.h>
struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) calloc(1, sizeof(BloomFilter));
    if (bf) {
        bf->primary[0] = SALT_PRIMARY_LO;
        bf->primary[1] = SALT_PRIMARY_HI;
        bf->secondary[0] = SALT_SECONDARY_LO;
        bf->secondary[1] = SALT_SECONDARY_HI;
        bf->tertiary[0] = SALT_TERTIARY_LO;
        bf->tertiary[1] = SALT_TERTIARY_LO;
        bf->filter = bv_create(size);
    }
    return bf;
}

void bf_delete(BloomFilter **bf) {
    if (bf) {

        bv_delete(&(*bf)->filter);
        free(*bf);
        *bf = NULL;
    }
    return;
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    bv_set_bit(bf->filter, (hash(bf->primary, oldspeak) % bf_size(bf)));
    bv_set_bit(bf->filter, (hash(bf->secondary, oldspeak) % bf_size(bf)));
    bv_set_bit(bf->filter, (hash(bf->tertiary, oldspeak) % bf_size(bf)));
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    if (bv_get_bit(bf->filter, hash(bf->primary, oldspeak))
        && (bv_get_bit(bf->filter, hash(bf->secondary, oldspeak)))
        && (bv_get_bit(bf->filter, hash(bf->tertiary, oldspeak)))) {
        return true;
    }

    return false;
}

uint32_t bf_count(BloomFilter *bf) {
    uint32_t total = 0;
    for (uint32_t i = 0; i < bv_length(bf->filter); i++) {
        if (bv_get_bit(bf->filter, i)) {
            total++;
        }
    }
    return total;
}

void bf_print(BloomFilter *bf) {
    printf("count is %u\n", bf_count(bf));
    bv_print(bf->filter);
}
