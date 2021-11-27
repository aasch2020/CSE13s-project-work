#include "salts.h"
#include <stdlib.h>
#include "speck.h"
struct BloomFilter {
	uint64_t primary[2];
	uint64_t secondary[2];
	uint64_t tertiary[2];
	BitVector *filter;

}

BloomFilter *bf_create(uint32_t size){
	BloomFilter *bf = (BloomFilter *) calloc(1, sizeof(BloomFilter));
	if(bf){
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

void bf_delete(BloomFilter **bf){
	if(bf){

		bv_delete((*bf)->filter);
		free(*bf);
		*bf = NULL;

	}
	return;

}

uint32_t bf_size(BloomFilter *bf){
	return bv_length(bf->vector);

}

void bf_insert(BloomFilter *bf, char *oldspeak){
	bv_set_bit(bf->vector, (hash(bf->primary, oldspeak) % size));
	bv_set_bit(bf->vector, (hash(bf->secondary, oldspeak) % size));
	bv_set_bit(bf->vector, (hash(bf->tertiary, oldspeak) % size));


}
