#include "salts.h"
#include "speck.h" //This code inspired by/adapted from the code shown in the BST lecture 18 (Professor Long 2021)
#include "bv.h"
#include "bf.h"
//The above header files provided in the resources repository by Professor Long (Professor Long 2021)
#include <stdio.h>
#include <stdlib.h>

//Declares the Bloom filter struct, which has three salts and a bit vector.
struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

//Takes a size and creates a bloom filter of that size, returns a pointer to the bloom filter.
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) calloc(1, sizeof(BloomFilter));
    if (bf) {
        //Set the salts
        bf->primary[0] = SALT_PRIMARY_LO;
        bf->primary[1] = SALT_PRIMARY_HI;
        bf->secondary[0] = SALT_SECONDARY_LO;
        bf->secondary[1] = SALT_SECONDARY_HI;
        bf->tertiary[0] = SALT_TERTIARY_LO;
        bf->tertiary[1] = SALT_TERTIARY_LO;
        //Create the filter
        bf->filter = bv_create(size);
    }
    //return the bloom filter
    return bf;
}

//Takes a pointer to a bloomfilter and delete the bloom filter, then set the pointer to null.
void bf_delete(BloomFilter **bf) {
    if (bf) {

        bv_delete(&(*bf)->filter);
        free(*bf);
        *bf = NULL;
    }
    return;
}

//Takes a bloom filter and returns the length of the bit vector in it.
uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

//Takes a word and a Bloom filter, hashes the word with the three given salts, and inserts the hashed number modulo the bf size into the vector.
void bf_insert(BloomFilter *bf, char *oldspeak) {
    bv_set_bit(bf->filter, (hash(bf->primary, oldspeak) % bf_size(bf)));
    bv_set_bit(bf->filter, (hash(bf->secondary, oldspeak) % bf_size(bf)));
    bv_set_bit(bf->filter, (hash(bf->tertiary, oldspeak) % bf_size(bf)));
    return;
}

//Takes a word and a Bloom filter, and returns if the word is in the bloom filter.
//Hash the word with all three algorithms, and get the bit at index hashed number module bf size.
//If all three bits are 1, return true, else return false.
bool bf_probe(BloomFilter *bf, char *oldspeak) {
    if (bv_get_bit(bf->filter, (hash(bf->primary, oldspeak) % bf_size(bf)))
        && (bv_get_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf)))
        && (bv_get_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf)))) {
        return true;
    }

    return false;
}

//Returns the number of bits that are set i the given bloom filter.
//iterate through the bit vector and get the bits, adding one to the count for every bit set.
//Return the counter.
uint32_t bf_count(BloomFilter *bf) {
    uint32_t total = 0;
    for (uint32_t i = 0; i < bv_length(bf->filter); i++) {
        if (bv_get_bit(bf->filter, i)) {
            total++;
        }
    }
    return total;
}

//Print the Bloom filter by printing the count and the bit vector in the bloom filter
void bf_print(BloomFilter *bf) {
    printf("count is %u\n", bf_count(bf));
    bv_print(bf->filter);
    return;
}
