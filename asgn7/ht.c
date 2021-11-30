#include "bv.h"
#include "bst.h"


struct HashTable{
	uint64_t salts[2];
	uint32_t size;
	Node **trees;

}

HashTable *ht_create(uint32_t size){
	HashTable *ht = (HashTable *) calloc(1, sizeof(HashTable));
	if(ht){
		ht->size - 

	}	


}
