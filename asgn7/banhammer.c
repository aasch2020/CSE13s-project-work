#include "bv.h"
#include "node.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "bf.h"
#include "speck.h"
#include "bst.h"
#include "regex.h"
#include "messages.h"
#include "ht.h"
#include "parser.h"
#define WORD "(([a-zA-Z0-9_]+(['-]|[a-z0-9A-Z_])+[a-zA_Z0-9_]+)|([a-zA-Z0-9_]+))"
int main() {

    BloomFilter *bf = bf_create(1000000);
    HashTable *ht = ht_create(60000);
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
        if (!bf_probe(bf, oldspk)) {
            printf("problem\n");
        }
        if (!ht_lookup(ht, oldspk)) {
            printf("prbp\n");
        }
    }
    //    ht_print(ht);

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
    if (old & bad) {
        printf("%s", mixspeak_message);
    }
    if (old & !bad) {
        printf("%s", goodspeak_message);
    }
    if (bad & !old) {
        printf("%s", badspeak_message);
    }
    double htcnt = ht_avg_bst_size(ht);
    printf("avg bst size %f\n", htcnt);
    bst_print(broot);
    bst_print(oroot);
    clear_words();
    printf("avg branch traversed%Lf\n", ((long double)branches)/lookups);
    printf("Hast table lode%f\n", 100.0 * ht_count(ht)/ht_size(ht));
    printf("bflode %f\n", 100.0 *bf_count(bf)/bf_size(bf));
    bst_delete(&broot);
    bst_delete(&oroot);
    ht_delete(&ht);
    fclose(newspeakfile);
    fclose(badspeakfile);
    bf_delete(&bf);
    regfree(&regex);
    return 0;
}
