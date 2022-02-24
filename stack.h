#ifndef STACK_H
#define STACK_H

// Structures

typedef struct stacknode
{
    // Data
    void *data;
    unsigned long length;

    // Link
    struct stacknode *next;
} StackNode;
typedef struct
{
    StackNode *top;
    int length;
} Stack;

// Function Declarations

Stack *createStack();
void deleteStack(Stack *);
void deleteStackData(void *);

int pushStack(Stack *, void *, unsigned long);
unsigned long topStack(Stack *, void **);
unsigned long popStack(Stack *, void **);

#endif