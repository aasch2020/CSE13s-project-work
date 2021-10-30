#include "node.h"
#include "pq.h"
#include "code.h"
#include "stack.h"
#include "huffman.h"
#include <stdio.h>
int main() {
    Code C = code_init();
    code_print(&C);
    printf("asdf\n");
    printf("mainskis\n");
    struct Node *nodeone = node_create('a', 5);
    struct Node *nodetwo = node_create('x', 12);
    struct Node *nodethree = node_join(nodeone, nodetwo);
    struct Node *nodefour = node_join(nodethree, nodetwo);
    struct PriorityQueue *pq = pq_create(13);
    //   struct Node *nodetwo = node_create('x', 12);
    struct Node *a = node_create('x', 2);
    struct Node *b = node_create('x', 45);
    struct Node *c = node_create('x', 3);
    struct Node *d = node_create('x', 123);
    struct Node *e = node_create('x', 4);
    struct Node *f = node_create('s', 1);
    enqueue(pq, f);
    enqueue(pq, a);
    enqueue(pq, b);
    enqueue(pq, c);
    enqueue(pq, d);
    enqueue(pq, e);
    // enqueue(pq, nodetwo);
    // enqueue(pq, nodefour);
    // enqueue(pq, nodeone);
    //  enqueue(pq, nodethree);

    pq_print(pq);

    dequeue(pq, &a);
    dequeue(pq, &b);
    dequeue(pq, &c);
    dequeue(pq, &d);
    dequeue(pq, &e);
    dequeue(pq, &f);
    dequeue(pq, &nodeone);
    pq_print(pq);
    pq_delete(&pq);
    node_delete(&nodefour);
    node_delete(&nodeone);
    node_delete(&nodetwo);
    node_delete(&nodethree);
    node_print(a);
    node_print(b);
    node_print(c);
    node_print(d);
    node_print(e);
    node_print(f);
    node_delete(&a);
    node_delete(&b);
    node_delete(&c);
}
