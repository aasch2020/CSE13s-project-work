#include "bv.h"
#include "bst.h"
#include "salts.h"
#include "ht.h"
#include "node.h"
#include "speck.h" //The implementation of this hashing function, speck.c is provided in the resources repository by Professor Long (Professor Long 2021)
//The above header files provided by Professor Long in the resources repository (Professor Long 2021).
#include <stdlib.h>
uint64_t lookups = 0;

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **trees;
};

//Creates a hash table of given size and return the pointer to it.
HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) calloc(1, sizeof(HashTable));
    if (ht) {
        ht->size = size;
        ht->trees = (Node **) calloc(size, sizeof(Node *));
        ht->salt[0] = SALT_HASHTABLE_LO; //Set the salts to the given salt.
        ht->salt[1] = SALT_HASHTABLE_HI;
    }
    return ht;
}

//Delete a given hash tabkle, by first deleting every tree in it using bst_delete, then deleting the hash table itself.
//Rset the given pointer to null.
void ht_delete(HashTable **ht) {
    if (ht) {
        for (uint32_t i = 0; i < (*ht)->size; i++) {
            if ((*ht)->trees[i]) {
                bst_delete(&((*ht)->trees[i]));
            }
        }
        free((*ht)->trees);
        free(*ht);
        *ht = NULL;
    }
    return;
}

//Takes a hash table and returns the size of the given hash table.
uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

//Checks if a given oldspeak string is in the hash table ht.
//Returns the node if it is found.
//This is done by searching the binary search tree at index of the string hashed mod the size for the given oldspeak.
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    lookups++;
    if (ht->trees[(hash(ht->salt, oldspeak) % ht->size)]) {
        return bst_find((ht->trees[(hash(ht->salt, oldspeak) % ht->size)]), oldspeak);
    }
    return NULL;
}

//Inserts a given oldspeak and newspeak into a hash table
//first hash the given oldspeak, and then insert the oldspeak and newspeak into the tree at index hashed value mod size of ht.
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    lookups++;
    if (ht->trees[(
            hash(ht->salt, oldspeak)
            % ht->size)]) { //This is to ensure we do not try to insert into a null tree, as that does not work with bst_insert.
        bst_insert((ht->trees[(hash(ht->salt, oldspeak) % ht->size)]), oldspeak, newspeak);

    } else {
        ht->trees[(hash(ht->salt, oldspeak) % ht->size)] = node_create(oldspeak, newspeak);
    }
    return;
}

//Counts the number of non NULL trees in hash table ht, and returns it.
//This iterates over the array and adds one to the counter for each non null tree.
uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->trees[i]) {
            count++;
        }
    }
    return count;
}
//Calculatees the average size of the non null bsts in the hash table ht, and returns it as a double.
//This iterates over the array amd adds the size of each tree to the double total.
//Then returns total/count.
double ht_avg_bst_size(HashTable *ht) {
    double total = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        total += bst_size(ht->trees[i]);
    }
    return total / ht_count(ht);
}
//Calculatees the average height of the non null bsts in the hash table ht, and returns it as a double.
//This iterates over the array amd adds the height of each tree to the double total.
//Then returns total/count.
double ht_avg_bst_height(HashTable *ht) {
    double total = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        total += bst_height(ht->trees[i]);
    }
    return total / ht_count(ht);
}
//This prints each bst in the Hash table ht, by iterating over it and calling bst_print.
void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        bst_print(ht->trees[i]);
    }
    return;
}
