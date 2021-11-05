#include "huffman.h"
#include "pq.h"
#include "node.h"
Node *build_tree(uint64_t hist[static ALPHABET]) {
    Node *a = node_create('0', 0);
    PriorityQueue *pq = pq_create(ALPHABET);
    for (int i = 0; i < 256; i++) {
        if (hist[i]) {
            a = node_create(i, hist[i]);
            enqueue(pq, a);
        }
    }
    pq_print(pq);
    return a;
}
