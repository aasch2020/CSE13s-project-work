#include "stack.h"

#include "vertices.h"
//The above header files provided in the resources repo by Professor Long. (2021 P;rofessor Long)
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//The below struct definition provided in the assignment document by Professor Long. (2021 Professor Long)
struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
};

//The below function creates the stack, and takes on integer for the capcacity of the stack
//If also allocates memory as appropriate and returns a null ponter on failed allocation
//This code provided in the assignment document by Professor Long. (2021 Professor Long)
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

//This code takes a pointer to a pointer to a stack, and first frees the array of items in stack, then frees stack.
//Then it sets the pointer to null perevent call after free.
//This code provided in the assignment document by Professor Long. (2021 Professor Long)
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

//Thi function takes a pointer to a stack and returns if the stack is empty by checking if the top is 0.
bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    } else {
        return false;
    }
}

//This function takes a pointer to a stack a nd returns if the stack is full by checking if the top is eqaul to the capacity.
bool stack_full(Stack *s) {
    if (s->top == s->capacity) {
        return true;
    } else {
        return false;
    }
}

//This function returns the size of the stack, which is the top of the stack.
uint32_t stack_size(Stack *s) {
    return s->top;
}

//This function takes the stack and an integer, and adds that integer to the top of the stack
//It then increases the top by one to reflect that change.
//It ensures the stack is not full before doing this.
bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s)) {
        return false;
    } else {
        s->items[s->top] = x;
        s->top++;
        return true;
    }
}

//This function takes the stack and a pointer to an integer, and removes the top item from the stack if it is not empty.
//The function returns a boolean for succeeded pop, and puts the popped value in the pointer x.
bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    } else {
        s->top--;
        *x = s->items[s->top];
        s->items[s->top] = 0;

        return true;
    }
}

//This function is similar to stack pop in that it takes a pointer to a stack and integer, and puts the top of the stack in pointer x.
//however, this function does not take the top item off the stack.
bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    } else {
        *x = s->items[(s->top - 1)];
        return true;
    }
}

//This function takes two pointers stacks, and copies src to dst, by first copying the top, and then copying the values in the items array
//This is to make sure that the items array is a duplicate and not pointed to the same array.
//this function assumes both stacks are properly created.
void stack_copy(Stack *dst, Stack *src) {
    dst->top = src->top;
    for (uint32_t i = 0; i < src->capacity; i++) {
        dst->items[i] = src->items[i];
    }
    return;
}

//This code is given in the assignment document by Professor Long (2021 Professor Long)
//This function prints the contents of the stack to the given file outfile, and maps the integers in the stack
//to the array of cities given.
void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
    return;
}
