#include "node.h"
#include "pq.h"
#include "code.h"
#include "stack.h"
#include "huffman.h"
int main() {
    Code C = code_init();
    code_print(&C);
}
