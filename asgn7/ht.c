#include "bv.h"
#include "bst.h"
#include "salts.h"
#include <stdlib.h>
#include "ht.h"
#include "node.h"
struct HashTable {
    uint64_t salts[2];
    uint32_t size;
    Node **trees;
};

HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) calloc(1, sizeof(HashTable));
    if (ht) {
        ht->size = size;
        ht->trees = (Node **) calloc(size, sizeof(Node *));
        ht->salts[0] = SALT_HASHTABLE_LO;
        ht->salts[1] = SALT_HASHTABLE_HI;
    }
    return ht;
}

/*void ht_delete(HashTable **ht){
	for(uint32_t i = 0; i < size; i++){
		if((*ht)->trees[i]){
			
		}

	}

}*/

void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        bst_print(ht->trees[i]);
    }
}
