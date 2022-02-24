#include "stack.h"
#include <stdlib.h>
#include <string.h>

// Function Definitions

Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack)
    {
        stack->length = 0;
        stack->top = NULL;
    }

    return stack;
}
void deleteStack(Stack *stack)
{
    if (!stack)
        return;

    while (stack->length)
        popStack(stack, NULL);

    free(stack);
}
void deleteStackData(void *data)
{
    if (!data)
        return;

    free(data);
}

int pushStack(Stack *stack, void *data, unsigned long dataLength)
{
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    if (!node)
        return -1;

    node->length = dataLength;
    node->data = malloc(dataLength);
    if (!node->data)
    {
        free(node);
        return -2;
    }

    memcpy(node->data, data, dataLength);
    node->next = stack->top;
    stack->top = node;
    stack->length++;

    return 0;
}
unsigned long topStack(Stack *stack, void **dataOut)
{
    if (!stack->length)
        return 0;

    if (dataOut)
        *dataOut = stack->top->data;

    return stack->top->length;
}
unsigned long popStack(Stack *stack, void **dataOut)
{
    if (!stack->length)
        return 0;

    StackNode *topNode = stack->top;
    unsigned long dataLength = topNode->length;
    if (dataOut)
        *dataOut = topNode->data;
    else
        free(topNode->data);

    stack->top = topNode->next;
    free(topNode);
    stack->length--;

    return dataLength;
}