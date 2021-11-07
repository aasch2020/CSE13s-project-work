#include "code.h"
#include "defines.h"
// The above header file provided by Professor Long in the resources respository (Professor Long 2021)
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>

//This function initializes the code struct, it takes no arguments, and returns a code.
Code code_init(void) {
    Code c;
    c.top = 0;
    for (uint32_t i = 0; i < (MAX_CODE_SIZE); i++) {
        c.bits[i] = 0;
    }
    return c;
}

//This function takes a pointer to a code c, and returns the size of the code c, which is the location of the pointer to top.
uint32_t code_size(Code *c) {
    return c->top;
}

//This function takes a pointer to a code c, and returns true if the code is empty, which is when the top is 0.
bool code_empty(Code *c) {
    if (c->top == 0) {
        return true;
    }
    return false;
}

//This boolean checks if a code is full, by taking a pointer to a code c, and checking if the top, or the number of bits in the code is equal to
//The MAX_CODE_SIZE macro * 8, which converts the max number of bytes to bits
bool code_full(Code *c) {
    if (c->top == MAX_CODE_SIZE * 8) {
        return true;
    }
    return false;
}

//This function take a code c, and an index in the code  i, and sets the bit at that location in the code to 1.
//It achieves this by taking the bitwise or of the given byte which is the bit divided by 8, and 1 shifted over
//the correct amount of bits, which is the current bit modulo 8.
//It retuns a boolean, which is true if the set is successful and false if it is out of range.
bool code_set_bit(Code *c, uint32_t i) {
    if (i >= MAX_CODE_SIZE * 8) {
        return false;
    }
    c->bits[(i / 8)] = (c->bits[(i / 8)] | (1 << (i % 8)));
    return true;
}

//This function takes the pointer to a code c and an integer i, i being the index for clearing the bit.
//It clears the bit at the given index by setting it to zero.
//It achieves this by finding the correct byte and bit as the code_set_bit,
//but instead of doing bitwise or with 1 shifted by the bit shift, it instead does a bitwise and with
//A byte which is all ones except a zero in the position to clear.
//It returns true if the clear is successful and false if the index is out of range.
bool code_clr_bit(Code *c, uint32_t i) {
    if (i >= MAX_CODE_SIZE * 8) {
        return false;
    }
    c->bits[(i / 8)] = (c->bits[(i / 8)] & ~(1 << (i % 8)));
    return true;
}

//This function retreives the bit at index i, by taking a pointer to code c and a pointer to code i.
//It returns a boolean value of false if the bit is out of range or zero, and true iff the bit is one
//This function achieves this by returning the biwise and of the given byte for the corresponding bit,
//and one shifted by the amount of the index modulo 8.
bool code_get_bit(Code *c, uint32_t i) {
    if (i >= MAX_CODE_SIZE * 8) {
        return false;
    }
    return (c->bits[(i / 8)] >> (i % 8) & 1);
}

//This function pushes a bit given in the bit and a code pointer to push the pointer to.
//This returns false if the code is full, else uses the above code set or clear bit, depending on if the bit is zero or one
//to set or clear the bit at the top of the code as appropriate.
bool code_push_bit(Code *c, uint8_t bit) {
    if (c->top >= MAX_CODE_SIZE * 8) {
        return false;
    }
    if (bit) {

        code_set_bit(c, c->top);
        c->top++;
        return true;

    } else {
        code_clr_bit(c, c->top);
        c->top++;
        return true;
    }
}

//This function pops the bit into the bit pointer given in args from the code given.
//It returns true or false depending on if the code is empty, and thus pop fails
//It puts the bit at the index of top-1 using code_get_bit into the pointer bit, and then clears the bit at top, and decrements the top by 1.
bool code_pop_bit(Code *c, uint8_t *bit) {
    if (c->top <= 0) {

        return false;
    }
    if (code_get_bit(c, c->top - 1)) {
        *bit = 1;
        code_clr_bit(c, c->top - 1);
        c->top--;
        return true;
    } else {
        code_clr_bit(c, c->top - 1);
        *bit = 0;
        c->top--;
        return true;
    }
}

//This funciton take a code c and returns void.
//It prints the top and the code of a code struct
void code_print(Code *c) {
    printf("%u\n", c->top);
    for (uint32_t i = 0; i < (MAX_CODE_SIZE); i++) {
        printf(" %" PRIu8 " ", c->bits[i]);
    }
    printf("\n");
    return;
}
