#include "node.h"
#include "pq.h"
#include "code.h"
#include "stack.h"
#include "huffman.h"
#include <stdio.h>
int main() {
    Code C = code_init();
    code_push_bit(&C, 1);
    code_push_bit(&C, 0);
    code_push_bit(&C, 1);

    code_push_bit(&C, 0);

    code_push_bit(&C, 0);

    code_push_bit(&C, 1);

    code_push_bit(&C, 1);

    code_print(&C);
    uint8_t as = 19;
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_print(&C);

    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_pop_bit(&C, &as);
    printf("poppin as%u\n", as);
    code_print(&C);
    Node *nodeone = node_create('s', 4);
    Node *nocdetwo = node_create('a', 8);
    Stack *s = stack_create(12);
   stack_push(s, nodeone);
  stack_push(s, nocdetwo); 
  stack_print(s);
     Node *nd = node_create('f', 16);
     stack_pop(s, &nd);
     node_print(nd);
}
