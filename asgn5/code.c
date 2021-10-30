#include "code.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>
Code code_init(void) {
    Code c;
    c.top = 0;
    for (uint32_t i = 0; i < (MAX_CODE_SIZE); i++) {
        c.bits[i] = 0;
    }
    return c;
}
uint32_t code_size(Code *c) {
    return c->top;
}
bool code_empty(Code *c) {
    if (c->top == 0) {
        return true;
    }
    return false;
}

bool code_full(Code *c) {
    if (c->top == MAX_CODE_SIZE * 8) {
        return true;
    }
    return false;
}

bool code_set_bit(Code *c, uint32_t i) {
    if (i >= MAX_CODE_SIZE * 8) {
        return false;
    }
    printf("\n");
    printf("%d\n", (i / 8));

    printf("asdf\n");
    printf("%d\n", (i % 8));
    c->bits[(i / 8)] = (c->bits[(i / 8)] | (1 << (% 8)));
    return true;
}
void code_print(Code *c) {
    printf("%u\n", c->top);
    for (uint32_t i = 0; i < (MAX_CODE_SIZE); i++) {
        printf("%" PRIu8, c->bits[i]);
    }
    printf("\n");
}