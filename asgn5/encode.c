#include "node.h"
#include "pq.h"
#include "code.h"
#include "stack.h"
#include "huffman.h"
#include <stdio.h>
int main() {
    Code C = code_init();
    code_set_bit(&C, 0);
    code_print(&C);
}
