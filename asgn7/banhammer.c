#include "bv.h"
#include "node.h"
#include "bf.h"
#include "speck.h" //The implementation of this hashing function, speck.c is provided in the resources repository by Professor Long (Professor Long 2021)
#include "bst.h"
#include "regex.h"
#include "messages.h"
#include "ht.h"
#include "parser.h" //The implementation of this parser, parser.c also provided in the resources repository by Professor Long (Professor Long 2021)
//The above header files provided by Professor Long in the resources respository. (Professor Long 2021)
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define WORD    "(([a-zA-Z0-9_]+(['-]|[a-z0-9A-Z_])+[a-zA_Z0-9_]+)+|([a-zA-Z0-9_]+))"
#define OPTIONS "hst:f:"
//
//The main function takes command line arguments, and parses stdin for banned words after reading in banned words from badspeak and newspeak files.
//
int main(int argc, char **argv) {
    //This code loops over command line arguments, and parses the arguments to set the size of the bloom filter, hash table, and stats will be printed
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
    //This code creates a bloom filter and hash table to store the given badspeak.
    //It then opens the badspeak text file, and loops over it until all words are read, adding it to the bloom filter and hash table.
    BloomFilter *bf = bf_create(bfsize);
    HashTable *ht = ht_create(htsize);
    FILE *badspeakfile;
    badspeakfile = fopen("badspeak.txt", "r");
    char badspk[1024];
    while (EOF != fscanf(badspeakfile, "%s", badspk)) {
        bf_insert(bf, badspk);
        ht_insert(ht, badspk, NULL);
    }
    //This code opens a file for newspeak, and loops through it until all oldspeak newspeak pairs are inserted into the bloom filter and hash table.
    FILE *newspeakfile;
    newspeakfile = fopen("newspeak.txt", "r");
    char oldspk[1024];
    char newspk[1024];
    while (EOF != fscanf(newspeakfile, "%s %s", oldspk, newspk)) {
        bf_insert(bf, oldspk);
        ht_insert(ht, oldspk, newspk);
    }
    //This below code compiles a regular expression using the defined word.
    //This code for compiling the regex inspired/adapted from the regex example program provided in the assignment document (Professor Long 2021).
    regex_t regex;
    if (regcomp(&regex, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }
    //This below code creates two net bst for badspeak and oldspeak, and two booleans for if oldspeak or badspeak are found.
    Node *broot = NULL;
    Node *oroot = NULL;
    bool old = false;
    bool bad = false;
    char *word = NULL;
    Node *find = NULL;
    //This below loop inspired by/adapted from the regex example program provided in the assignment document (Professor Long 2021).
    while ((word = next_word(stdin, &regex)) != NULL) {
        for (unsigned long i = 0; i < strlen(word); i++) {
            word[i] = tolower(
                word[i]); // for each read word, convert each character in the word to lowercase using tolower
        }
        if (bf_probe(bf, word)) { //Check if the word is in the Bloom Filter.
            find = ht_lookup(ht, word);
            if (find) { //Check if the word is in the hash table.
                if (find->newspeak) { //Check if the word is badspeak or oldspeak by if it has a newspeak translation.
                    old = true;
                    if (!oroot) { //If the oldspeak tree is empty, set the node to the root, if not, insert the node.
                        oroot = node_create(find->oldspeak, find->newspeak);
                    } else {
                        bst_insert(oroot, find->oldspeak, find->newspeak);
                    }

                } else {
                    if (!broot) { //If the oldspeak tree is empty, set the node to the root, if not, insert the node.
                        broot = node_create(find->oldspeak, find->newspeak);
                    } else {
                        bst_insert(broot, find->oldspeak, find->newspeak);
                    }

                    bad = true;
                }
            }
        }
    }
    if (stats) { //If the stats arg is specified, print the statistics of the program and nothing else.
        printf("Average BST size: %f\n", ht_avg_bst_size(ht));
        printf("Average BST height: %f\n", ht_avg_bst_height(ht));

        printf("Average branches traversed: %Lf\n",
            ((long double) branches)
                / lookups); //Cast branches to double, as we want a floating point value.
        printf("Hash table load: %f%%\n", 100.0 * ht_count(ht) / ht_size(ht));
        printf("Bloom filter load: %f%%\n", 100.0 * bf_count(bf) / bf_size(bf));

    } else {
        if (old & bad) { //Print the corresponding messages as to what was found in the input.
            printf("%s", mixspeak_message);
        }
        if (old & !bad) {
            printf("%s", goodspeak_message);
        }
        if (bad & !old) {
            printf("%s", badspeak_message);
        }
        //Print the binary search trees of badspeak and oldspeak that we found.
        bst_print(broot);
        bst_print(oroot);
    }
    //Clears the allocated memory.
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
