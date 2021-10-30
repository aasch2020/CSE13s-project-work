#include "node.h"
#include "pq.h"
#include "code.h"
#include "stack.h"
#include "huffman.h"
#include <stdio.h>
int main() {
    Code C = code_init();
    code_push_bit(&C, 1);
   
    code_print(&C);
    uint8_t as = 19;
    code_pop_bit(&C, &as);
    code_print(&C);
}
