#include "bv.h"
#include "node.h"
#include <stdio.h>
#include "bf.h"
#include "speck.h"
#include "bst.h"
#include "ht.h"
int main() {

    Node *root = bst_create();
    root = node_create("a", "b");

    bst_insert(root, "a", "xd");
    //    node_print(root);
    bst_insert(root, "av", "Abba");

    bst_insert(root, "am", "Abba");
    bst_insert(root, "xd", "z");
    // node_print(bst_find(root, "av" ));
    node_print(bst_find(root, "xd"));

    bst_print(root);
    bst_delete(&root);
    BloomFilter *bf = bf_create(30);

    bf_insert(bf, "Zato");
    bf_print(bf);
    if (bf_probe(bf, "Zato")) {
        printf("worky");
    }
}
