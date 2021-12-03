#include "parser.h"
#include <regex.h>
#include <stdio.h>
//This code supplied in the assignment document by Professor Long(Professor Long 2021).
//This code not used in the implementation of the assignment, but used to debug the implementation of regex.
#define WORD "([a-zA-Z_0]+(['-]|[a-z_0-9A-Z])+[a-z]+)|([a-zA-Z])"
/*
int main(void) {
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
}*/
