#include "bv.h"
#include "node.h"
#include <stdio.h>
#include "bf.h"
#include "speck.h"
#include "bst.h"
#include "regex.h"
#include "ht.h"
#include "parser.h"
#define WORD "([a-zA-Z0-9_]+(['-]|[a-z0-9A-Z_])+[a-zA_Z0-9_]+)|([a-zA-Z0-9_]+)"
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
       regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }

    char *word = NULL;
    while ((word = next_word(stdin, &re)) != NULL) {
        printf("Word: %s\n", word);
    }

    clear_words();
    regfree(&re);
    return 0;

    }
}
