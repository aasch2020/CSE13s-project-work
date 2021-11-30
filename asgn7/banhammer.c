#include "bv.h"
#include "node.h"
#include <stdio.h>
#include "bf.h"
#include "speck.h"
#include "bst.h"
int main() {
    printf("main");
    char test[] = "newspeaks";
    char testing[] = "oldspeaks";
    char asdf[] = "badspeaks";
    Node *a = node_create(test, testing);
    node_print(a);
    test[3] = 'z';
    node_print(a);
    Node *b = node_create(asdf, NULL);
    node_print(b);
    BitVector *bv = bv_create(8);
    bv_print(bv);
    bv_set_bit(bv, 0);
    bv_set_bit(bv, 6);
    bv_print(bv);
    bv_clr_bit(bv, 0);
    bv_print(bv);
    node_delete(&a);
    node_delete(&b);
    bv_delete(&bv);
    Node *root = bst_create();
    root = node_create("a", "b");

    bst_insert(root, "a", "xd");
//    node_print(root);
   bst_insert(root, "av", "Abba");
    
    bst_insert(root, "am", "Abba");
    bst_insert(root, "xd", "z");
  //  node_print(bst_find(root, "av" ));
  //  node_print(bst_find(root, "xd"));
    bst_print(root);
}
