#include "stack.h"

#include "node.h"
//The above header files provided in the resources repo by Professor Long. (2021 P;rofessor Long)
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//The below struct definition provided in the assignment document by Professor Long. (2021 Professor Long)
struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

//The below function creates the stack, and takes on integer for the capcacity of the stack
//It also allocates memory as appropriate and returns a null ponter on failed allocation
//The allocated array is an array of node pointers as this stack stores nodes.
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (Node **) calloc(capacity, sizeof(Node *));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

//This code takes a pointer to a pointer to a stack, and first frees the array of items in stack, then frees stack.
//Then it sets the pointer to null perevent call after free.

void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

//This function takes a pointer to a stack and returns true if the stack is empty by checking if the top is 0.
bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    } else {
        return false;
    }
}

//This function takes a pointer to a stack and returns true if the stack is full by checking if the top is equal to the capacity.
bool stack_full(Stack *s) {
    if (s->top == s->capacity) {
        return true;
    } else {
        return false;
    }
}

//This function returns the size of the stack, which is the number of the top of the stack.
uint32_t stack_size(Stack *s) {
    return s->top;
}

//This function takes the stack and a node, and adds that node to the top of the stack
//It then increases the top by one to reflect that change.
//It ensures the stack is not full before doing this, in which case false is returned.
bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) {
        return false;
    } else {
        s->items[s->top] = n;
        s->top++;
        return true;
    }
}

//This function takes the stack and a pointer to an node, and removes the top item from the stack if it is not empty.
//The function returns a boolean for succeeded pop which is false if the stack is empty, and puts the popped value in the pointer n.
bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) {
        return false;
    } else {
        s->top--;
        *n = s->items[s->top];
        s->items[s->top] = 0;

        return true;
    }
}

//This function takes a stack and prints all nodes in the stack
void stack_print(Stack *s) {
    for (uint32_t i = 0; i < s->top; i++) {
        node_print(s->items[i]);
    }
}
