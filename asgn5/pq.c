#include "pq.h"
//The above header file provided in the resources repository by Professor Long (Professor Long 2021)
#include <stdlib.h>
#include <stdio.h>

//This is the struct definition for a priority queue of nodes, which will have an array of nodes
//a top index, and a capacity
struct PriorityQueue {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

//This function creates a priority queue by allocating the memory needed for an array of nodes of the lenght of the given capacity.
//It then sets the node capacity to the given capacity and the top to 0
//it returns the address to the created queue.
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

//This function takes a pointer to a pointer to a priority queue and deletes it
//it free the memeory allocated for the array, frees the memory, and sets the pointer to null.
void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

//This function takes a pointer to a priority queue, and returns if the queue is empty as a boolean
//The queue is empty when the top is 0.
bool pq_empty(PriorityQueue *q) {
    if (q->top == 0) {
        return true;
    }
    return false;
}

//This function takes a pointer to a priority queue, and returns if the queue is full as a boolean
//The queue is full when the top is the capacity
bool pq_full(PriorityQueue *q) {
    if (q->top == q->capacity) {
        return true;
    }
    return false;
}

//This function takes a pointer to the priority queue and  returns the size as an integer.
//The size the the current value of top.
uint32_t pq_size(PriorityQueue *q) {
    return q->top;
}

//This helper function is used in enqueue and dequeue
//it takes two pointers to address of two nodes, and swaps the values in the nodes.
void node_swap(Node **x, Node **y) {
    Node *t = *x;
    *x = *y;
    *y = t;
    return;
}

//This helper function takes a priority queue, a parent index, and an end index
//It returns the index of the smaller child of the parent node
//It does this by comparing the frequencies of the child nodes, and checking if those child nodes
//do not fall out of the array.
//it then returns the index of the smaller node.
//The function is used in enqueue and dequeue.
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

//This helper function enqueues a node n into priority queue q.
//It retuns a boolean to indicate successful enqueue, which is false when the queue is already full
//It enqueues a node by adding the given node to the end.
//It then swaps the given node and it's parent node while the node is not the first node, and the node
//is less than it's parent, thus making sure the queue remains in a min heap.
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

//This function takes the address of a pointer to a node, and a pointer to a priority queue
//It dequeues the element with least frequency into the given node pointer
//It returns a boolean for successful dequeue which is false when the queue is empty and true otherwise.
//This function first swaps the first and last items, it then puts the last item into the pointer of node given,
//and decrements the top by one, which dequeues the node and shortens the queue by one.
//It then must fix the heap in the queue, which is achieved by using the first node as the first parent,
//and swapping it with it's smallest child, as long as it is larger than it's smallest child.
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

//This debug function prints the prioirty queue, by iterating until the end of the tree and pointeing the symbol and frequency of the element,
void pq_print(PriorityQueue *q) {
    printf("\n");
    uint32_t cntr = 0;
    uint32_t tree = 1;
    for (uint32_t i = 0; i < q->top; i++) {
        printf("         %c  %lu             ", ((q->items[i])->symbol), (q->items[i])->frequency);
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
