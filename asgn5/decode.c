#include "node.h"
#include "pq.h"
#include "code.h"
#include "stack.h"
#include "huffman.h"
#include <stdio.h>
int main() {
    Code c = code_init();
    code_set_bit(&c, 2);
    code_print(&c);
    printf("%d", code_get_bit(&c, 2));
    code_clr_bit(&c, 2);
    code_print(&c);
    uint8_t asd = 0;

    for (int i = 0; i <= 255; i++) {
        code_push_bit(&c, 1);
        code_pop_bit(&c, &asd);
        code_print(&c);
    }
    for (int i = 0; i <= 256; i++) {
        uint8_t asd = 0;
        code_pop_bit(&c, &asd);
        code_print(&c);
    }
}
