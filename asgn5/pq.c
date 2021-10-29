#include "pq.h"
#include <stdlib.h>
#include <stdio.h>
struct PriorityQueue {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (pq) {
        pq->top = 0;
        pq->capacity = capacity;
        pq->items = (Node **) calloc(capacity, sizeof(Node *));

        if (!pq->items) {
            free(pq);
            pq = NULL;
        }
    }
    return pq;
}
void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

bool pq_empty(PriorityQueue *q) {
    if (q->top == 0) {
        return true;
    }
    return false;
}

bool pq_full(PriorityQueue *q) {
    if (q->top == q->capacity) {
        return true;
    }
    return false;
}

uint32_t pq_size(PriorityQueue *q) {
    return q->top;
}

void node_swap(Node **x, Node **y) {
    Node *t = *x;
    *x = *y;
    *y = t;
    return;
}

uint32_t min_node_child(PriorityQueue *q, uint32_t parent_index, uint32_t end) {
    uint32_t left = 2 * parent_index;
    uint32_t right = left + 1;
    if ((right <= end)
        && (((q->items[right - 1])->frequency) < ((q->items[left - 1])->frequency))) {
        return right;
    } else {
        return left;
    }
}
bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) {
        return false;
    } else {
        q->items[q->top] = n;
        q->top += 1;
        uint32_t current = q->top;
        bool fixed = false;
        while ((current > 1) && !(fixed)) {
            if (((q->items[current - 1])->frequency) < ((q->items[(current / 2) - 1])->frequency)) {
                node_swap(&q->items[current - 1], &q->items[(current / 2) - 1]);
            } else {
                fixed = true;
            }
            current = current / 2;
        }
        return true;
    }
}

bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    }
    node_swap(&q->items[0], &q->items[q->top - 1]);
    q->top--;
    *n = q->items[q->top];
    uint32_t parent = 1;
    uint32_t least_child = min_node_child(q, parent, q->top);
    bool fixed = false;
    while ((parent <= (q->top / 2)) && !(fixed)) {
        if (((q->items[parent - 1])->frequency) > ((q->items[least_child - 1])->frequency)) {
            node_swap(&q->items[parent - 1], &q->items[least_child - 1]);
            parent = least_child;
            least_child = min_node_child(q, parent, q->top);

        } else {
            fixed = true;
        }
    }
    return true;
}

void pq_print(PriorityQueue *q) {
    printf("\n");
    uint32_t cntr = 0;
    uint32_t tree = 1;
    for (uint32_t i = 0; i < q->top; i++) {
        printf("           %lu             ", (q->items[i])->frequency);
        cntr++;
        if (cntr == tree) {
            printf("\n");
            tree *= 2;
            cntr = 0;
        }
    }
    printf("\n");
    return;
}
