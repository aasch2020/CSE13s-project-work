#include "bv.h"
#include "node.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "bf.h"
#include "speck.h"
#include "bst.h"
#include "regex.h"
#include "messages.h"
#include "ht.h"
#include "parser.h"
#define WORD    "(([a-zA-Z0-9_]+(['-]|[a-z0-9A-Z_])+[a-zA_Z0-9_]+)+|([a-zA-Z0-9_]+))"
#define OPTIONS "hst:f:"
int main(int argc, char **argv) {
    int opt = 0;
    bool stats = false;
    int htsize = 65536;
    int bfsize = 1048576;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n  A word filtering program for the GPRSC.\n  Filters out and reports "
                   "bad words parsed from stdin.\n\n");
            printf("USAGE\n  ./banhammer [-hs] [-t size] [-f size]\n\n");
            printf("OPTIONS\n  -h           Program usage and help.\n  -s           Print "
                   "program statistics.\n  -t size      Specify hash table size (default: 2^16).\n "
                   " -f "
                   "size      Specify Bloom filter size (default: 2^20).\n");
            return 0;
            break;
        case 's': stats = true; break;
        case 't': htsize = strtoul(optarg, NULL, 10); break;
        case 'f': bfsize = strtoul(optarg, NULL, 10); break;
        }
    }

    BloomFilter *bf = bf_create(bfsize);
    HashTable *ht = ht_create(htsize);
    FILE *badspeakfile;
    badspeakfile = fopen("badspeak.txt", "r");
    char badspk[1024];
    while (EOF != fscanf(badspeakfile, "%s", badspk)) {
        // printf("%s\n", badspk);
        bf_insert(bf, badspk);
        ht_insert(ht, badspk, NULL);
    }
    FILE *newspeakfile;
    newspeakfile = fopen("newspeak.txt", "r");
    char oldspk[1024];
    char newspk[1024];
    while (EOF != fscanf(newspeakfile, "%s %s", oldspk, newspk)) {
        // printf("%s %s", oldspk, newspk);
        bf_insert(bf, oldspk);
        ht_insert(ht, oldspk, newspk);
    }
    regex_t regex;
    if (regcomp(&regex, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }
    Node *broot = NULL;
    Node *oroot = NULL;
    bool old = false;
    bool bad = false;
    char *word = NULL;
    Node *find = NULL;
    // double htcnt = ht_avg_bst_size(ht);

    // printf("avg bst size %f\n", htcnt);
    //   printf("%Lf\n", ((long double)branches)/lookups);

    while ((word = next_word(stdin, &regex)) != NULL) {
        for (unsigned long i = 0; i < strlen(word); i++) {
            word[i] = tolower(word[i]);
        }
        if (bf_probe(bf, word)) {
            find = ht_lookup(ht, word);
            if (find) {
                if (find->newspeak) {
                    old = true;
                    if (!oroot) {
                        oroot = node_create(find->oldspeak, find->newspeak);
                    } else {
                        bst_insert(oroot, find->oldspeak, find->newspeak);
                    }

                } else {
                    if (!broot) {
                        broot = node_create(find->oldspeak, find->newspeak);
                    } else {
                        bst_insert(broot, find->oldspeak, find->newspeak);
                    }

                    bad = true;
                }
            }
        }
    }
    if (stats) {
        printf("Average BST size: %f\n", ht_avg_bst_size(ht));
        printf("Average BST height: %f\n", ht_avg_bst_height(ht));

        printf("Average branches traversed: %Lf\n", ((long double) branches) / lookups);
        printf("Hash table load: %f%%\n", 100.0 * ht_count(ht) / ht_size(ht));
        printf("Bloom filter load: %f%%\n", 100.0 * bf_count(bf) / bf_size(bf));

    } else {

        if (old & bad) {
            printf("%s", mixspeak_message);
        }
        if (old & !bad) {
            printf("%s", goodspeak_message);
        }
        if (bad & !old) {
            printf("%s", badspeak_message);
        }

        bst_print(broot);
        bst_print(oroot);
    }
    clear_words();
    bst_delete(&broot);
    bst_delete(&oroot);
    ht_delete(&ht);
    fclose(newspeakfile);
    fclose(badspeakfile);
    bf_delete(&bf);
    regfree(&regex);
    return 0;
}
