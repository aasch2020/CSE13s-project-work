#include "bv.h"
#include "bst.h"
#include "salts.h"
#include <stdlib.h>
#include "ht.h"
#include "node.h"
#include "speck.h"
struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **trees;
};

HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) calloc(1, sizeof(HashTable));
    if (ht) {
        ht->size = size;
        ht->trees = (Node **) calloc(size, sizeof(Node *));
        ht->salt[0] = SALT_HASHTABLE_LO;
        ht->salt[1] = SALT_HASHTABLE_HI;
    }
    return ht;
}

void ht_delete(HashTable **ht) {
    for (uint32_t i = 0; i < (*ht)->size; i++) {
        if ((*ht)->trees[i]) {
            bst_delete(&((*ht)->trees[i]));
        }
    }
    free(*ht);
    *ht = NULL;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    if (ht->trees[(hash(ht->salt, oldspeak) % ht->size)]) {
        return bst_find((ht->trees[(hash(ht->salt, oldspeak) % ht->size)]), oldspeak);
    }
    return NULL;
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    if (ht->trees[(hash(ht->salt, oldspeak) % ht->size)]) {
        bst_insert((ht->trees[(hash(ht->salt, oldspeak) % ht->size)]), oldspeak, newspeak);

    } else {
        ht->trees[(hash(ht->salt, oldspeak) % ht->size)] = node_create(oldspeak, newspeak);
    }
}

uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->trees[i]) {
            count++;
        }
    }
    return count;
}
double ht_avg_bst_size(HashTable *ht) {
    double total = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        total += bst_size(ht->trees[i]);
    }
    return total / ht_count(ht);
}
double ht_avg_bst_height(HashTable *ht) {
    double total = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        total += bst_height(ht->trees[i]);
    }
    return total / ht_count(ht);
}

void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        bst_print(ht->trees[i]);
    }
}
