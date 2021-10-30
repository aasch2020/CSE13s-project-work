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
       c->bits[(i / 8)] = (c->bits[(i / 8)] | (1 << (i % 8)));
    return true;
}

bool code_clr_bit(Code *c, uint32_t i){
 if (i >= MAX_CODE_SIZE * 8) {
        return false;
    }
       c->bits[(i / 8)] = (c->bits[(i / 8)] & ~(1 << (i % 8)));
    return true;	
}
bool code_get_bit(Code *c, uint32_t i){
	if (i >= MAX_CODE_SIZE * 8) {
        return false;
    }
    return (c->bits[(i/8)] >> (i % 8) & 1);

}
bool code_push_bit(Code *c, uint8_t bit){
	if(c->top >= MAX_CODE_SIZE*8){
		return false;
	
	}
	if(bit){


	code_set_bit(c, c->top);
		c->top++;
		return true;

	}else{
		c->top++;
		return true;

	}
	
}

bool code_pop_bit(Code *c, uint8_t *bit){
	if(c->top >= MAX_CODE_SIZE*8){

		return false;
	}
	if(code_get_bit(c, c->top - 1)){
		*bit = 1;
		code_clr_bit(c, c->top -1);
		c->top--;
		return true;
	}else{
		code_clr_bit(c, c->top -1);
		*bit = 0;
		c->top--;
		return true;
	}	
}
void code_print(Code *c) {
    printf("%u\n", c->top);
    for (uint32_t i = 0; i < (MAX_CODE_SIZE); i++) {
        printf("%" PRIu8, c->bits[i]);
    }
    printf("\n");
}
